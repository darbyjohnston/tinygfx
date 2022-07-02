// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/MathTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Math.h>

using namespace tg::math;

namespace tg
{
    namespace core_tests
    {
        MathTest::MathTest() :
            ITest("core_tests::MathTest")
        {}

        std::shared_ptr<MathTest> MathTest::create()
        {
            return std::shared_ptr<MathTest>(new MathTest);
        }

        void MathTest::run()
        {
            {
                TINYGFX_ASSERT(0 == clamp(-1, 0, 1));
                TINYGFX_ASSERT(1 == clamp(2, 0, 1));
            }
            {
                TINYGFX_ASSERT(0.F == lerp(0.F, 0.F, 1.F));
                TINYGFX_ASSERT(1.F == lerp(1.F, 0.F, 1.F));
            }
            {
                for (float i = 0.F; i <= 1.F; i += .1F)
                {
                    std::stringstream ss;
                    ss << "Smoothstep " << i << ": " << smoothStep(i, 0.F, 1.F);
                    _print(ss.str());
                }
                for (double i = 0.0; i <= 1.0; i += 0.1)
                {
                    std::stringstream ss;
                    ss << "Smoothstep " << i << ": " << smoothStep(i, 0.0, 1.0);
                    _print(ss.str());
                }
            }
            {
                TINYGFX_ASSERT(1 == digits(0));
                TINYGFX_ASSERT(1 == digits(1));
                TINYGFX_ASSERT(2 == digits(10));
                TINYGFX_ASSERT(3 == digits(123));
                TINYGFX_ASSERT(1 == digits(-1));
                TINYGFX_ASSERT(2 == digits(-10));
                TINYGFX_ASSERT(3 == digits(-123));
            }
        }
    }
}
