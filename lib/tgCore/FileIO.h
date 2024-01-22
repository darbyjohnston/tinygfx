// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/String.h>
#include <tgCore/Util.h>

#include <memory>

namespace tg
{
    namespace core
    {
        //! File I/O modes.
        enum class FileMode
        {
            Read,
            Write,
            ReadWrite,
            Append,

            Count,
            First = Read
        };
        TG_ENUM(FileMode);

        //! File read type.
        enum class FileRead
        {
            Normal,
            MemoryMapped,

            Count,
            First = Normal
        };
        TG_ENUM(FileRead);

        //! Read files from memory.
        struct FileMemoryRead
        {
            FileMemoryRead() = default;
            FileMemoryRead(const uint8_t*, size_t size);

            const uint8_t* p = nullptr;
            size_t size = 0;

            bool operator == (const FileMemoryRead&) const;
            bool operator != (const FileMemoryRead&) const;
        };

        //! File I/O.
        class FileIO
        {
            TG_NON_COPYABLE(FileIO);

        protected:
            FileIO();

        public:
            ~FileIO();

            //! Create a new file I/O object.
            static std::shared_ptr<FileIO> create(
                const std::string& fileName,
                FileMode,
                FileRead = FileRead::MemoryMapped);

            //! Create a read-only file I/O object from memory.
            static std::shared_ptr<FileIO> create(
                const std::string& fileName,
                const FileMemoryRead&);

            //! Create a read-write temporary file I/O object.
            static std::shared_ptr<FileIO> createTemp();

            //! Get whether the file is open.
            bool isOpen() const;

            //! \name Information
            ///@{

            //! Get the file name.
            const std::string& getFileName() const;

            //! Get the file size.
            size_t getSize() const;

            ///@}

            //! \name Position
            ///@{

            //! Get the current file position.
            size_t getPos() const;

            //! Set the current file position.
            void setPos(size_t);

            //! Advance the current file position.
            void seek(size_t);

            //! Get whether the file position is at the end of the file.
            bool isEOF() const;

            ///@}

            //! \name Read
            ///@{

            void read(void*, size_t, size_t wordSize = 1);

            void read8(int8_t*, size_t = 1);
            void readU8(uint8_t*, size_t = 1);
            void read16(int16_t*, size_t = 1);
            void readU16(uint16_t*, size_t = 1);
            void read32(int32_t*, size_t = 1);
            void readU32(uint32_t*, size_t = 1);
            void readF32(float*, size_t = 1);

            ///@}

            //! \name Write
            ///@{

            void write(const void*, size_t, size_t wordSize = 1);

            void write8(const int8_t*, size_t);
            void writeU8(const uint8_t*, size_t);
            void write16(const int16_t*, size_t);
            void writeU16(const uint16_t*, size_t);
            void write32(const int32_t*, size_t);
            void writeU32(const uint32_t*, size_t);
            void writeF32(const float*, size_t);

            void write8(int8_t);
            void writeU8(uint8_t);
            void write16(int16_t);
            void writeU16(uint16_t);
            void write32(int32_t);
            void writeU32(uint32_t);
            void writeF32(float);

            void write(const std::string&);

            ///@}

            //! \name Memory Mapping
            ///@{

            //! Get a pointer to the start of the memory-map.
            const uint8_t* getMemoryStart() const;

            //! Get a pointer to the end of the memory-map.
            const uint8_t* getMemoryEnd() const;

            //! Get the current memory-map position.
            const uint8_t* getMemoryP() const;

            ///@}

            //! \name Endian
            ///@{

            //! Get whether automatic endian conversion is performed.
            bool hasEndianConversion() const;

            //! Set whether automatic endian conversion is performed.
            void setEndianConversion(bool);

            ///@}

        private:
            void _open(const std::string& fileName, FileMode, FileRead);
            bool _close(std::string* error = nullptr);

            TG_PRIVATE();
        };

        //! Read the contents from a file.
        std::string read(const std::shared_ptr<FileIO>&);

        //! Read a word from a file.
        void readWord(const std::shared_ptr<FileIO>&, char*, size_t maxLen = cStringSize);

        //! Read a line from a file.
        //! \todo Should we handle comments like readWord()?
        void readLine(const std::shared_ptr<FileIO>&, char*, size_t maxLen = cStringSize);

        //! Read all the lines from a file.
        std::vector<std::string> readLines(const std::string& fileName);

        //! Write lines to a file.
        void writeLines(const std::string& fileName, const std::vector<std::string>&);

        //! Truncate a file.
        void truncateFile(const std::string& fileName, size_t);
    }
}

#include <tgCore/FileIOInline.h>
