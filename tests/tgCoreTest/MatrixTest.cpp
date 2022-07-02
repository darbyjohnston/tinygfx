// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/MatrixTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Matrix.h>

using namespace tg::math;

namespace tg
{
    namespace core_tests
    {
        MatrixTest::MatrixTest() :
            ITest("core_tests::MatrixTest")
        {}

        std::shared_ptr<MatrixTest> MatrixTest::create()
        {
            return std::shared_ptr<MatrixTest>(new MatrixTest);
        }

        void MatrixTest::run()
        {
            _ctors();
            _transforms();
            _operators();
        }

        void MatrixTest::_ctors()
        {
            {
                const Matrix3x3f m;

                TINYGFX_ASSERT(1.F == m.e[0]);
                TINYGFX_ASSERT(0.F == m.e[1]);
                TINYGFX_ASSERT(0.F == m.e[2]);

                TINYGFX_ASSERT(0.F == m.e[3]);
                TINYGFX_ASSERT(1.F == m.e[4]);
                TINYGFX_ASSERT(0.F == m.e[5]);

                TINYGFX_ASSERT(0.F == m.e[6]);
                TINYGFX_ASSERT(0.F == m.e[7]);
                TINYGFX_ASSERT(1.F == m.e[8]);
            }
            {
                const Matrix3x3f m(
                    0.F, 1.F, 2.F,
                    3.F, 4.F, 5.F,
                    6.F, 7.F, 8.F);

                TINYGFX_ASSERT(0.F == m.e[0]);
                TINYGFX_ASSERT(1.F == m.e[1]);
                TINYGFX_ASSERT(2.F == m.e[2]);

                TINYGFX_ASSERT(3.F == m.e[3]);
                TINYGFX_ASSERT(4.F == m.e[4]);
                TINYGFX_ASSERT(5.F == m.e[5]);

                TINYGFX_ASSERT(6.F == m.e[6]);
                TINYGFX_ASSERT(7.F == m.e[7]);
                TINYGFX_ASSERT(8.F == m.e[8]);
            }
            {
                const Matrix4x4f m;

                TINYGFX_ASSERT(1.F == m.e[0]);
                TINYGFX_ASSERT(0.F == m.e[1]);
                TINYGFX_ASSERT(0.F == m.e[2]);
                TINYGFX_ASSERT(0.F == m.e[3]);

                TINYGFX_ASSERT(0.F == m.e[4]);
                TINYGFX_ASSERT(1.F == m.e[5]);
                TINYGFX_ASSERT(0.F == m.e[6]);
                TINYGFX_ASSERT(0.F == m.e[7]);

                TINYGFX_ASSERT(0.F == m.e[8]);
                TINYGFX_ASSERT(0.F == m.e[9]);
                TINYGFX_ASSERT(1.F == m.e[10]);
                TINYGFX_ASSERT(0.F == m.e[11]);

                TINYGFX_ASSERT(0.F == m.e[12]);
                TINYGFX_ASSERT(0.F == m.e[13]);
                TINYGFX_ASSERT(0.F == m.e[14]);
                TINYGFX_ASSERT(1.F == m.e[15]);
            }
            {
                const Matrix4x4f m(
                    0.F, 1.F, 2.F, 3.F,
                    4.F, 5.F, 6.F, 7.F,
                    8.F, 9.F, 10.F, 11.F,
                    12.F, 13.F, 14.F, 15.F);

                TINYGFX_ASSERT(0.F == m.e[0]);
                TINYGFX_ASSERT(1.F == m.e[1]);
                TINYGFX_ASSERT(2.F == m.e[2]);
                TINYGFX_ASSERT(3.F == m.e[3]);

                TINYGFX_ASSERT(4.F == m.e[4]);
                TINYGFX_ASSERT(5.F == m.e[5]);
                TINYGFX_ASSERT(6.F == m.e[6]);
                TINYGFX_ASSERT(7.F == m.e[7]);

                TINYGFX_ASSERT(8.F == m.e[8]);
                TINYGFX_ASSERT(9.F == m.e[9]);
                TINYGFX_ASSERT(10.F == m.e[10]);
                TINYGFX_ASSERT(11.F == m.e[11]);

                TINYGFX_ASSERT(12.F == m.e[12]);
                TINYGFX_ASSERT(13.F == m.e[13]);
                TINYGFX_ASSERT(14.F == m.e[14]);
                TINYGFX_ASSERT(15.F == m.e[15]);
            }
        }

        void MatrixTest::_transforms()
        {
            {
                const Matrix4x4f m = translate(Vector3f(2.F, 3.F, 4.F));
                TINYGFX_ASSERT(m == Matrix4x4f(
                    1.F, 0.F, 0.F, 0.F,
                    0.F, 1.F, 0.F, 0.F,
                    0.F, 0.F, 1.F, 0.F,
                    2.F, 3.F, 4.F, 1.F));
            }
            {
                const Matrix4x4f m = scale(Vector3f(2.F, 3.F, 4.F));
                TINYGFX_ASSERT(m == Matrix4x4f(
                    2.F, 0.F, 0.F, 0.F,
                    0.F, 3.F, 0.F, 0.F,
                    0.F, 0.F, 4.F, 0.F,
                    0.F, 0.F, 0.F, 1.F));
            }
        }

        void MatrixTest::_operators()
        {
            {
                const Matrix3x3f a;
                const Matrix3x3f b(
                    0.F, 1.F, 2.F,
                    3.F, 4.F, 5.F,
                    6.F, 7.F, 8.F);
                TINYGFX_ASSERT(a == a);
                TINYGFX_ASSERT(a != b);
            }
            {
                const Matrix4x4f a;
                const Matrix4x4f b(
                    0.F, 1.F, 2.F, 3.F,
                    4.F, 5.F, 6.F, 7.F,
                    8.F, 9.F, 10.F, 11.F,
                    12.F, 13.F, 14.F, 15.F);
                TINYGFX_ASSERT(a == a);
                TINYGFX_ASSERT(a != b);
            }
            {
                const Matrix3x3f a(
                    0.F, 1.F, 2.F,
                    3.F, 4.F, 5.F,
                    6.F, 7.F, 8.F);
                const Matrix3x3f b(
                    0.F, 1.F, 2.F,
                    3.F, 4.F, 5.F,
                    6.F, 7.F, 8.F);
                const Matrix3x3f c = a * b;
                TINYGFX_ASSERT(c == Matrix3x3f(
                    15.F, 18.F, 21.F,
                    42.F, 54.F, 66.F,
                    69.F, 90.F, 111.F));
            }
            {
                const Matrix4x4f a(
                    0.F, 1.F, 2.F, 3.F,
                    4.F, 5.F, 6.F, 7.F,
                    8.F, 9.F, 10.F, 11.F,
                    12.F, 13.F, 14.F, 15.F);
                const Matrix4x4f b(
                    0.F, 1.F, 2.F, 3.F,
                    4.F, 5.F, 6.F, 7.F,
                    8.F, 9.F, 10.F, 11.F,
                    12.F, 13.F, 14.F, 15.F);
                const Matrix4x4f c = a * b;
                TINYGFX_ASSERT(c == Matrix4x4f(
                    56.F, 62.F, 68.F, 74.F,
                    152.F, 174.F, 196.F, 218.F,
                    248.F, 286.F, 324.F, 362.F,
                    344.F, 398.F, 452.F, 506.F));
            }
            {
                std::stringstream ss;
                ss << Matrix3x3f();
                _print(ss.str());
            }
            {
                std::stringstream ss;
                ss << Matrix4x4f();
                _print(ss.str());
            }
        }
    }
}
