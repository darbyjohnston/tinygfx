// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/SizeTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Size.h>

#include <sstream>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        SizeTest::SizeTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::SizeTest")
        {}

        SizeTest::~SizeTest()
        {}

        std::shared_ptr<SizeTest> SizeTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<SizeTest>(new SizeTest(context));
        }
        
        void SizeTest::run()
        {
            _members();
            _functions();
            _operators();
            _serialize();
        }
        
        void SizeTest::_members()
        {
            {
                const Size<1, int> s;
                TG_ASSERT(0 == s[0]);
                TG_ASSERT(s.data());
                TG_ASSERT(!s.isValid());
            }
            {
                Size<1, int> s;
                s[0] = 1;
                TG_ASSERT(1 == s[0]);
                TG_ASSERT(s.data());
                TG_ASSERT(s.isValid());
            }
            {
                const Size2I s;
                TG_ASSERT(0 == s[0]);
                TG_ASSERT(0 == s[1]);
                TG_ASSERT(0 == s.w());
                TG_ASSERT(0 == s.h());
                TG_ASSERT(s.data());
                TG_ASSERT(!s.isValid());
            }
            {
                Size2I s;
                s[0] = 1;
                s[1] = 2;
                TG_ASSERT(1 == s[0]);
                TG_ASSERT(2 == s[1]);
                TG_ASSERT(s.data());
                TG_ASSERT(s.isValid());
                s.w() = 3;
                s.h() = 4;
                TG_ASSERT(3 == s[0]);
                TG_ASSERT(4 == s[1]);
            }
            {
                const Size3F s;
                TG_ASSERT(0.F == s[0]);
                TG_ASSERT(0.F == s[1]);
                TG_ASSERT(0.F == s[2]);
                TG_ASSERT(0.F == s.w());
                TG_ASSERT(0.F == s.h());
                TG_ASSERT(0.F == s.d());
                TG_ASSERT(s.data());
                TG_ASSERT(!s.isValid());
            }
            {
                Size3F s;
                s[0] = 1.F;
                s[1] = 2.F;
                s[2] = 3.F;
                TG_ASSERT(1.F == s[0]);
                TG_ASSERT(2.F == s[1]);
                TG_ASSERT(3.F == s[2]);
                TG_ASSERT(s.data());
                TG_ASSERT(s.isValid());
                s.w() = 4.F;
                s.h() = 5.F;
                s.d() = 6.F;
                TG_ASSERT(4.F == s[0]);
                TG_ASSERT(5.F == s[1]);
                TG_ASSERT(6.F == s[2]);
            }
        }
        
        void SizeTest::_functions()
        {
            {
                const Size2I s(2, 1);
                TG_ASSERT(2.F == aspectRatio(s));
            }
            {
                const Size2F s(2.F, 1.F);
                TG_ASSERT(2.F == aspectRatio(s));
            }
            {
                const Size2F s(1.F, 2.F);
                TG_ASSERT(2.F == area(s));
            }
            {
                const Size3F s(1.F, 2.F, 3.F);
                TG_ASSERT(6.F == volume(s));
            }
        }
        
        void SizeTest::_operators()
        {
            {
                const Size2I s(1, 2);
                const Size2I s2 = s + 1;
                const Size2I s3 = s - 1;
                TG_ASSERT(Size2I(2, 3) == s2);
                TG_ASSERT(Size2I(0, 1) == s3);
            }
            {
                const Size2I s(1, 2);
                TG_ASSERT(s == Size2I(1, 2));
                TG_ASSERT(s != Size2I(2, 1));
            }
        }
        
        void SizeTest::_serialize()
        {
            {
                const Size2I s(1, 2);
                std::stringstream ss;
                ss << s;
                Size2I s1;
                ss >> s1;
                TG_ASSERT(s == s1);
            }
            {
                const Size2F s(1.F, 2.F);
                std::stringstream ss;
                ss << s;
                Size2F s1;
                ss >> s1;
                TG_ASSERT(s == s1);
            }
            {
                const Size3F s(1.F, 2.F, 3.F);
                std::stringstream ss;
                ss << s;
                Size3F s1;
                ss >> s1;
                TG_ASSERT(s == s1);
            }
        }
    }
}

