// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/FileTest.h>

#include <tgCore/Assert.h>
#include <tgCore/File.h>
#include <tgCore/FileIO.h>
#include <tgCore/Format.h>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        FileTest::FileTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::FileTest")
        {}

        FileTest::~FileTest()
        {}

        std::shared_ptr<FileTest> FileTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileTest>(new FileTest(context));
        }
        
        void FileTest::run()
        {
            {
                const std::string fileName = "FileTest";
                auto fileIO = FileIO::create(fileName, FileMode::Write);
                fileIO.reset();
                TG_ASSERT(fileExists(fileName));
                TG_ASSERT(rm(fileName));
            }
            {
                const std::string fileName = "FileTestDir";
                TG_ASSERT(mkdir(fileName));
                TG_ASSERT(rmdir(fileName));
            }
            _print(Format("CWD: {0}").arg(getCWD()));
            _print(Format("Temp dir: {0}").arg(getTempDir()));
            _print(Format("Create temp dir: {0}").arg(createTempDir()));
        }
    }
}

