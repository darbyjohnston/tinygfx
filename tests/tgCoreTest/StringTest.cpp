// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/StringTest.h>

#include <tgCore/Assert.h>
#include <tgCore/String.h>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        StringTest::StringTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::StringTest")
        {}

        StringTest::~StringTest()
        {}

        std::shared_ptr<StringTest> StringTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<StringTest>(new StringTest(context));
        }
        
        void StringTest::run()
        {
            _split();
            _format();
            _compare();
            _convert();
        }
        
        void StringTest::_split()
        {
            {
                TG_ASSERT(
                    split("a,b,c", ',') ==
                    std::vector<std::string>({ "a", "b", "c" }));
                TG_ASSERT(
                    split("a,,c", ',', SplitOptions::DiscardEmpty) ==
                    std::vector<std::string>({ "a", "c" }));
                TG_ASSERT(
                    split("a,,c", ',', SplitOptions::KeepEmpty) ==
                    std::vector<std::string>({ "a", "", "c" }));
            }
            {
                TG_ASSERT(
                    split("a,b.c", { ',', '.' } ) ==
                    std::vector<std::string>({ "a", "b", "c" }));
                TG_ASSERT(
                    split("a,.c", { ',', '.' }, SplitOptions::DiscardEmpty) ==
                    std::vector<std::string>({ "a", "c" }));
                TG_ASSERT(
                    split("a,.c", { ',', '.' }, SplitOptions::KeepEmpty) ==
                    std::vector<std::string>({ "a", "", "c" }));
            }
            {
                TG_ASSERT(join({ "a", "b", "c" }, ',') == "a,b,c");
                TG_ASSERT(join({ "a", "b", "c" }, ",.") == "a,.b,.c");
            }
        }
        
        void StringTest::_format()
        {
            {
                TG_ASSERT(toUpper("abc") == "ABC");
                TG_ASSERT(toLower("ABC") == "abc");
            }
            {
                std::string s = "abc";
                removeTrailingNewlines(s);
                TG_ASSERT("abc" == s);
                s = "abc\n";
                removeTrailingNewlines(s);
                TG_ASSERT("abc" == s);
                s = "abc\n\r";
                removeTrailingNewlines(s);
                TG_ASSERT("abc" == s);
            }
            {
                const std::string s("abcdef");
                TG_ASSERT("abcdef" == elide(s, 6));
                TG_ASSERT("abc..." == elide(s, 3));
                TG_ASSERT("..." == elide(s, 0));
            }
        }
        
        void StringTest::_compare()
        {
            {
                TG_ASSERT(!compare("abc", "ABC", Compare::CaseSensitive));
                TG_ASSERT(compare("abc", "ABC", Compare::CaseInsensitive));
            }
            {
                TG_ASSERT(!contains("abc", "AB", Compare::CaseSensitive));
                TG_ASSERT(contains("abc", "AB", Compare::CaseInsensitive));
            }
        }
        
        void StringTest::_convert()
        {
            {
                const std::string s("abc");
                const std::wstring w = toWide(s);
                TG_ASSERT(s == fromWide(w));
            }
        }
    }
}

