// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/VectorTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Vector.h>

using namespace tg::math;

namespace tg
{
    namespace core_tests
    {
        VectorTest::VectorTest() :
            ITest("core_tests::VectorTest")
        {}

        std::shared_ptr<VectorTest> VectorTest::create()
        {
            return std::shared_ptr<VectorTest>(new VectorTest);
        }

        void VectorTest::run()
        {
            _ctors();
            _operators();
        }

        void VectorTest::_ctors()
        {
            {
                const Vector2f v(1.F, 2.F);
                TINYGFX_ASSERT(1.F == v.x);
                TINYGFX_ASSERT(2.F == v.y);
            }
            {
                const Vector3f v(1.F, 2.F, 3.F);
                TINYGFX_ASSERT(1.F == v.x);
                TINYGFX_ASSERT(2.F == v.y);
                TINYGFX_ASSERT(3.F == v.z);
            }
            {
                const Vector4f v(1.F, 2.F, 3.F, 4.F);
                TINYGFX_ASSERT(1.F == v.x);
                TINYGFX_ASSERT(2.F == v.y);
                TINYGFX_ASSERT(3.F == v.z);
                TINYGFX_ASSERT(4.F == v.w);
            }
        }

        void VectorTest::_operators()
        {
            {
                const Vector2f a(1.F, 2.F);
                const Vector2f b(2.F, 1.F);
                TINYGFX_ASSERT(a == a);
                TINYGFX_ASSERT(a != b);
            }
            {
                const Vector3f a(1.F, 2.F, 3.F);
                const Vector3f b(3.F, 2.F, 1.F);
                TINYGFX_ASSERT(a == a);
                TINYGFX_ASSERT(a != b);
            }
            {
                const Vector4f a(1.F, 2.F, 3.F, 4.F);
                const Vector4f b(4.F, 3.F, 2.F, 1.F);
                TINYGFX_ASSERT(a == a);
                TINYGFX_ASSERT(a != b);
            }
            {
                Vector2f v(1.F, 2.F);
                v += Vector2f(1.F, 2.F);
                TINYGFX_ASSERT(Vector2f(2.F, 4.F) == v);
                v -= Vector2f(1.F, 2.F);
                TINYGFX_ASSERT(Vector2f(1.F, 2.F) == v);
                v *= Vector2f(2.F, 3.F);
                TINYGFX_ASSERT(Vector2f(2.F, 6.F) == v);
                v /= Vector2f(2.F, 3.F);
                TINYGFX_ASSERT(Vector2f(1.F, 2.F) == v);
                v += 1.F;
                TINYGFX_ASSERT(Vector2f(2.F, 3.F) == v);
                v -= 1.F;
                TINYGFX_ASSERT(Vector2f(1.F, 2.F) == v);
                v *= 2.F;
                TINYGFX_ASSERT(Vector2f(2.F, 4.F) == v);
                v /= 2.F;
                TINYGFX_ASSERT(Vector2f(1.F, 2.F) == v);
            }
            {
                Vector3f v(1.F, 2.F, 3.F);
                v += Vector3f(1.F, 2.F, 3.F);
                TINYGFX_ASSERT(Vector3f(2.F, 4.F, 6.F) == v);
                v -= Vector3f(1.F, 2.F, 3.F);
                TINYGFX_ASSERT(Vector3f(1.F, 2.F, 3.F) == v);
                v *= Vector3f(2.F, 3.F, 4.F);
                TINYGFX_ASSERT(Vector3f(2.F, 6.F, 12.F) == v);
                v /= Vector3f(2.F, 3.F, 4.F);
                TINYGFX_ASSERT(Vector3f(1.F, 2.F, 3.F) == v);
                v += 1.F;
                TINYGFX_ASSERT(Vector3f(2.F, 3.F, 4.F) == v);
                v -= 1.F;
                TINYGFX_ASSERT(Vector3f(1.F, 2.F, 3.F) == v);
                v *= 2.F;
                TINYGFX_ASSERT(Vector3f(2.F, 4.F, 6.F) == v);
                v /= 2.F;
                TINYGFX_ASSERT(Vector3f(1.F, 2.F, 3.F) == v);
            }
            {
                Vector4f v(1.F, 2.F, 3.F, 4.F);
                v += Vector4f(1.F, 2.F, 3.F, 4.F);
                TINYGFX_ASSERT(Vector4f(2.F, 4.F, 6.F, 8.F) == v);
                v -= Vector4f(1.F, 2.F, 3.F, 4.F);
                TINYGFX_ASSERT(Vector4f(1.F, 2.F, 3.F, 4.F) == v);
                v *= Vector4f(2.F, 3.F, 4.F, 5.F);
                TINYGFX_ASSERT(Vector4f(2.F, 6.F, 12.F, 20.F) == v);
                v /= Vector4f(2.F, 3.F, 4.F, 5.F);
                TINYGFX_ASSERT(Vector4f(1.F, 2.F, 3.F, 4.F) == v);
                v += 1.F;
                TINYGFX_ASSERT(Vector4f(2.F, 3.F, 4.F, 5.F) == v);
                v -= 1.F;
                TINYGFX_ASSERT(Vector4f(1.F, 2.F, 3.F, 4.F) == v);
                v *= 2.F;
                TINYGFX_ASSERT(Vector4f(2.F, 4.F, 6.F, 8.F) == v);
                v /= 2.F;
                TINYGFX_ASSERT(Vector4f(1.F, 2.F, 3.F, 4.F) == v);
            }
            {
                Vector2f v = Vector2f(1.F, 2.F) + Vector2f(1.F, 2.F);
                TINYGFX_ASSERT(Vector2f(2.F, 4.F) == v);
                v = v - Vector2f(1.F, 2.F);
                TINYGFX_ASSERT(Vector2f(1.F, 2.F) == v);
                v = v * Vector2f(2.F, 3.F);
                TINYGFX_ASSERT(Vector2f(2.F, 6.F) == v);
                v = v / Vector2f(2.F, 3.F);
                TINYGFX_ASSERT(Vector2f(1.F, 2.F) == v);
                v = v + 1.F;
                TINYGFX_ASSERT(Vector2f(2.F, 3.F) == v);
                v = v - 1.F;
                TINYGFX_ASSERT(Vector2f(1.F, 2.F) == v);
                v = v * 2.F;
                TINYGFX_ASSERT(Vector2f(2.F, 4.F) == v);
                v = v / 2.F;
                TINYGFX_ASSERT(Vector2f(1.F, 2.F) == v);
            }
            {
                Vector3f v = Vector3f(1.F, 2.F, 3.F) + Vector3f(1.F, 2.F, 3.F);
                TINYGFX_ASSERT(Vector3f(2.F, 4.F, 6.F) == v);
                v = v - Vector3f(1.F, 2.F, 3.F);
                TINYGFX_ASSERT(Vector3f(1.F, 2.F, 3.F) == v);
                v = v * Vector3f(2.F, 3.F, 4.F);
                TINYGFX_ASSERT(Vector3f(2.F, 6.F, 12.F) == v);
                v = v / Vector3f(2.F, 3.F, 4.F);
                TINYGFX_ASSERT(Vector3f(1.F, 2.F, 3.F) == v);
                v = v + 1.F;
                TINYGFX_ASSERT(Vector3f(2.F, 3.F, 4.F) == v);
                v = v - 1.F;
                TINYGFX_ASSERT(Vector3f(1.F, 2.F, 3.F) == v);
                v = v * 2.F;
                TINYGFX_ASSERT(Vector3f(2.F, 4.F, 6.F) == v);
                v = v / 2.F;
                TINYGFX_ASSERT(Vector3f(1.F, 2.F, 3.F) == v);
            }
            {
                Vector4f v = Vector4f(1.F, 2.F, 3.F, 4.F) + Vector4f(1.F, 2.F, 3.F, 4.F);
                TINYGFX_ASSERT(Vector4f(2.F, 4.F, 6.F, 8.F) == v);
                v = v - Vector4f(1.F, 2.F, 3.F, 4.F);
                TINYGFX_ASSERT(Vector4f(1.F, 2.F, 3.F, 4.F) == v);
                v = v * Vector4f(2.F, 3.F, 4.F, 5.F);
                TINYGFX_ASSERT(Vector4f(2.F, 6.F, 12.F, 20.F) == v);
                v = v / Vector4f(2.F, 3.F, 4.F, 5.F);
                TINYGFX_ASSERT(Vector4f(1.F, 2.F, 3.F, 4.F) == v);
                v = v + 1.F;
                TINYGFX_ASSERT(Vector4f(2.F, 3.F, 4.F, 5.F) == v);
                v = v - 1.F;
                TINYGFX_ASSERT(Vector4f(1.F, 2.F, 3.F, 4.F) == v);
                v = v * 2.F;
                TINYGFX_ASSERT(Vector4f(2.F, 4.F, 6.F, 8.F) == v);
                v = v / 2.F;
                TINYGFX_ASSERT(Vector4f(1.F, 2.F, 3.F, 4.F) == v);
            }
            {
                std::stringstream ss;
                ss << Vector2f(1.F, 2.F);
                _print(ss.str());
            }
            {
                std::stringstream ss;
                ss << Vector3f(1.F, 2.F, 3.F);
                _print(ss.str());
            }
            {
                std::stringstream ss;
                ss << Vector4f(1.F, 2.F, 3.F, 4.F);
                _print(ss.str());
            }
        }
    }
}
