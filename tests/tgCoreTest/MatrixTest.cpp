// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/MatrixTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Matrix.h>

#include <sstream>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        MatrixTest::MatrixTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::MatrixTest")
        {}

        MatrixTest::~MatrixTest()
        {}

        std::shared_ptr<MatrixTest> MatrixTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<MatrixTest>(new MatrixTest(context));
        }
        
        void MatrixTest::run()
        {
            _members();
            _functions();
            _operators();
            _serialize();
        }
        
        void MatrixTest::_members()
        {
            {
                const Matrix<2, 2, float> m;
                TG_ASSERT(0.F == m.get(0, 0));
                TG_ASSERT(m.data());
            }
            {
                Matrix<2, 2, float> m;
                TG_ASSERT(0.F == m.get(0, 0));
                m.set(0, 0, 1.F);
                TG_ASSERT(1.F == m.get(0, 0));
                TG_ASSERT(m.data());
            }
            {
                const M33F m;
                TG_ASSERT(1.F == m.get(0, 0));
                TG_ASSERT(m.data());
            }
            {
                M33F m;
                TG_ASSERT(1.F == m.get(0, 0));
                m.set(0, 0, 0.F);
                TG_ASSERT(0.F == m.get(0, 0));
                TG_ASSERT(m.data());
            }
            {
                const M33F m(
                    1.F, 2.F, 3.F,
                    4.F, 5.F, 6.F,
                    7.F, 8.F, 9.F);
                TG_ASSERT(9.F == m.get(2, 2));
            }
            {
                const M44F m;
                TG_ASSERT(1.F == m.get(0, 0));
                TG_ASSERT(m.data());
            }
            {
                M44F m;
                TG_ASSERT(1.F == m.get(0, 0));
                m.set(0, 0, 0.F);
                TG_ASSERT(0.F == m.get(0, 0));
                TG_ASSERT(m.data());
            }
            {
                const M44F m(
                    1.F, 2.F, 3.F, 4.F,
                    5.F, 6.F, 7.F, 8.F,
                    9.F, 10.F, 11.F, 12.F,
                    13.F, 14.F, 15.F, 16.F);
                TG_ASSERT(16.F == m.get(3, 3));
            }
        }

        void MatrixTest::_functions()
        {
            translate(V3F(1.F, 1.F, 1.F));
            rotateX(90.F);
            rotateY(90.F);
            rotateZ(90.F);
            scale(V3F(1.F, 2.F, 3.F));
            ortho(0.F, 1.F, 0.F, 1.F, .1F, 10000.F);
            perspective(60.F, 1.F, .1F, 10000.F);
        }
        
        void MatrixTest::_operators()
        {
            {
                const auto m33 = M33F() * M33F();
                const auto v2 = m33 * V2F(1.F, 2.f);
            }
            {
                const auto m44 = translate(V3F(1.F, 2.F, 3.F)) * rotateX(90.F);
                const auto v3 = m44 * V3F(1.F, 2.F, 3.F);
                const auto v4 = m44 * V4F(1.F, 2.F, 3.F, 1.F);
            }
            {
                M44F a;
                M44F b;
                TG_ASSERT(a == b);
                b.set(0, 0, 0.F);
                TG_ASSERT(a != b);                
            }
        }
        
        void MatrixTest::_serialize()
        {
            {
                const M33F m;
                std::stringstream ss;
                ss << m;
                M33F m1;
                ss >> m1;
                TG_ASSERT(m == m1);
            }
            {
                const M44F m;
                std::stringstream ss;
                ss << m;
                M44F m1;
                ss >> m1;
                TG_ASSERT(m == m1);
            }
            {
                nlohmann::json j;
                const M33F m = translate(V2F(1.F, 2.F));
                to_json(j, m);
                M33F m1;
                from_json(j, m1);
                TG_ASSERT(m == m1);
            }
            {
                nlohmann::json j;
                const M44F m = translate(V3F(1.F, 2.F, 3.F));
                to_json(j, m);
                M44F m1;
                from_json(j, m1);
                TG_ASSERT(m == m1);
                _print(j.dump());
            }
        }
    }
}

