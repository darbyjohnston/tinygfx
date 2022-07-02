// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/BBoxTest.h>

#include <tgCore/Assert.h>
#include <tgCore/BBox.h>

using namespace tg::math;

namespace tg
{
    namespace core_tests
    {
        BBoxTest::BBoxTest() :
            ITest("core_tests::BBoxTest")
        {}

        std::shared_ptr<BBoxTest> BBoxTest::create()
        {
            return std::shared_ptr<BBoxTest>(new BBoxTest);
        }

        void BBoxTest::run()
        {
            _ctors();
            _components();
            _dimensions();
            _intersections();
            _expand();
            _margin();
            _operators();
        }

        void BBoxTest::_ctors()
        {
            {
                const BBox2i b;
                TINYGFX_ASSERT(0 == b.min.x);
                TINYGFX_ASSERT(0 == b.min.y);
                TINYGFX_ASSERT(0 == b.max.x);
                TINYGFX_ASSERT(0 == b.max.y);
            }
            {
                const BBox2f b;
                TINYGFX_ASSERT(0.F == b.min.x);
                TINYGFX_ASSERT(0.F == b.min.y);
                TINYGFX_ASSERT(0.F == b.max.x);
                TINYGFX_ASSERT(0.F == b.max.y);
            }
            {
                const BBox2i b(Vector2i(1, 2));
                TINYGFX_ASSERT(1 == b.min.x);
                TINYGFX_ASSERT(2 == b.min.y);
                TINYGFX_ASSERT(1 == b.max.x);
                TINYGFX_ASSERT(2 == b.max.y);
            }
            {
                const BBox2f b(Vector2f(1.F, 2.F));
                TINYGFX_ASSERT(1.F == b.min.x);
                TINYGFX_ASSERT(2.F == b.min.y);
                TINYGFX_ASSERT(1.F == b.max.x);
                TINYGFX_ASSERT(2.F == b.max.y);
            }
            {
                const BBox2i b(Vector2i(1, 2), Vector2i(3, 4));
                TINYGFX_ASSERT(1 == b.min.x);
                TINYGFX_ASSERT(2 == b.min.y);
                TINYGFX_ASSERT(3 == b.max.x);
                TINYGFX_ASSERT(4 == b.max.y);
            }
            {
                const BBox2f b(Vector2f(1.F, 2.F), Vector2f(3.F, 4.F));
                TINYGFX_ASSERT(1.F == b.min.x);
                TINYGFX_ASSERT(2.F == b.min.y);
                TINYGFX_ASSERT(3.F == b.max.x);
                TINYGFX_ASSERT(4.F == b.max.y);
            }
            {
                const BBox2i b(1, 2, 3, 4);
                TINYGFX_ASSERT(1 == b.min.x);
                TINYGFX_ASSERT(2 == b.min.y);
                TINYGFX_ASSERT(3 == b.max.x);
                TINYGFX_ASSERT(5 == b.max.y);
            }
            {
                const BBox2f b(1.F, 2.F, 3.F, 4.F);
                TINYGFX_ASSERT(1.F == b.min.x);
                TINYGFX_ASSERT(2.F == b.min.y);
                TINYGFX_ASSERT(4.F == b.max.x);
                TINYGFX_ASSERT(6.F == b.max.y);
            }
        }

        void BBoxTest::_components()
        {
            {
                const BBox2i b(1, 2, 3, 4);
                TINYGFX_ASSERT(1 == b.x());
                TINYGFX_ASSERT(2 == b.y());
                TINYGFX_ASSERT(3 == b.w());
                TINYGFX_ASSERT(4 == b.h());
            }
            {
                const BBox2f b(1.F, 2.F, 3.F, 4.F);
                TINYGFX_ASSERT(1.F == b.x());
                TINYGFX_ASSERT(2.F == b.y());
                TINYGFX_ASSERT(3.F == b.w());
                TINYGFX_ASSERT(4.F == b.h());
            }
            {
                TINYGFX_ASSERT(!BBox2i().isValid());
                TINYGFX_ASSERT(!BBox2f().isValid());
            }
            {
                BBox2i b(1, 2, 3, 4);
                b.zero();
                TINYGFX_ASSERT(0 == b.min.x);
                TINYGFX_ASSERT(0 == b.min.y);
                TINYGFX_ASSERT(0 == b.max.x);
                TINYGFX_ASSERT(0 == b.max.y);
            }
            {
                BBox2i b(1.F, 2.F, 3.F, 4.F);
                b.zero();
                TINYGFX_ASSERT(0.F == b.min.x);
                TINYGFX_ASSERT(0.F == b.min.y);
                TINYGFX_ASSERT(0.F == b.max.x);
                TINYGFX_ASSERT(0.F == b.max.y);
            }
        }

        void BBoxTest::_dimensions()
        {
            {
                BBox2i b(1, 2, 3, 4);
                TINYGFX_ASSERT(Vector2i(3, 4) == b.getSize());
                TINYGFX_ASSERT(Vector2i(2, 4) == b.getCenter());
                TINYGFX_ASSERT(12 == b.getArea());
                TINYGFX_ASSERT(3 / static_cast<float>(4) == b.getAspect());
            }
            {
                BBox2f b(1.F, 2.F, 3.F, 4.F);
                TINYGFX_ASSERT(Vector2f(3.F, 4.F) == b.getSize());
                const auto c = b.getCenter();
                TINYGFX_ASSERT(Vector2f(2.5F, 4.F) == c);
                TINYGFX_ASSERT(12.F == b.getArea());
                TINYGFX_ASSERT(3.F / 4.F == b.getAspect());
            }
        }

        void BBoxTest::_intersections()
        {
            {
                TINYGFX_ASSERT(BBox2i(0, 0, 1, 1).contains(BBox2i(0, 0, 1, 1)));
                TINYGFX_ASSERT(!BBox2i(0, 0, 1, 1).contains(BBox2i(1, 1, 1, 1)));
                TINYGFX_ASSERT(!BBox2i(0, 0, 1, 1).contains(BBox2i(-1, -1, 1, 1)));
            }
            {
                TINYGFX_ASSERT(BBox2f(0.F, 0.F, 1.F, 1.F).contains(BBox2f(0.F, 0.F, 1.F, 1.F)));
                TINYGFX_ASSERT(!BBox2f(0.F, 0.F, 1.F, 1.F).contains(BBox2f(1.F, 1.F, 1.F, 1.F)));
                TINYGFX_ASSERT(!BBox2f(0.F, 0.F, 1.F, 1.F).contains(BBox2f(-1.F, -1.F, 1.F, 1.F)));
            }
            {
                TINYGFX_ASSERT(BBox2i(0, 0, 1, 1).intersects(BBox2i(0, 0, 1, 1)));
                TINYGFX_ASSERT(!BBox2i(0, 0, 1, 1).intersects(BBox2i(2, 2, 1, 1)));
                TINYGFX_ASSERT(!BBox2i(0, 0, 1, 1).intersects(BBox2i(-2, -2, 1, 1)));
            }
            {
                TINYGFX_ASSERT(BBox2f(0.F, 0.F, 1.F, 1.F).intersects(BBox2f(0.F, 0.F, 1.F, 1.F)));
                TINYGFX_ASSERT(!BBox2f(0.F, 0.F, 1.F, 1.F).intersects(BBox2f(2.F, 2.F, 1.F, 1.F)));
                TINYGFX_ASSERT(!BBox2f(0.F, 0.F, 1.F, 1.F).intersects(BBox2f(-2.F, -2.F, 1.F, 1.F)));
            }
            {
                TINYGFX_ASSERT(BBox2i(0, 0, 1, 1).intersect(BBox2i(0, 0, 1, 1)) == BBox2i(0, 0, 1, 1));
                TINYGFX_ASSERT(BBox2i(0, 0, 1, 1).intersect(BBox2i(-1, -1, 2, 2)) == BBox2i(0, 0, 1, 1));
                TINYGFX_ASSERT(!BBox2i(BBox2i(0, 0, 1, 1).intersect(BBox2i(2, 2, 1, 1))).isValid());
                TINYGFX_ASSERT(!BBox2i(BBox2i(0, 0, 1, 1).intersect(BBox2i(-2, -2, 1, 1))).isValid());
            }
            {
                TINYGFX_ASSERT(BBox2f(0.F, 0.F, 1.F, 1.F).intersect(BBox2f(0.F, 0.F, 1.F, 1.F)) == BBox2f(0.F, 0.F, 1.F, 1.F));
                TINYGFX_ASSERT(BBox2f(0.F, 0.F, 1.F, 1.F).intersect(BBox2f(-1.F, -1.F, 2.F, 2.F)) == BBox2f(0.F, 0.F, 1.F, 1.F));
                TINYGFX_ASSERT(!BBox2f(BBox2f(0.F, 0.F, 1.F, 1.F).intersect(BBox2f(2.F, 2.F, 1.F, 1.F))).isValid());
                TINYGFX_ASSERT(!BBox2f(BBox2f(0.F, 0.F, 1.F, 1.F).intersect(BBox2f(-2.F, -2.F, 1.F, 1.F))).isValid());
            }
        }

        void BBoxTest::_expand()
        {
            {
                BBox2i b(0, 1, 2, 3);
                b.expand(BBox2i(4, 5, 6, 7));
                TINYGFX_ASSERT(BBox2i(0, 1, 10, 11) == b);
            }
            {
                BBox2f b(0.F, 1.F, 2.F, 3.F);
                b.expand(BBox2f(4.F, 5.F, 6.F, 7.F));
                TINYGFX_ASSERT(BBox2f(0.F, 1.F, 10.F, 11.F) == b);
            }
            {
                BBox2i b(0, 1, 2, 3);
                b.expand(Vector2i(6, 7));
                TINYGFX_ASSERT(BBox2i(0, 1, 7, 7) == b);
            }
            {
                BBox2f b(0.F, 1.F, 2.F, 3.F);
                b.expand(Vector2f(6.F, 7.F));
                TINYGFX_ASSERT(BBox2f(0.F, 1.F, 6.F, 6.F) == b);
            }
        }

        void BBoxTest::_margin()
        {
            {
                TINYGFX_ASSERT(BBox2i(0, 1, 2, 3).margin(Vector2i(1, 2)) == BBox2i(-1, -1, 4, 7));
                TINYGFX_ASSERT(BBox2f(0.F, 1.F, 2.F, 3.F).margin(Vector2f(1.F, 2.F)) == BBox2f(-1.F, -1.F, 4.F, 7.F));
            }
            {
                TINYGFX_ASSERT(BBox2i(0, 1, 2, 3).margin(1) == BBox2i(-1, 0, 4, 5));
                TINYGFX_ASSERT(BBox2f(0.F, 1.F, 2.F, 3.F).margin(1.F) == BBox2f(-1.F, 0.F, 4.F, 5.F));
            }
            {
                const auto b = BBox2i(0, 1, 2, 3).margin(1, 2, 3, 4);
                TINYGFX_ASSERT(BBox2i(0, 1, 2, 3).margin(1, 2, 3, 4) == BBox2i(-1, -1, 6, 9));
                const auto b2 = BBox2f(0.F, 1.F, 2.F, 3.F).margin(1.F, 2.F, 3.F, 4.F);
                TINYGFX_ASSERT(BBox2f(0.F, 1.F, 2.F, 3.F).margin(1.F, 2.F, 3.F, 4.F) == BBox2f(-1.F, -1.F, 6.F, 9.F));
            }
        }

        void BBoxTest::_operators()
        {
            {
                TINYGFX_ASSERT(BBox2i(0, 1, 2, 3) == BBox2i(0, 1, 2, 3));
                TINYGFX_ASSERT(BBox2i(0, 1, 2, 3) != BBox2i(3, 2, 1, 0));
                TINYGFX_ASSERT(BBox2f(0.F, 1.F, 2.F, 3.F) == BBox2f(0.F, 1.F, 2.F, 3.F));
                TINYGFX_ASSERT(BBox2f(0.F, 1.F, 2.F, 3.F) != BBox2f(3.F, 2.F, 1.F, 0.F));
            }
        }
    }
}
