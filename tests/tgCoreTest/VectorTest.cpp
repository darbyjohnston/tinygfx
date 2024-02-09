// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/VectorTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Vector.h>

#include <sstream>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        VectorTest::VectorTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::VectorTest")
        {}

        VectorTest::~VectorTest()
        {}

        std::shared_ptr<VectorTest> VectorTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<VectorTest>(new VectorTest(context));
        }
        
        void VectorTest::run()
        {
            _members();
            _functions();
            _operators();
            _serialize();
        }
        
        void VectorTest::_members()
        {
            {
                const Vector<1, int> v;
                TG_ASSERT(0 == v[0]);
                TG_ASSERT(v.data());
            }
            {
                Vector<1, int> v;
                v[0] = 1;
                TG_ASSERT(1 == v[0]);
                TG_ASSERT(v.data());
            }
            {
                const V2I v2;
                TG_ASSERT(0 == v2[0]);
                TG_ASSERT(0 == v2[1]);
                TG_ASSERT(v2.data());
                const V3F v3;
                TG_ASSERT(0.F == v3[0]);
                TG_ASSERT(0.F == v3[1]);
                TG_ASSERT(0.F == v3[2]);
                TG_ASSERT(v3.data());
                const V4F v4;
                TG_ASSERT(0.F == v4[0]);
                TG_ASSERT(0.F == v4[1]);
                TG_ASSERT(0.F == v4[2]);
                TG_ASSERT(0.F == v4[3]);
                TG_ASSERT(v4.data());
            }
            {
                V2I v2;
                v2[0] = 1;
                v2[1] = 2;
                TG_ASSERT(1 == v2[0]);
                TG_ASSERT(2 == v2[1]);
                TG_ASSERT(v2.data());
                V3F v3;
                v3[0] = 1.F;
                v3[1] = 2.F;
                v3[2] = 3.F;
                TG_ASSERT(1.F == v3[0]);
                TG_ASSERT(2.F == v3[1]);
                TG_ASSERT(3.F == v3[2]);
                TG_ASSERT(v3.data());
                V4F v4;
                v4[0] = 1.F;
                v4[1] = 2.F;
                v4[2] = 3.F;
                v4[3] = 4.F;
                TG_ASSERT(1.F == v4[0]);
                TG_ASSERT(2.F == v4[1]);
                TG_ASSERT(3.F == v4[2]);
                TG_ASSERT(4.F == v4[3]);
                TG_ASSERT(v4.data());
            }
            {
                const V2I v2(1, 2);
                TG_ASSERT(1 == v2.x);
                TG_ASSERT(2 == v2.y);
                const V3F v3(1.F, 2.F, 3.F);
                TG_ASSERT(1.F == v3.x);
                TG_ASSERT(2.F == v3.y);
                TG_ASSERT(3.F == v3.z);
                const V4F v4(1.F, 2.F, 3.F, 4.F);
                TG_ASSERT(1.F == v4.x);
                TG_ASSERT(2.F == v4.y);
                TG_ASSERT(3.F == v4.z);
                TG_ASSERT(4.F == v4.w);
            }
            {
                const V2F v2(Size2F(1.F, 2.F));
                TG_ASSERT(1.F == v2.x);
                TG_ASSERT(2.F == v2.y);
                const V3F v3(Size3F(1.F, 2.F, 3.F));
                TG_ASSERT(1.F == v3.x);
                TG_ASSERT(2.F == v3.y);
                TG_ASSERT(3.F == v3.z);
            }
            {
                V2I v2;
                v2.x = 1;
                v2.y = 2;
                TG_ASSERT(1 == v2.x);
                TG_ASSERT(2 == v2.y);
                V3F v3;
                v3.x = 1.F;
                v3.y = 2.F;
                v3.z = 3.F;
                TG_ASSERT(1.F == v3.x);
                TG_ASSERT(2.F == v3.y);
                TG_ASSERT(3.F == v3.z);
                V4F v4;
                v4.x = 1.F;
                v4.y = 2.F;
                v4.z = 3.F;
                v4.w = 4.F;
                TG_ASSERT(1.F == v4.x);
                TG_ASSERT(2.F == v4.y);
                TG_ASSERT(3.F == v4.z);
                TG_ASSERT(4.F == v4.w);
            }
        }

        void VectorTest::_functions()
        {
            {
                float l = length(V2F(0.F, 1.F));
                TG_ASSERT(1.F == l);
                l = length(V2F(1.F, 0.F));
                TG_ASSERT(1.F == l);
            }
            {
                V2F v = normalize(V2F(0.F, 2.F));
                TG_ASSERT(length(v) == 1.F);
                v = normalize(V2F(2.F, 0.F));
                TG_ASSERT(length(v) == 1.F);
            }
            {
                float d = dot(V2F(0.F, 1.F), V2F(1.F, 0.F));
                TG_ASSERT(0.F == d);
                d = dot(V2F(0.F, 1.F), V2F(0.F, -1.F));
                TG_ASSERT(-1.F == d);
            }
            {
                V2F v = perpCW(V2F(1.F, 0.F));
                TG_ASSERT(V2F(0.F, -1.F) == v);
                v = perpCCW(V2F(1.F, 0.F));
                TG_ASSERT(V2F(0.F, 1.F) == v);
            }
        }
        
        void VectorTest::_operators()
        {
            {
                V2F v = V2F(1.F, 2.F) + V2F(3.F, 4.F);
                TG_ASSERT(V2F(4.F, 6.F) == v);
                v = V2F(1.F, 2.F) + 1.F;
                TG_ASSERT(V2F(2.F, 3.F) == v);
            }
            {
                V2F v = V2F(3.F, 4.F) - V2F(1.F, 2.F);
                TG_ASSERT(V2F(2.F, 2.F) == v);
                v = V2F(3.F, 4.F) - 1.F;
                TG_ASSERT(V2F(2.F, 3.F) == v);
            }
            {
                TG_ASSERT(V2F(1.F, 2.F) == V2F(1.F, 2.F));
                TG_ASSERT(V2F(1.F, 2.F) != V2F(2.F, 1.F));
            }
        }
        
        void VectorTest::_serialize()
        {
            {
                const V2I v(1, 2);
                std::stringstream ss;
                ss << v;
                V2I v1;
                ss >> v1;
                TG_ASSERT(v == v1);
            }
            {
                const V2F v(1.F, 2.F);
                std::stringstream ss;
                ss << v;
                V2F v1;
                ss >> v1;
                TG_ASSERT(v == v1);
            }
            {
                const V3F v(1.F, 2.F, 3.F);
                std::stringstream ss;
                ss << v;
                V3F v1;
                ss >> v1;
                TG_ASSERT(v == v1);
            }
            {
                const V4F v(1.F, 2.F, 3.F, 4.F);
                std::stringstream ss;
                ss << v;
                V4F v1;
                ss >> v1;
                TG_ASSERT(v == v1);
            }
            {
                nlohmann::json j;
                const V2I v(1, 2);
                to_json(j, v);
                V2I v1;
                from_json(j, v1);
                TG_ASSERT(v == v1);
            }
            {
                nlohmann::json j;
                const V2F v(1.F, 2.F);
                to_json(j, v);
                V2F v1;
                from_json(j, v1);
                TG_ASSERT(v == v1);
            }
            {
                nlohmann::json j;
                const V3F v(1.F, 2.F, 3.F);
                to_json(j, v);
                V3F v1;
                from_json(j, v1);
                TG_ASSERT(v == v1);
            }
            {
                nlohmann::json j;
                const V4F v(1.F, 2.F, 3.F, 4.F);
                to_json(j, v);
                V4F v1;
                from_json(j, v1);
                TG_ASSERT(v == v1);
            }
        }
    }
}

