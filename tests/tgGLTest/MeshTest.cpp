// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGLTest/MeshTest.h>

#include <tgGL/GL.h>
#include <tgGL/Mesh.h>
#include <tgGL/Window.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::gl;

namespace tg
{
    namespace gl_test
    {
        MeshTest::MeshTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::MeshTest")
        {}

        MeshTest::~MeshTest()
        {}

        std::shared_ptr<MeshTest> MeshTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<MeshTest>(new MeshTest(context));
        }
        
        namespace
        {
            std::shared_ptr<Window> createWindow(
                const std::shared_ptr<Context>& context)
            {
                return Window::create(
                    context,
                    "MeshTest",
                    Size2I(100, 100),
                    static_cast<int>(WindowOptions::MakeCurrent));
            }
        }
        
        void MeshTest::run()
        {
            _enums();
            _members();
            _functions();
        }
        
        void MeshTest::_enums()
        {
            TINYGFX_TEST_ENUM(VBOType);
            for (auto i : getVBOTypeEnums())
            {
                _print(Format("{0} byte count: {1}").arg(i).arg(getByteCount(i)));
            }
        }
        
        namespace
        {
            TriMesh3F mesh3F()
            {
                TriMesh3F out;
                V3F min(0.F, 0.F, 0.F);
                V3F max(1.F, 1.F, 0.F);
                out.v.push_back(V3F(min.x(), min.y(), 0.F));
                out.v.push_back(V3F(max.x(), min.y(), 0.F));
                out.v.push_back(V3F(max.x(), max.y(), 0.F));
                out.v.push_back(V3F(min.x(), max.y(), 0.F));
                out.t.push_back(V2F(0.F, 0.F));
                out.t.push_back(V2F(1.F, 0.F));
                out.t.push_back(V2F(1.F, 1.F));
                out.t.push_back(V2F(0.F, 1.F));

                Triangle3 triangle;
                triangle.v[0].v = 1;
                triangle.v[1].v = 2;
                triangle.v[2].v = 3;
                triangle.v[0].t = 1;
                triangle.v[1].t = 2;
                triangle.v[2].t = 3;
                out.triangles.push_back(triangle);
                triangle.v[0].v = 3;
                triangle.v[1].v = 4;
                triangle.v[2].v = 1;
                triangle.v[0].t = 3;
                triangle.v[1].t = 4;
                triangle.v[2].t = 1;
                out.triangles.push_back(triangle);
                
                return out;
            }
        }
        
        void MeshTest::_members()
        {
            if (auto context = _context.lock())
            {
                auto window = createWindow(context);
                {
                    auto mesh = core::mesh(Box2F(0.F, 0.F, 1.F, 1.F));
                    for (auto type : getVBOTypeEnums())
                    {
                        const size_t size = mesh.triangles.size() * 3;
                        auto vbo = VBO::create(size, type);
                        TG_ASSERT(size == vbo->getSize());
                        TG_ASSERT(type == vbo->getType());
                        TG_ASSERT(vbo->getID());
                        auto data = convert(mesh, type);
                        vbo->copy(data);
                        vbo->copy(data, 0, getByteCount(type));
                        auto vao = VAO::create(type, vbo->getID());
                        TG_ASSERT(vao->getID());
                        vao->bind();
                        vao->draw(GL_TRIANGLES, 0, 3);
                    }
                }
            }
        }
        
        void MeshTest::_functions()
        {
            {
                const auto mesh = core::mesh(Box2F(0.F, 0.F, 1.F, 1.F));
                for (auto type : getVBOTypeEnums())
                {
                    auto data = convert(mesh, type);
                    data = convert(mesh, type, RangeSizeT(0, 0));
                }
            }
            {
                const auto mesh = mesh3F();
                for (auto type : getVBOTypeEnums())
                {
                    auto data = convert(mesh, type);
                    data = convert(mesh, type, RangeSizeT(0, 0));
                }
            }
        }
    }
}

