// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/FileTest.h>

#include <tgCore/Assert.h>
#include <tgCore/File.h>

#include <sstream>

using namespace tg::file;

namespace tg
{
    namespace core_tests
    {
        FileTest::FileTest() :
            ITest("core_tests::FileTest")
        {}

        std::shared_ptr<FileTest> FileTest::create()
        {
            return std::shared_ptr<FileTest>(new FileTest);
        }

        void FileTest::run()
        {
            {
                std::stringstream ss;
                ss << "Temp dir:" << createTempDir();
                _print(ss.str());
            }
        }
    }
}
