// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/FileIOTest.h>

#include <tgCore/Assert.h>
#include <tgCore/FileIO.h>
#include <tgCore/Format.h>

#include <limits>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        FileIOTest::FileIOTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::FileIOTest")
        {}

        FileIOTest::~FileIOTest()
        {}

        std::shared_ptr<FileIOTest> FileIOTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileIOTest>(new FileIOTest(context));
        }
        
        void FileIOTest::run()
        {
            _enums();
            _members();
            _functions();
            _operators();
        }
        
        void FileIOTest::_enums()
        {
            TINYGFX_TEST_ENUM(FileMode);
            TINYGFX_TEST_ENUM(FileRead);
        }
        
        void FileIOTest::_members()
        {
            for (auto fileRead : getFileReadEnums())
            {
                {
                    const std::string fileName = "FileIOTest";
                    auto fileIO = FileIO::create(fileName, FileMode::Write);
                    TG_ASSERT(fileIO->isOpen());
                    TG_ASSERT(fileName == fileIO->getFileName());
                    TG_ASSERT(0 == fileIO->getPos());
                    fileIO->write("Hello");
                    fileIO->setPos(0);
                    TG_ASSERT(0 == fileIO->getPos());
                    fileIO->seek(1);
                    fileIO->seek(1);
                    TG_ASSERT(2 == fileIO->getPos());
                    TG_ASSERT(!fileIO->isEOF());
                    fileIO->setPos(5);                    
                    TG_ASSERT(fileIO->isEOF());
                    fileIO.reset();
                    
                    fileIO = FileIO::create(fileName, FileMode::Append);
                    fileIO->write(" world");
                    fileIO.reset();

                    fileIO = FileIO::create(fileName, FileMode::Read, fileRead);
                    const size_t size = fileIO->getSize();
                    TG_ASSERT(11 == size);
                    if (FileRead::MemoryMapped == fileRead)
                    {
                        TG_ASSERT(fileIO->getMemoryStart());
                        TG_ASSERT(fileIO->getMemoryEnd());
                        TG_ASSERT(fileIO->getMemoryP());
                    }
                    std::string contents;
                    while (!fileIO->isEOF())
                    {
                        char c = 0;
                        fileIO->read(&c, 1);
                        contents.push_back(c);
                    }
                    TG_ASSERT(contents == "Hello world");
                    fileIO->setPos(0);
                    TG_ASSERT(0 == fileIO->getPos());
                    fileIO->seek(1);
                    fileIO->seek(1);
                    TG_ASSERT(2 == fileIO->getPos());
                    TG_ASSERT(!fileIO->isEOF());
                    fileIO->setPos(fileIO->getSize());                    
                    TG_ASSERT(fileIO->isEOF());
                    fileIO.reset();

                    FileMemoryRead memoryRead((uint8_t*)contents.data(), contents.size());
                    fileIO = FileIO::create(fileName, memoryRead);
                    std::string contents2;
                    while (!fileIO->isEOF())
                    {
                        char c = 0;
                        fileIO->read(&c, 1);
                        contents2.push_back(c);
                    }
                    TG_ASSERT(contents2 == "Hello world");
                }
                {
                    const std::string fileName = "FileIOTest2";
                    auto fileIO = FileIO::create(fileName, FileMode::Write);
                    int8_t i8 = 1;
                    uint8_t u8 = 2;
                    int16_t i16 = 3;
                    uint16_t u16 = 4;
                    int32_t i32 = 5;
                    uint32_t u32 = 6;
                    float f = 7.F;
                    fileIO->write8(i8);
                    fileIO->writeU8(u8);
                    fileIO->write16(i16);
                    fileIO->writeU16(u16);
                    fileIO->write32(i32);
                    fileIO->writeU32(u32);
                    fileIO->writeF32(f);
                    fileIO.reset();

                    fileIO = FileIO::create(fileName, FileMode::Read, fileRead);
                    int8_t i8b = 1;
                    uint8_t u8b = 2;
                    int16_t i16b = 3;
                    uint16_t u16b = 4;
                    int32_t i32b = 5;
                    uint32_t u32b = 6;
                    float fb = 7.F;
                    fileIO->read8(&i8b, 1);
                    fileIO->readU8(&u8b, 1);
                    fileIO->read16(&i16b, 1);
                    fileIO->readU16(&u16b, 1);
                    fileIO->read32(&i32b, 1);
                    fileIO->readU32(&u32b, 1);
                    fileIO->readF32(&fb, 1);
                    TG_ASSERT(i8 == i8b);
                    TG_ASSERT(u8 == u8b);
                    TG_ASSERT(i16 == i16b);
                    TG_ASSERT(u16 == u16b);
                    TG_ASSERT(i32 == i32b);
                    TG_ASSERT(u32 == u32b);
                    TG_ASSERT(f == fb);
                }
                {
                    const std::string fileName = "FileIOTest3";
                    auto fileIO = FileIO::create(fileName, FileMode::Write);
                    uint32_t u32 = 1;
                    TG_ASSERT(!fileIO->hasEndianConversion());
                    fileIO->setEndianConversion(true);
                    TG_ASSERT(fileIO->hasEndianConversion());
                    fileIO->writeU32(u32);
                    fileIO.reset();

                    fileIO = FileIO::create(fileName, FileMode::Read, fileRead);
                    uint32_t u32b = 0;
                    fileIO->readU32(&u32b, 1);
                    TG_ASSERT(u32 != u32b);
                    fileIO.reset();

                    fileIO = FileIO::create(fileName, FileMode::Read, fileRead);
                    fileIO->setEndianConversion(true);
                    u32b = 0;
                    fileIO->readU32(&u32b, 1);
                    TG_ASSERT(u32 == u32b);
                    fileIO.reset();

                    fileIO = FileIO::create(fileName, FileMode::ReadWrite, fileRead);
                    fileIO->setEndianConversion(true);
                    u32b = 0;
                    fileIO->readU32(&u32b, 1);
                    TG_ASSERT(u32 == u32b);
                }
                {
                    auto fileIO = FileIO::createTemp();
                    fileIO->write("Hello world");                    
                }
                try
                {
                    const std::string fileName = "FileIOTest4";
                    auto fileIO = FileIO::create(fileName, FileMode::Read, fileRead);
                    TG_ASSERT(false);
                }
                catch (const std::exception&)
                {}
                //! \bug Why doesn't the read fail with an empty file on Windows?
#if !defined(_WINDOWS)
                try
                {
                    const std::string fileName = "FileIOTest5";
                    auto fileIO = FileIO::create(fileName, FileMode::Write);
                    fileIO.reset();

                    fileIO = FileIO::create(fileName, FileMode::Read, fileRead);
                    uint8_t u8 = 0;
                    fileIO->readU8(&u8, 1);
                    TG_ASSERT(false);
                }
                catch (const std::exception&)
                {}
                try
                {
                    const std::string fileName = "FileIOTest6";
                    auto fileIO = FileIO::create(fileName, FileMode::Write);
                    fileIO.reset();

                    fileIO = FileIO::create(fileName, FileMode::ReadWrite, fileRead);
                    uint8_t u8 = 0;
                    fileIO->readU8(&u8, 1);
                    TG_ASSERT(false);
                }
                catch (const std::exception&)
                {}
#endif
                try
                {
                    const std::string fileName = "FileIOTest7";
                    auto fileIO = FileIO::create(fileName, FileMode::Read, fileRead);
                    fileIO->writeU8(1);
                    TG_ASSERT(false);
                }
                catch (const std::exception&)
                {}
            }
        }
        
        void FileIOTest::_functions()
        {
            {
                const std::string fileName = "FileIOTest8";
                auto fileIO = FileIO::create(fileName, FileMode::Write);
                fileIO->write("Hello world");
                fileIO.reset();

                fileIO = FileIO::create(fileName, FileMode::Read);
                std::string contents = read(fileIO);
                TG_ASSERT(contents == "Hello world");
            }
            {
                const std::string fileName = "FileIOTest9";
                auto fileIO = FileIO::create(fileName, FileMode::Write);
                fileIO->write("# This is a comment\n");
                fileIO->write("Hello\n");
                fileIO->write("# This is another comment\n");
                fileIO->write("world\n");
                fileIO.reset();

                fileIO = FileIO::create(fileName, FileMode::Read);
                char contents[cStringSize];
                readWord(fileIO, contents);
                TG_ASSERT(std::string(contents) == "Hello");
                readWord(fileIO, contents);
                TG_ASSERT(std::string(contents) == "world");
            }
            {
                const std::string fileName = "FileIOTest10";
                auto fileIO = FileIO::create(fileName, FileMode::Write);
                fileIO->write("Hello world");
                fileIO.reset();

                fileIO = FileIO::create(fileName, FileMode::Read);
                char contents[cStringSize];
                readLine(fileIO, contents);
                TG_ASSERT(std::string(contents) == "Hello world");
            }
            {
                const std::string fileName = "FileIOTest11";
                std::vector<std::string> contents;
                contents.push_back("Hello");
                contents.push_back("World");
                writeLines(fileName, contents);
                TG_ASSERT(contents == readLines(fileName));
            }
            {
                const std::string fileName = "FileIOTest12";
                auto fileIO = FileIO::create(fileName, FileMode::Write);
                fileIO->write("Hello world");
                fileIO.reset();

                truncateFile(fileName, 5);
                fileIO = FileIO::create(fileName, FileMode::ReadWrite);
                std::string contents = read(fileIO);
                TG_ASSERT(contents == "Hello");
            }
        }
        
        void FileIOTest::_operators()
        {
            {
                std::string contents = "Hello world";
                FileMemoryRead a((uint8_t*)contents.data(), contents.size());
                FileMemoryRead b((uint8_t*)contents.data(), contents.size());
                TG_ASSERT(a == b);
                b = FileMemoryRead();
                TG_ASSERT(a != b);
            }
        }
    }
}

