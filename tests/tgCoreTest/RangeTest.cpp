// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/RangeTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Range.h>

using namespace tg::math;

namespace tg
{
    namespace core_tests
    {
        RangeTest::RangeTest() :
            ITest("core_tests::RangeTest")
        {}

        std::shared_ptr<RangeTest> RangeTest::create()
        {
            return std::shared_ptr<RangeTest>(new RangeTest);
        }

        void RangeTest::run()
        {
            {
                const auto r = IntRange();
                TINYGFX_ASSERT(0 == r.getMin());
                TINYGFX_ASSERT(0 == r.getMax());
            }
            {
                const auto r = IntRange(1);
                TINYGFX_ASSERT(1 == r.getMin());
                TINYGFX_ASSERT(1 == r.getMax());
            }
            {
                const auto r = IntRange(1, 10);
                TINYGFX_ASSERT(1 == r.getMin());
                TINYGFX_ASSERT(10 == r.getMax());
            }
            {
                auto r = IntRange(1, 10);
                r.zero();
                TINYGFX_ASSERT(0 == r.getMin());
                TINYGFX_ASSERT(0 == r.getMax());
            }
            {
                const auto r = IntRange(1, 10);
                TINYGFX_ASSERT(r.contains(1));
                TINYGFX_ASSERT(r.contains(10));
                TINYGFX_ASSERT(!r.contains(0));
                TINYGFX_ASSERT(!r.contains(11));
            }
            {
                const auto r = IntRange(1, 10);
                TINYGFX_ASSERT(r.intersects(IntRange(0, 1)));
                TINYGFX_ASSERT(r.intersects(IntRange(10, 11)));
                TINYGFX_ASSERT(!r.intersects(IntRange(12, 20)));
            }
            {
                auto r = IntRange(1, 10);
                r.expand(20);
                TINYGFX_ASSERT(IntRange(1, 20) == r);
            }
            {
                auto r = IntRange(1, 10);
                r.expand(IntRange(0, 20));
                TINYGFX_ASSERT(IntRange(0, 20) == r);
            }
            {
                TINYGFX_ASSERT(IntRange(1, 10) == IntRange(1, 10));
                TINYGFX_ASSERT(IntRange(1, 10) != IntRange(0, 11));
                TINYGFX_ASSERT(IntRange(0, 10) < IntRange(1, 11));
            }
        }
    }
}
