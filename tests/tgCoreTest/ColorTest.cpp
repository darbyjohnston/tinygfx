// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/ColorTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Color.h>

#include <sstream>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        ColorTest::ColorTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::ColorTest")
        {}

        ColorTest::~ColorTest()
        {}

        std::shared_ptr<ColorTest> ColorTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ColorTest>(new ColorTest(context));
        }
        
        void ColorTest::run()
        {
            _members();
            _operators();
            _serialize();
        }
        
        void ColorTest::_members()
        {
            {
                const Color<5, float> c;
                TG_ASSERT(c[0] == 0.F);
                TG_ASSERT(c[1] == 0.F);
                TG_ASSERT(c[2] == 0.F);
                TG_ASSERT(c[3] == 0.F);
                TG_ASSERT(c[4] == 0.F);
                TG_ASSERT(c.data());
            }
            {
                Color<5, float> c;
                c[0] = .1F;
                c[1] = .2F;
                c[2] = .3F;
                c[3] = .4F;
                c[4] = .5F;
                TG_ASSERT(c[0] == .1F);
                TG_ASSERT(c[1] == .2F);
                TG_ASSERT(c[2] == .3F);
                TG_ASSERT(c[3] == .4F);
                TG_ASSERT(c[4] == .5F);
                TG_ASSERT(c.data());
            }
            {
                const Color1F c1;
                TG_ASSERT(c1[0] == 0.F);
                TG_ASSERT(c1.data());
                const Color2F c2;
                TG_ASSERT(c2[0] == 0.F);
                TG_ASSERT(c2[1] == 0.F);
                TG_ASSERT(c2.data());
                const Color3F c3;
                TG_ASSERT(c3[0] == 0.F);
                TG_ASSERT(c3[1] == 0.F);
                TG_ASSERT(c3[2] == 0.F);
                TG_ASSERT(c3.data());
                const Color4F c4;
                TG_ASSERT(c4[0] == 0.F);
                TG_ASSERT(c4[1] == 0.F);
                TG_ASSERT(c4[2] == 0.F);
                TG_ASSERT(c4[3] == 0.F);
                TG_ASSERT(c4.data());
            }
            {
                const Color1F c1(1.F);
                TG_ASSERT(c1.l == 1.F);
                const Color2F c2(1.F, 1.F);
                TG_ASSERT(c2.l == 1.F);
                TG_ASSERT(c2.a == 1.F);
                const Color3F c3(1.F, 1.F, 1.F);
                TG_ASSERT(c3.r == 1.F);
                TG_ASSERT(c3.g == 1.F);
                TG_ASSERT(c3.b == 1.F);
                const Color4F c4(1.F, 1.F, 1.F, 1.F);
                TG_ASSERT(c4.r == 1.F);
                TG_ASSERT(c4.g == 1.F);
                TG_ASSERT(c4.b == 1.F);
                TG_ASSERT(c4.a == 1.F);
            }
            {
                Color1F c1;
                c1[0] = 1.F;
                TG_ASSERT(c1[0] == 1.F);
                Color2F c2;
                c2[0] = 1.F;
                TG_ASSERT(c2[0] == 1.F);
                Color3F c3;
                c3[0] = 1.F;
                TG_ASSERT(c3[0] == 1.F);
                Color4F c4;
                c4[0] = 1.F;
                TG_ASSERT(c4[0] == 1.F);
            }
        }
        
        void ColorTest::_operators()
        {
            {
                const Color1F c(.5F);
                TG_ASSERT(c == Color1F(.5F));
                TG_ASSERT(c != Color1F(1.F));
            }
        }

        void ColorTest::_serialize()
        {
            {
                const Color1F c(.5F);
                std::stringstream ss;
                ss << c;
                Color1F c1;
                ss >> c1;
                TG_ASSERT(c == c1);
            }
            {
                const Color2F c(.5F, 1.F);
                std::stringstream ss;
                ss << c;
                Color2F c1;
                ss >> c1;
                TG_ASSERT(c == c1);
            }
            {
                const Color3F c(.25F, .5F, .75F);
                std::stringstream ss;
                ss << c;
                Color3F c1;
                ss >> c1;
                TG_ASSERT(c == c1);
            }
            {
                const Color4F c(.25F, .5F, .75F, 1.F);
                std::stringstream ss;
                ss << c;
                Color4F c1;
                ss >> c1;
                TG_ASSERT(c == c1);
            }
        }
    }
}

