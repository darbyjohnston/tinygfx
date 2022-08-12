// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/BBoxTest.h>

#include <tgCore/Assert.h>
#include <tgCore/BBox2.h>
#include <tgCore/BBox3.h>

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
                const auto& min = b.getMin();
                const auto& max = b.getMax();
                TINYGFX_ASSERT(0 == min[0]);
                TINYGFX_ASSERT(0 == min[1]);
                TINYGFX_ASSERT(0 == max[0]);
                TINYGFX_ASSERT(0 == max[1]);
            }
            {
                const BBox2f b;
                const auto& min = b.getMin();
                const auto& max = b.getMax();
                TINYGFX_ASSERT(0.F == min[0]);
                TINYGFX_ASSERT(0.F == min[1]);
                TINYGFX_ASSERT(0.F == max[0]);
                TINYGFX_ASSERT(0.F == max[1]);
            }
            {
                const BBox2i b(Vector2i(1, 2));
                const auto& min = b.getMin();
                const auto& max = b.getMax();
                TINYGFX_ASSERT(1 == min[0]);
                TINYGFX_ASSERT(2 == min[1]);
                TINYGFX_ASSERT(1 == max[0]);
                TINYGFX_ASSERT(2 == max[1]);
            }
            {
                const BBox2f b(Vector2f(1.F, 2.F));
                const auto& min = b.getMin();
                const auto& max = b.getMax();
                TINYGFX_ASSERT(1.F == min[0]);
                TINYGFX_ASSERT(2.F == min[1]);
                TINYGFX_ASSERT(1.F == max[0]);
                TINYGFX_ASSERT(2.F == max[1]);
            }
            {
                const BBox2i b(Vector2i(1, 2), Vector2i(3, 4));
                const auto& min = b.getMin();
                const auto& max = b.getMax();
                TINYGFX_ASSERT(1 == min[0]);
                TINYGFX_ASSERT(2 == min[1]);
                TINYGFX_ASSERT(3 == max[0]);
                TINYGFX_ASSERT(4 == max[1]);
            }
            {
                const BBox2f b(Vector2f(1.F, 2.F), Vector2f(3.F, 4.F));
                const auto& min = b.getMin();
                const auto& max = b.getMax();
                TINYGFX_ASSERT(1.F == min[0]);
                TINYGFX_ASSERT(2.F == min[1]);
                TINYGFX_ASSERT(3.F == max[0]);
                TINYGFX_ASSERT(4.F == max[1]);
            }
            {
                const BBox2i b(1, 2, 3, 4);
                const auto& min = b.getMin();
                const auto& max = b.getMax();
                TINYGFX_ASSERT(1 == min[0]);
                TINYGFX_ASSERT(2 == min[1]);
                TINYGFX_ASSERT(3 == max[0]);
                TINYGFX_ASSERT(5 == max[1]);
            }
            {
                const BBox2f b(1.F, 2.F, 3.F, 4.F);
                const auto& min = b.getMin();
                const auto& max = b.getMax();
                TINYGFX_ASSERT(1.F == min[0]);
                TINYGFX_ASSERT(2.F == min[1]);
                TINYGFX_ASSERT(4.F == max[0]);
                TINYGFX_ASSERT(6.F == max[1]);
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
        }

        void BBoxTest::_dimensions()
        {
            {
                BBox2i b(1, 2, 3, 4);
                const Vector2i s = getSize(b);
                TINYGFX_ASSERT(Vector2i(3, 4) == s);
                const Vector2i c = getCenter(b);
                TINYGFX_ASSERT(Vector2i(2, 4) == c);
                TINYGFX_ASSERT(12 == getArea(b));
                TINYGFX_ASSERT(3 / static_cast<float>(4) == getAspect(b));
            }
            {
                BBox2f b(1.F, 2.F, 3.F, 4.F);
                TINYGFX_ASSERT(Vector2f(3.F, 4.F) == getSize(b));
                const auto c = getCenter(b);
                TINYGFX_ASSERT(Vector2f(2.5F, 4.F) == c);
                TINYGFX_ASSERT(12.F == getArea(b));
                TINYGFX_ASSERT(3.F / 4.F == getAspect(b));
            }
        }

        void BBoxTest::_intersections()
        {
            {
                TINYGFX_ASSERT(contains(BBox2i(0, 0, 1, 1), BBox2i(0, 0, 1, 1)));
                TINYGFX_ASSERT(!contains(BBox2i(0, 0, 1, 1), BBox2i(1, 1, 1, 1)));
                TINYGFX_ASSERT(!contains(BBox2i(0, 0, 1, 1), BBox2i(-1, -1, 1, 1)));
            }
            {
                TINYGFX_ASSERT(contains(BBox2f(0.F, 0.F, 1.F, 1.F), BBox2f(0.F, 0.F, 1.F, 1.F)));
                TINYGFX_ASSERT(!contains(BBox2f(0.F, 0.F, 1.F, 1.F), BBox2f(1.F, 1.F, 1.F, 1.F)));
                TINYGFX_ASSERT(!contains(BBox2f(0.F, 0.F, 1.F, 1.F), BBox2f(-1.F, -1.F, 1.F, 1.F)));
            }
            {
                TINYGFX_ASSERT(intersects(BBox2i(0, 0, 1, 1), BBox2i(0, 0, 1, 1)));
                TINYGFX_ASSERT(!intersects(BBox2i(0, 0, 1, 1), BBox2i(2, 2, 1, 1)));
                TINYGFX_ASSERT(!intersects(BBox2i(0, 0, 1, 1), BBox2i(-2, -2, 1, 1)));
            }
            {
                TINYGFX_ASSERT(intersects(BBox2f(0.F, 0.F, 1.F, 1.F), BBox2f(0.F, 0.F, 1.F, 1.F)));
                TINYGFX_ASSERT(!intersects(BBox2f(0.F, 0.F, 1.F, 1.F), BBox2f(2.F, 2.F, 1.F, 1.F)));
                TINYGFX_ASSERT(!intersects(BBox2f(0.F, 0.F, 1.F, 1.F), BBox2f(-2.F, -2.F, 1.F, 1.F)));
            }
            {
                TINYGFX_ASSERT(intersect(BBox2i(0, 0, 1, 1), BBox2i(0, 0, 1, 1)) == BBox2i(0, 0, 1, 1));
                TINYGFX_ASSERT(intersect(BBox2i(0, 0, 1, 1), BBox2i(-1, -1, 2, 2)) == BBox2i(0, 0, 1, 1));
                TINYGFX_ASSERT(!intersect(BBox2i(0, 0, 1, 1), BBox2i(2, 2, 1, 1)).isValid());
                TINYGFX_ASSERT(!intersect(BBox2i(0, 0, 1, 1), BBox2i(-2, -2, 1, 1)).isValid());
            }
            {
                TINYGFX_ASSERT(intersect(BBox2f(0.F, 0.F, 1.F, 1.F), BBox2f(0.F, 0.F, 1.F, 1.F)) == BBox2f(0.F, 0.F, 1.F, 1.F));
                TINYGFX_ASSERT(intersect(BBox2f(0.F, 0.F, 1.F, 1.F), BBox2f(-1.F, -1.F, 2.F, 2.F)) == BBox2f(0.F, 0.F, 1.F, 1.F));
                TINYGFX_ASSERT(!intersect(BBox2f(0.F, 0.F, 1.F, 1.F), BBox2f(2.F, 2.F, 1.F, 1.F)).isValid());
                TINYGFX_ASSERT(!intersect(BBox2f(0.F, 0.F, 1.F, 1.F), BBox2f(-2.F, -2.F, 1.F, 1.F)).isValid());
            }
        }

        void BBoxTest::_expand()
        {
            {
                const BBox2i b = expand(BBox2i(0, 1, 2, 3), BBox2i(4, 5, 6, 7));
                TINYGFX_ASSERT(BBox2i(0, 1, 10, 11) == b);
            }
            {
                const BBox2f b = expand(BBox2f(0.F, 1.F, 2.F, 3.F), BBox2f(4.F, 5.F, 6.F, 7.F));
                TINYGFX_ASSERT(BBox2f(0.F, 1.F, 10.F, 11.F) == b);
            }
            {
                const BBox2i b = expand(BBox2i(0, 1, 2, 3), Vector2i(6, 7));
                TINYGFX_ASSERT(BBox2i(0, 1, 7, 7) == b);
            }
            {
                const BBox2f b = expand(BBox2f(0.F, 1.F, 2.F, 3.F), Vector2f(6.F, 7.F));
                TINYGFX_ASSERT(BBox2f(0.F, 1.F, 6.F, 6.F) == b);
            }
        }

        void BBoxTest::_margin()
        {
            {
                const BBox2i b = margin(BBox2i(0, 1, 2, 3), Vector2i(1, 2));
                const BBox2i b2 = BBox2i(-1, -1, 4, 7);
                TINYGFX_ASSERT(b == b2);
            }
            {
                const BBox2f b = margin(BBox2f(0.F, 1.F, 2.F, 3.F), Vector2f(1.F, 2.F));
                TINYGFX_ASSERT(b == BBox2f(-1.F, -1.F, 4.F, 7.F));
            }
            {
                const BBox2i b = margin(BBox2i(0, 1, 2, 3), 1);
                TINYGFX_ASSERT(b == BBox2i(-1, 0, 4, 5));
            }
            {
                const BBox2f b = margin(BBox2f(0.F, 1.F, 2.F, 3.F), 1.F);
                TINYGFX_ASSERT(b == BBox2f(-1.F, 0.F, 4.F, 5.F));
            }
            {
                const auto b = margin(BBox2i(0, 1, 2, 3), 1, 2, 3, 4);
                TINYGFX_ASSERT(b == BBox2i(-1, -1, 6, 9));
            }
            {
                const auto b = margin(BBox2f(0.F, 1.F, 2.F, 3.F), 1.F, 2.F, 3.F, 4.F);
                TINYGFX_ASSERT(b == BBox2f(-1.F, -1.F, 6.F, 9.F));
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
