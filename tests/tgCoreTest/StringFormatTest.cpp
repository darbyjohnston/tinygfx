// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/StringFormatTest.h>

#include <tgCore/Assert.h>
#include <tgCore/StringFormat.h>

using namespace tg::string;

namespace tg
{
    namespace core_tests
    {
        StringFormatTest::StringFormatTest() :
            ITest("core_tests::StringFormatTest")
        {}

        std::shared_ptr<StringFormatTest> StringFormatTest::create()
        {
            return std::shared_ptr<StringFormatTest>(new StringFormatTest);
        }

        void StringFormatTest::run()
        {
            {
                const std::string s = Format("");
                TINYGFX_ASSERT(s.empty());
            }
            {
                const std::string s = Format("abc");
                TINYGFX_ASSERT("abc" == s);
            }
            {
                const std::string s = Format("{0}{1}{2}").arg("a").arg("b").arg("c");
                TINYGFX_ASSERT("abc" == s);
            }
            {
                const std::string s = Format("{0}{1}{2}").arg(1).arg(2).arg(3);
                TINYGFX_ASSERT("123" == s);
            }
            {
                const std::string s = Format("{0}").arg(1.0F, 2);
                TINYGFX_ASSERT("1.00" == s);
            }
            {
                const std::string s = Format("{0}").arg(1.0, 2);
                TINYGFX_ASSERT("1.00" == s);
            }
            {
                const auto f = Format("").arg(1);
                TINYGFX_ASSERT(f.hasError());
                std::stringstream ss;
                ss << "String format error: " << f.getError();
                _print(ss.str());
            }
            {
                const auto f = Format("{0}{0}").arg(0).arg(1);
                TINYGFX_ASSERT(f.hasError());
                std::stringstream ss;
                ss << "String format error: " << f.getError();
                _print(ss.str());
            }
        }
    }
}
