// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/FileIO.h>

#include <tgCore/Error.h>
#include <tgCore/Format.h>
#include <tgCore/Memory.h>

#include <cstring>
#include <exception>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX
#include <sys/stat.h>
#include <windows.h>

namespace tg
{
    namespace core
    {
        namespace
        {
            enum class ErrorType
            {
                Open,
                OpenTemp,
                MemoryMap,
                Close,
                CloseMemoryMap,
                Read,
                ReadMemoryMap,
                Write,
                Seek,
                SeekMemoryMap
            };

            std::string getErrorMessage(
                ErrorType          type,
                const std::string& fileName,
                const std::string& message = std::string())
            {
                std::string out;
                switch (type)
                {
                case ErrorType::Open:
                    out = Format("{0}: Cannot open file").arg(fileName);
                    break;
                case ErrorType::OpenTemp:
                    out = Format("Cannot open temporary file");
                    break;
                case ErrorType::MemoryMap:
                    out = Format("{0}: Cannot memory map").arg(fileName);
                    break;
                case ErrorType::Close:
                    out = Format("{0}: Cannot close").arg(fileName);
                    break;
                case ErrorType::CloseMemoryMap:
                    out = Format("{0}: Cannot unmap").arg(fileName);
                    break;
                case ErrorType::Read:
                    out = Format("{0}: Cannot read").arg(fileName);
                    break;
                case ErrorType::ReadMemoryMap:
                    out = Format("{0}: Cannot read memory map").arg(fileName);
                    break;
                case ErrorType::Write:
                    out = Format("{0}: Cannot write").arg(fileName);
                    break;
                case ErrorType::Seek:
                    out = Format("{0}: Cannot seek").arg(fileName);
                    break;
                case ErrorType::SeekMemoryMap:
                    out = Format("{0}: Cannot seek memory map").arg(fileName);
                    break;
                default: break;
                }
                if (!message.empty())
                {
                    out = Format("{0}: {1}").arg(out).arg(message);
                }
                return out;
            }

        } // namespace

        struct FileIO::Private
        {
            void setPos(size_t, bool seek);

            std::string    fileName;
            FileMode       mode = FileMode::First;
            FileRead       readType = FileRead::First;
            size_t         pos = 0;
            size_t         size = 0;
            bool           endianConversion = false;
            HANDLE         f = INVALID_HANDLE_VALUE;
            void*          mMap = nullptr;
            const uint8_t* memoryStart = nullptr;
            const uint8_t* memoryEnd = nullptr;
            const uint8_t* memoryP = nullptr;
        };

        FileIO::FileIO() :
            _p(new Private)
        {}

        FileIO::~FileIO()
        {
            _close();
        }

        std::shared_ptr<FileIO> FileIO::create(
            const std::string& fileName,
            const FileMemoryRead& memory)
        {
            auto out = std::shared_ptr<FileIO>(new FileIO);
            out->_p->fileName = fileName;
            out->_p->mode = FileMode::Read;
            out->_p->readType = FileRead::Normal;
            out->_p->size = memory.size;
            out->_p->memoryStart = memory.p;
            out->_p->memoryEnd = memory.p + memory.size;
            out->_p->memoryP = memory.p;
            return out;
        }

        std::shared_ptr<FileIO> FileIO::createTemp()
        {
            auto out = std::shared_ptr<FileIO>(new FileIO);

            WCHAR path[MAX_PATH];
            DWORD r = GetTempPathW(MAX_PATH, path);
            if (!r)
            {
                throw std::runtime_error(
                    getErrorMessage(ErrorType::OpenTemp, std::string(), getLastError()));
            }
            WCHAR buf[MAX_PATH];
            if (GetTempFileNameW(path, L"", 0, buf))
            {
                std::string fileName;
                try
                {
                    fileName = fromWide(buf);
                }
                catch (const std::exception&)
                {
                    throw std::runtime_error(getErrorMessage(ErrorType::OpenTemp, fileName));
                }
                out->_open(fileName, FileMode::ReadWrite, FileRead::Normal);
            }
            else
            {
                throw std::runtime_error(
                    getErrorMessage(ErrorType::OpenTemp, std::string(), getLastError()));
            }

            return out;
        }

        bool FileIO::isOpen() const
        {
            return _p->f != INVALID_HANDLE_VALUE || _p->memoryStart;
        }

        const std::string& FileIO::getFileName() const
        {
            return _p->fileName;
        }

        size_t FileIO::getSize() const
        {
            return _p->size;
        }

        size_t FileIO::getPos() const
        {
            return _p->pos;
        }

        void FileIO::setPos(size_t in)
        {
            _p->setPos(in, false);
        }

        void FileIO::seek(size_t in)
        {
            _p->setPos(in, true);
        }

        const uint8_t* FileIO::getMemoryStart() const
        {
            return _p->memoryStart;
        }

        const uint8_t* FileIO::getMemoryEnd() const
        {
            return _p->memoryEnd;
        }

        const uint8_t* FileIO::getMemoryP() const
        {
            return _p->memoryP;
        }

        bool FileIO::hasEndianConversion() const
        {
            return _p->endianConversion;
        }

        void FileIO::setEndianConversion(bool in)
        {
            _p->endianConversion = in;
        }

        bool FileIO::isEOF() const
        {
            TG_P();
            bool out = false;
            if (!p.memoryStart)
            {
                out |= p.f == INVALID_HANDLE_VALUE;
            }
            out |= p.pos >= p.size;
            return out;
        }

        void FileIO::read(void* in, size_t size, size_t wordSize)
        {
            TG_P();

            if (!p.memoryStart && !p.f)
            {
                throw std::runtime_error(getErrorMessage(ErrorType::Read, p.fileName));
            }

            switch (p.mode)
            {
            case FileMode::Read:
            {
                if (p.memoryStart)
                {
                    const uint8_t* memoryP = p.memoryP + size * wordSize;
                    if (memoryP > p.memoryEnd)
                    {
                        throw std::runtime_error(getErrorMessage(ErrorType::ReadMemoryMap, p.fileName));
                    }
                    if (p.endianConversion && wordSize > 1)
                    {
                        endian(p.memoryP, in, size, wordSize);
                    }
                    else
                    {
                        std::memcpy(in, p.memoryP, size * wordSize);
                    }
                    p.memoryP = memoryP;
                }
                else
                {
                    DWORD n;
                    if (!::ReadFile(p.f, in, static_cast<DWORD>(size * wordSize), &n, 0))
                    {
                        throw std::runtime_error(getErrorMessage(ErrorType::Read, p.fileName, getLastError()));
                    }
                    if (p.endianConversion && wordSize > 1)
                    {
                        endian(in, size, wordSize);
                    }
                }
                break;
            }
            case FileMode::ReadWrite:
            {
                DWORD n;
                if (!::ReadFile(p.f, in, static_cast<DWORD>(size * wordSize), &n, 0))
                {
                    throw std::runtime_error(
                        getErrorMessage(ErrorType::Read, p.fileName, getLastError()));
                }
                if (p.endianConversion && wordSize > 1)
                {
                    endian(in, size, wordSize);
                }
                break;
            }
            default: break;
            }
            p.pos += size * wordSize;
        }

        void FileIO::write(const void* in, size_t size, size_t wordSize)
        {
            TG_P();

            if (!p.f)
            {
                throw std::runtime_error(getErrorMessage(ErrorType::Write, p.fileName));
            }

            const uint8_t* inP = reinterpret_cast<const uint8_t*>(in);
            std::vector<uint8_t> tmp;
            if (p.endianConversion && wordSize > 1)
            {
                tmp.resize(size * wordSize);
                endian(in, tmp.data(), size, wordSize);
                inP = tmp.data();
            }

            DWORD n = 0;
            if (!::WriteFile(p.f, inP, static_cast<DWORD>(size * wordSize), &n, 0))
            {
                throw std::runtime_error(
                    getErrorMessage(ErrorType::Write, p.fileName, getLastError()));
            }
            p.pos += size * wordSize;
            p.size = std::max(p.pos, p.size);
        }

        void FileIO::_open(
            const std::string& fileName,
            FileMode mode,
            FileRead readType)
        {
            TG_P();

            _close();

            const std::wstring fileNameW = toWide(fileName);

            // Open the file.
            DWORD desiredAccess = 0;
            DWORD shareMode = 0;
            DWORD disposition = 0;
            DWORD flags =
                //FILE_ATTRIBUTE_NORMAL;
                FILE_FLAG_SEQUENTIAL_SCAN;
            switch (mode)
            {
            case FileMode::Read:
                desiredAccess = GENERIC_READ;
                shareMode = FILE_SHARE_READ;
                disposition = OPEN_EXISTING;
                break;
            case FileMode::Write:
                desiredAccess = GENERIC_WRITE;
                disposition = CREATE_ALWAYS;
                break;
            case FileMode::ReadWrite:
                desiredAccess = GENERIC_READ | GENERIC_WRITE;
                shareMode = FILE_SHARE_READ;
                disposition = OPEN_EXISTING;
                break;
            case FileMode::Append:
                desiredAccess = GENERIC_WRITE;
                disposition = OPEN_EXISTING;
                break;
            default: break;
            }
            try
            {
                p.f = CreateFileW(
                    fileNameW.c_str(),
                    desiredAccess,
                    shareMode,
                    0,
                    disposition,
                    flags,
                    0);
            }
            catch (const std::exception&)
            {
                p.f = INVALID_HANDLE_VALUE;
            }
            if (INVALID_HANDLE_VALUE == p.f)
            {
                throw std::runtime_error(
                    getErrorMessage(ErrorType::Open, fileName, getLastError()));
            }
            p.fileName = fileName;
            p.mode = mode;
            p.readType = readType;
            p.pos = 0;
            struct _stati64 info;
            memset(&info, 0, sizeof(struct _stati64));
            if (_wstati64(fileNameW.c_str(), &info) != 0)
            {
                throw std::runtime_error(
                    Format("{0}: Cannot get file size").arg(fileName));
            }
            p.size = info.st_size;

            // Memory mapping.
            if (FileRead::MemoryMapped == p.readType &&
                FileMode::Read == p.mode &&
                p.size > 0)
            {
                p.mMap = CreateFileMapping(p.f, 0, PAGE_READONLY, 0, 0, 0);
                if (!p.mMap)
                {
                    throw std::runtime_error(
                        getErrorMessage(ErrorType::MemoryMap, fileName, getLastError()));
                }

                p.memoryStart = reinterpret_cast<const uint8_t*>(MapViewOfFile(p.mMap, FILE_MAP_READ, 0, 0, 0));
                if (!p.memoryStart)
                {
                    throw std::runtime_error(
                        getErrorMessage(ErrorType::MemoryMap, fileName));
                }

                p.memoryEnd = p.memoryStart + p.size;
                p.memoryP = p.memoryStart;
            }
        }

        bool FileIO::_close(std::string* error)
        {
            TG_P();

            bool out = true;

            p.fileName = std::string();

            if (p.mMap)
            {
                if (p.memoryStart)
                {
                    if (!::UnmapViewOfFile((void*)p.memoryStart))
                    {
                        out = false;
                        if (error)
                        {
                            *error = getErrorMessage(
                                ErrorType::CloseMemoryMap, p.fileName, getLastError());
                        }
                    }
                    p.memoryStart = nullptr;
                }

                if (!::CloseHandle(p.mMap))
                {
                    out = false;
                    if (error)
                    {
                        *error = getErrorMessage(
                            ErrorType::Close, p.fileName, getLastError());
                    }
                }
                p.mMap = nullptr;
            }
            p.memoryEnd = nullptr;
            p.memoryP = nullptr;

            if (p.f != INVALID_HANDLE_VALUE)
            {
                CloseHandle(p.f);
                p.f = INVALID_HANDLE_VALUE;
            }

            p.mode = FileMode::First;
            p.pos = 0;
            p.size = 0;

            return out;
        }

        void FileIO::Private::setPos(size_t value, bool seek)
        {
            switch (mode)
            {
            case FileMode::Read:
            {
                if (memoryStart)
                {
                    if (!seek)
                    {
                        memoryP = reinterpret_cast<const uint8_t*>(memoryStart) + value;
                    }
                    else
                    {
                        memoryP += value;
                    }
                    if (memoryP > memoryEnd)
                    {
                        throw std::runtime_error(getErrorMessage(ErrorType::SeekMemoryMap, fileName));
                    }
                }
                else
                {
                    LARGE_INTEGER v;
                    v.QuadPart = value;
                    if (!::SetFilePointerEx(
                        f,
                        static_cast<LARGE_INTEGER>(v),
                        0,
                        !seek ? FILE_BEGIN : FILE_CURRENT))
                    {
                        throw std::runtime_error(getErrorMessage(ErrorType::Seek, fileName, getLastError()));
                    }
                }
                break;
            }
            case FileMode::Write:
            case FileMode::ReadWrite:
            case FileMode::Append:
            {
                LARGE_INTEGER v;
                v.QuadPart = value;
                if (!::SetFilePointerEx(
                    f,
                    static_cast<LARGE_INTEGER>(v),
                    0,
                    !seek ? FILE_BEGIN : FILE_CURRENT))
                {
                    throw std::runtime_error(
                        getErrorMessage(ErrorType::Seek, fileName, getLastError()));
                }
                break;
            }
            default: break;
            }

            if (!seek)
            {
                pos = value;
            }
            else
            {
                pos += value;
            }
        }

        void truncateFile(const std::string& fileName, size_t size)
        {
            HANDLE h = INVALID_HANDLE_VALUE;
            try
            {
                h = CreateFileW(
                    toWide(fileName).c_str(),
                    GENERIC_WRITE,
                    0,
                    0,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    0);
            }
            catch (const std::exception&)
            {
                h = INVALID_HANDLE_VALUE;
            }
            if (INVALID_HANDLE_VALUE == h)
            {
                throw std::runtime_error(
                    getErrorMessage(ErrorType::Open, fileName, getLastError()));
            }
            LARGE_INTEGER v;
            v.QuadPart = size;
            if (!::SetFilePointerEx(
                h,
                static_cast<LARGE_INTEGER>(v),
                0,
                FILE_BEGIN))
            {
                CloseHandle(h);
                throw std::runtime_error(
                    getErrorMessage(ErrorType::Seek, fileName, getLastError()));
            }
            if (!::SetEndOfFile(h))
            {
                CloseHandle(h);
                throw std::runtime_error(
                    getErrorMessage(ErrorType::Write, fileName, getLastError()));
            }
            CloseHandle(h);
        }
    }
}
