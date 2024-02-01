// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/FileTest.h>

#include <tgCore/Assert.h>
#include <tgCore/File.h>
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
            for (const auto& drive : getDrives())
            {
                _print(Format("Drive: {0}").arg(drive));
            }
            for (auto path : getUserPathEnums())
            {
                _print(Format("{0}: {1}").arg(path).arg(getUserPath(path)));
            }
        }
    }
}

