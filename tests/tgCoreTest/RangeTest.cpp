// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/RangeTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Range.h>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        RangeTest::RangeTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::RangeTest")
        {}

        RangeTest::~RangeTest()
        {}

        std::shared_ptr<RangeTest> RangeTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<RangeTest>(new RangeTest(context));
        }
        
        void RangeTest::run()
        {
            _members();
            _functions();
        }
        
        void RangeTest::_members()
        {
            {
                const RangeI r;
                TG_ASSERT(0 == r.min());
                TG_ASSERT(0 == r.max());
            }
            {
                const RangeI r(1, 2);
                TG_ASSERT(1 == r.min());
                TG_ASSERT(2 == r.max());
            }
            {
                const RangeI a;
                RangeI b;
                TG_ASSERT(a == b);
                b = RangeI(1, 2);
                TG_ASSERT(a != b);
                TG_ASSERT(a < b);
            }
        }
        
        void RangeTest::_functions()
        {
            {
                TG_ASSERT(contains(RangeI(0, 2), 1));
                TG_ASSERT(!contains(RangeI(0, 2), 3));
            }
            {
                TG_ASSERT(intersects(RangeI(0, 2), RangeI(1, 3)));
                TG_ASSERT(!intersects(RangeI(0, 2), RangeI(3, 4)));
            }
            {
                TG_ASSERT(expand(RangeI(), 2) == RangeI(0, 2));
                TG_ASSERT(expand(RangeI(0, 2), RangeI(1, 3)) == RangeI(0, 3));
            }
        }
    }
}

