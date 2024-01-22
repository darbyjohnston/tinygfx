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
                const Box<1, int> b;
                TG_ASSERT(0 == b.min()[0]);
                TG_ASSERT(0 == b.max()[0]);
            }
            {
                Box<1, int> b;
                b.min()[0] = 1;
                b.max()[0] = 2;
                TG_ASSERT(1 == b.min()[0]);
                TG_ASSERT(2 == b.max()[0]);
            }
            {
                Vector<1, int> min;
                min[0] = 1;
                Vector<1, int> max;
                max[0] = 2;
                Box<1, int> b(min, max);
                TG_ASSERT(1 == b.min()[0]);
                TG_ASSERT(2 == b.max()[0]);
            }
            {
                Vector<1, int> min;
                min[0] = 1;
                Size<1, int> size;
                size[0] = 2;
                Box<1, int> b(min, size);
                TG_ASSERT(1 == b.min()[0]);
                TG_ASSERT(3 == b.max()[0]);
                TG_ASSERT(size == b.size());
            }
            {
                const Box2I b;
                TG_ASSERT(V2I() == b.min());
                TG_ASSERT(V2I() == b.max());
            }
            {
                Box2I b;
                b.min() = V2I(1, 2);
                b.max() = V2I(3, 4);
                TG_ASSERT(V2I(1, 2) == b.min());
                TG_ASSERT(V2I(3, 4) == b.max());
                TG_ASSERT(1 == b.x());
                TG_ASSERT(2 == b.y());
                TG_ASSERT(3 == b.w());
                TG_ASSERT(3 == b.h());
            }
            {
                const Box2I b(V2I(1, 2), V2I(3, 4));
                TG_ASSERT(V2I(1, 2) == b.min());
                TG_ASSERT(V2I(3, 4) == b.max());
            }
            {
                const Box2I b(V2I(1, 2), Size2I(3, 2));
                TG_ASSERT(V2I(1, 2) == b.min());
                TG_ASSERT(V2I(3, 3) == b.max());
                TG_ASSERT(Size2I(3, 2) == b.size());
            }
            {
                const Box2F b(V2F(1.F, 2.F), Size2F(3.F, 2.F));
                TG_ASSERT(V2F(1.F, 2.F) == b.min());
                TG_ASSERT(V2F(4.F, 4.F) == b.max());
                TG_ASSERT(Size2F(3.F, 2.F) == b.size());
            }
            {
                const Box3F b;
                TG_ASSERT(V3F() == b.min());
                TG_ASSERT(V3F() == b.max());
            }
            {
                Box3F b;
                b.min() = V3F(1.F, 2.F, 3.F);
                b.max() = V3F(4.F, 5.F, 6.F);
                TG_ASSERT(V3F(1.F, 2.F, 3.F) == b.min());
                TG_ASSERT(V3F(4.F, 5.F, 6.F) == b.max());
                TG_ASSERT(1.F == b.x());
                TG_ASSERT(2.F == b.y());
                TG_ASSERT(3.F == b.z());
                TG_ASSERT(3.F == b.w());
                TG_ASSERT(3.F == b.h());
                TG_ASSERT(3.F == b.d());
            }
            {
                const Box3F b(V3F(1.F, 2.F, 3.F), V3F(4.F, 5.F, 6.F));
                TG_ASSERT(V3F(1.F, 2.F, 3.F) == b.min());
                TG_ASSERT(V3F(4.F, 5.F, 6.F) == b.max());
            }
            {
                const Box3F b(V3F(1.F, 2.F, 3.F), Size3F(4.F, 5.F, 6.F));
                TG_ASSERT(V3F(1.F, 2.F, 3.F) == b.min());
                TG_ASSERT(V3F(5.F, 7.F, 9.F) == b.max());
                TG_ASSERT(Size3F(4.F, 5.F, 6.F) == b.size());
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

