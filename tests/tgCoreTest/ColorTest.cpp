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
                const Color1F c;
                TG_ASSERT(c[0] == 0.F);
                TG_ASSERT(c.l == 0.F);
                TG_ASSERT(c.data());
            }
            {
                Color1F c;
                c[0] = .1F;
                TG_ASSERT(c[0] == .1F);
                c.l = .2F;
                TG_ASSERT(c[0] == .2F);
                TG_ASSERT(c.data());
            }
            {
                const Color2F c;
                TG_ASSERT(c[0] == 0.F);
                TG_ASSERT(c[1] == 0.F);
                TG_ASSERT(c.l == 0.F);
                TG_ASSERT(c.a == 0.F);
                TG_ASSERT(c.data());
            }
            {
                Color2F c;
                c[0] = .1F;
                c[1] = .2F;
                TG_ASSERT(c[0] == .1F);
                TG_ASSERT(c[1] == .2F);
                c.l = .2F;
                c.a = .3F;
                TG_ASSERT(c[0] == .2F);
                TG_ASSERT(c[1] == .3F);
                TG_ASSERT(c.data());
            }
            {
                const Color3F c;
                TG_ASSERT(c[0] == 0.F);
                TG_ASSERT(c[1] == 0.F);
                TG_ASSERT(c[2] == 0.F);
                TG_ASSERT(c.r == 0.F);
                TG_ASSERT(c.g == 0.F);
                TG_ASSERT(c.b == 0.F);
                TG_ASSERT(c.data());
            }
            {
                Color3F c;
                c[0] = .1F;
                c[1] = .2F;
                c[2] = .3F;
                TG_ASSERT(c[0] == .1F);
                TG_ASSERT(c[1] == .2F);
                TG_ASSERT(c[2] == .3F);
                c.r = .2F;
                c.g = .3F;
                c.b = .4F;
                TG_ASSERT(c[0] == .2F);
                TG_ASSERT(c[1] == .3F);
                TG_ASSERT(c[2] == .4F);
                TG_ASSERT(c.data());
            }
            {
                const Color4F c;
                TG_ASSERT(c[0] == 0.F);
                TG_ASSERT(c[1] == 0.F);
                TG_ASSERT(c[2] == 0.F);
                TG_ASSERT(c[3] == 0.F);
                TG_ASSERT(c.r == 0.F);
                TG_ASSERT(c.g == 0.F);
                TG_ASSERT(c.b == 0.F);
                TG_ASSERT(c.a == 0.F);
                TG_ASSERT(c.data());
            }
            {
                Color4F c;
                c[0] = .1F;
                c[1] = .2F;
                c[2] = .3F;
                c[3] = .4F;
                TG_ASSERT(c[0] == .1F);
                TG_ASSERT(c[1] == .2F);
                TG_ASSERT(c[2] == .3F);
                TG_ASSERT(c[3] == .4F);
                c.r = .2F;
                c.g = .3F;
                c.b = .4F;
                c.a = .5F;
                TG_ASSERT(c[0] == .2F);
                TG_ASSERT(c[1] == .3F);
                TG_ASSERT(c[2] == .4F);
                TG_ASSERT(c[3] == .5F);
                TG_ASSERT(c.data());
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
            {
                nlohmann::json j;
                const Color1F c(.5F);
                to_json(j, c);
                Color1F c1;
                from_json(j, c1);
                TG_ASSERT(c == c1);
            }
            {
                nlohmann::json j;
                const Color2F c(.5F, 1.F);
                to_json(j, c);
                Color2F c1;
                from_json(j, c1);
                TG_ASSERT(c == c1);
            }
            {
                nlohmann::json j;
                const Color3F c(.25F, .5F, .75F);
                to_json(j, c);
                Color3F c1;
                from_json(j, c1);
                TG_ASSERT(c == c1);
            }
            {
                nlohmann::json j;
                const Color4F c(.25F, .5F, .75F, 1.F);
                to_json(j, c);
                Color4F c1;
                from_json(j, c1);
                TG_ASSERT(c == c1);
            }
        }
    }
}

