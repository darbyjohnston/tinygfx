// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/BoxTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Box.h>

#include <sstream>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        BoxTest::BoxTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::BoxTest")
        {}

        BoxTest::~BoxTest()
        {}

        std::shared_ptr<BoxTest> BoxTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<BoxTest>(new BoxTest(context));
        }
        
        void BoxTest::run()
        {
            _members();
            _functions();
            _operators();
            _serialize();
        }
        
        void BoxTest::_members()
        {
            {
                const Box2I b2;
                TG_ASSERT(V2I() == b2.min);
                TG_ASSERT(V2I() == b2.max);
                const Box3F b3;
                TG_ASSERT(V3F() == b3.min);
                TG_ASSERT(V3F() == b3.max);
            }
            {
                const V2I min2(1, 2);
                const V2I max2(3, 4);
                const Box2I b2(min2, max2);
                TG_ASSERT(min2 == b2.min);
                TG_ASSERT(max2 == b2.max);
                TG_ASSERT(1 == b2.x());
                TG_ASSERT(2 == b2.y());
                TG_ASSERT(3 == b2.w());
                TG_ASSERT(3 == b2.h());
                const V3F min3(1.F, 2.F, 3.F);
                const V3F max3(4.F, 5.F, 6.F);
                const Box3F b3(min3, max3);
                TG_ASSERT(min3 == b3.min);
                TG_ASSERT(max3 == b3.max);
                TG_ASSERT(1.F == b3.x());
                TG_ASSERT(2.F == b3.y());
                TG_ASSERT(3.F == b3.z());
                TG_ASSERT(3.F == b3.w());
                TG_ASSERT(3.F == b3.h());
                TG_ASSERT(3.F == b3.d());
            }
            {
                const V2I min2(1, 2);
                const Size2I size2(3, 2);
                const Box2I b2(min2, size2);
                TG_ASSERT(min2 == b2.min);
                TG_ASSERT(V2I(3, 3) == b2.max);
                TG_ASSERT(size2 == b2.size());
                const V2F min2f(1.F, 2.F);
                const Size2F size2f(3.F, 2.F);
                const Box2F b2f(min2f, size2f);
                TG_ASSERT(min2f == b2f.min);
                TG_ASSERT(V2F(4.F, 4.F) == b2f.max);
                TG_ASSERT(size2f == b2f.size());
                const V3F min3(1.F, 2.F, 3.F);
                const Size3F size3(4.F, 5.F, 6.F);
                const Box3F b3(min3, size3);
                TG_ASSERT(min3 == b3.min);
                TG_ASSERT(V3F(5.F, 7.F, 9.F) == b3.max);
                TG_ASSERT(size3 == b3.size());
            }
        }
        
        void BoxTest::_functions()
        {
            {
                const Box3F b(1.F, 2.F, 3.F, 4.F, 5.F, 6.F);
                const V3F c = center(b);
                TG_ASSERT(V3F(3.F, 4.5F, 6.F) == c);
            }
            {
                const Box2F b(1.F, 2.F, 3.F, 4.F);
                const float a = area(b);
                TG_ASSERT(12.F == a);
            }
            {
                const Box3F b(1.F, 2.F, 3.F, 4.F, 5.F, 6.F);
                const float v = volume(b);
                TG_ASSERT(120.F == v);
            }
            {
                const Box2F b(1.F, 2.F, 3.F, 4.F);
                const Box2F b1 = move(b, V2F(-1.F, -2.F));
                TG_ASSERT(Box2F(0.F, 0.F, 3.F, 4.F) == b1);
            }
            {
                const Box2I b(0, 0, 3, 3);
                TG_ASSERT(contains(b, Box2I(0, 0, 1, 1)));
                TG_ASSERT(!contains(b, Box2I(-1, -1, 1, 1)));
                TG_ASSERT(contains(b, V2I(1, 1)));
                TG_ASSERT(!contains(b, V2I(-1, -1)));
            }
            {
                const Box2F b(0.F, 0.F, 2.F, 2.F);
                TG_ASSERT(contains(b, Box2F(0.F, 0.F, 1.F, 1.F)));
                TG_ASSERT(!contains(b, Box2F(-1.F, -1.F, 1.F, 1.F)));
                TG_ASSERT(contains(b, V2F(1.F, 1.F)));
                TG_ASSERT(!contains(b, V2F(-1.F, -1.F)));
            }
            {
                const Box2I b(0, 0, 3, 3);
                TG_ASSERT(intersects(b, Box2I(-1, -1, 2, 2)));
                TG_ASSERT(!intersects(b, Box2I(-2, -2, 2, 2)));
                const Box2I b1 = intersect(b, Box2I(-1, -1, 2, 2));
                TG_ASSERT(Box2I(0, 0, 1, 1) == b1);
            }
            {
                const Box2F b(0.F, 0.F, 2.F, 2.F);
                TG_ASSERT(intersects(b, Box2F(-1.F, -1.F, 2.F, 2.F)));
                TG_ASSERT(!intersects(b, Box2F(-2.F, -2.F, 1.F, 1.F)));
                const Box2F b1 = intersect(b, Box2F(-1.F, -1.F, 2.F, 2.F));
                TG_ASSERT(Box2F(0.F, 0.F, 1.F, 1.F) == b1);
            }
            {
                const Box2I b(1, 2, 3, 4);
                const Box2I b1 = expand(b, Box2I(1, 2, 4, 5));
                const Box2I b2 = expand(b, V2I(4, 5));
                TG_ASSERT(Box2I(1, 2, 4, 5) == b1);
                TG_ASSERT(Box2I(1, 2, 4, 4) == b2);
            }
            {
                const Box2I b(1, 2, 3, 4);
                const Box2I b1 = margin(b, V2I(1, 2));
                const Box2I b2 = margin(b, 1);
                const Box2I b3 = margin(b, 1, 2, 3, 4);
                TG_ASSERT(Box2I(0, 0, 5, 8) == b1);
                TG_ASSERT(Box2I(0, 1, 5, 6) == b2);
                TG_ASSERT(Box2I(0, 0, 7, 10) == b3);
            }
        }
        
        void BoxTest::_operators()
        {
            {
                const Box2I b(1, 2, 3, 4);
                TG_ASSERT(b == Box2I(1, 2, 3, 4));
                TG_ASSERT(b != Box2I(0, 1, 2, 3));
            }
        }
        
        void BoxTest::_serialize()
        {
            {
                const Box2I b(1, 2, 3, 4);
                std::stringstream ss;
                ss << b;
                Box2I b1;
                ss >> b1;
                TG_ASSERT(b == b1);
            }
            {
                const Box2F b(1.F, 2.F, 3.F, 4.F);
                std::stringstream ss;
                ss << b;
                Box2F b1;
                ss >> b1;
                TG_ASSERT(b == b1);
            }
            {
                const Box3F b(1.F, 2.F, 3.F, 4.F, 5.F, 6.F);
                std::stringstream ss;
                ss << b;
                Box3F b1;
                ss >> b1;
                TG_ASSERT(b == b1);
            }
        }
    }
}

