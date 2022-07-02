// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/StringTest.h>

#include <tgCore/Assert.h>
#include <tgCore/String.h>

#include <iostream>
#include <sstream>

using namespace tg::string;

namespace tg
{
    namespace core_tests
    {
        StringTest::StringTest() :
            ITest("core_tests::StringTest")
        {}

        std::shared_ptr<StringTest> StringTest::create()
        {
            return std::shared_ptr<StringTest>(new StringTest);
        }

        void StringTest::run()
        {
            _split();
            _case();
            _util();
            _convert();
        }

        void StringTest::_split()
        {
            {
                const auto pieces = split("", '/');
                TINYGFX_ASSERT(0 == pieces.size());
            }
            {
                const auto pieces = split("/", '/');
                TINYGFX_ASSERT(0 == pieces.size());
            }
            {
                const auto pieces = split("a", '/');
                TINYGFX_ASSERT(1 == pieces.size());
                TINYGFX_ASSERT("a" == pieces[0]);
            }
            {
                const auto pieces = split("/a", '/');
                TINYGFX_ASSERT(1 == pieces.size());
                TINYGFX_ASSERT("a" == pieces[0]);
            }
            {
                const auto pieces = split("a/", '/');
                TINYGFX_ASSERT(1 == pieces.size());
                TINYGFX_ASSERT("a" == pieces[0]);
            }
            {
                const auto pieces = split("a/b/c//", '/');
                TINYGFX_ASSERT(3 == pieces.size());
                TINYGFX_ASSERT("a" == pieces[0]);
                TINYGFX_ASSERT("b" == pieces[1]);
                TINYGFX_ASSERT("c" == pieces[2]);
            }
            {
                const auto pieces = split("a/b/c//", '/', true);
                TINYGFX_ASSERT(4 == pieces.size());
                TINYGFX_ASSERT("a" == pieces[0]);
                TINYGFX_ASSERT("b" == pieces[1]);
                TINYGFX_ASSERT("c" == pieces[2]);
                TINYGFX_ASSERT(pieces[3].empty());
            }
            {
                const auto pieces = split("", { '/', '|' });
                TINYGFX_ASSERT(0 == pieces.size());
            }
            {
                const auto pieces = split("|", { '/', '|' });
                TINYGFX_ASSERT(0 == pieces.size());
            }
            {
                const auto pieces = split("a", { '/', '|' });
                TINYGFX_ASSERT(1 == pieces.size());
                TINYGFX_ASSERT("a" == pieces[0]);
            }
            {
                const auto pieces = split("a/b|c||", { '/', '|' });
                TINYGFX_ASSERT(3 == pieces.size());
                TINYGFX_ASSERT("a" == pieces[0]);
                TINYGFX_ASSERT("b" == pieces[1]);
                TINYGFX_ASSERT("c" == pieces[2]);
            }
            {
                const auto pieces = split("a/b|c||", { '/', '|' }, true);
                TINYGFX_ASSERT(4 == pieces.size());
                TINYGFX_ASSERT("a" == pieces[0]);
                TINYGFX_ASSERT("b" == pieces[1]);
                TINYGFX_ASSERT("c" == pieces[2]);
                TINYGFX_ASSERT(pieces[3].empty());
            }
            {
                TINYGFX_ASSERT("a/b/c" == join({ "a", "b", "c" }, "/"));
            }
        }

        void StringTest::_case()
        {
            {
                TINYGFX_ASSERT("ABC" == toUpper("abc"));
                TINYGFX_ASSERT("abc" == toLower("ABC"));
            }
            {
                TINYGFX_ASSERT(compareNoCase("abc", "ABC"));
            }
        }

        void StringTest::_util()
        {
            {
                std::string s = "abc";
                removeTrailingNewlines(s);
                TINYGFX_ASSERT("abc" == s);
                s = "abc\n";
                removeTrailingNewlines(s);
                TINYGFX_ASSERT("abc" == s);
                s = "abc\r";
                removeTrailingNewlines(s);
                TINYGFX_ASSERT("abc" == s);
                s = "abc\n\r";
                removeTrailingNewlines(s);
                TINYGFX_ASSERT("abc" == s);
            }
        }

        void StringTest::_convert()
        {
            {
                TINYGFX_ASSERT("abc" == fromWide(toWide("abc")));
            }
        }
    }
}
