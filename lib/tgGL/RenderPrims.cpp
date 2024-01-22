// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGL/RenderPrivate.h>

namespace tg
{
    namespace gl
    {
        void Render::drawRect(
            const core::Box2F& box,
            const core::Color4F& color)
        {
            TG_P();

            p.shaders["rect"]->bind();
            p.shaders["rect"]->setUniform("color", color);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            if (p.vbos["rect"])
            {
                p.vbos["rect"]->copy(convert(mesh(box), p.vbos["rect"]->getType()));
            }
            if (p.vaos["rect"])
            {
                p.vaos["rect"]->bind();
                p.vaos["rect"]->draw(GL_TRIANGLES, 0, p.vbos["rect"]->getSize());
            }
        }
        
        void Render::drawLine(
            const core::V2F& v0,
            const core::V2F& v1,
            const core::Color4F& color,
            const render::LineOptions& options)
        {
            TG_P();

            p.shaders["line"]->bind();
            p.shaders["line"]->setUniform("color", color);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            const core::V2F v2 = core::normalize(v1 - v0);
            const float w = options.width / 2.F;
            const core::V2F v2cw = core::normalize(core::perpCW(v2)) * w;
            const core::V2F v2ccw = core::normalize(core::perpCCW(v2)) * w;
            core::TriMesh2F mesh;
            mesh.v.push_back(v0 + v2ccw);
            mesh.v.push_back(v0 + v2cw);
            mesh.v.push_back(v1 + v2cw);
            mesh.v.push_back(v1 + v2ccw);
            core::Triangle2 triangle;
            triangle.v[0].v = 1;
            triangle.v[1].v = 2;
            triangle.v[2].v = 3;
            mesh.triangles.push_back(triangle);
            triangle;
            triangle.v[0].v = 3;
            triangle.v[1].v = 4;
            triangle.v[2].v = 1;
            mesh.triangles.push_back(triangle);

            if (p.vbos["line"])
            {
                p.vbos["line"]->copy(convert(mesh, p.vbos["line"]->getType()));
            }
            if (p.vaos["line"])
            {
                p.vaos["line"]->bind();
                p.vaos["line"]->draw(GL_TRIANGLES, 0, p.vbos["line"]->getSize());
            }
        }

        void Render::drawMesh(
            const core::TriMesh2F& mesh,
            const core::Color4F& color,
            const core::V2F& pos)
        {
            TG_P();
            const size_t size = mesh.triangles.size();
            if (size > 0)
            {
                p.shaders["mesh"]->bind();
                const auto transform =
                    p.transform *
                    core::translate(core::V3F(pos.x(), pos.y(), 0.F));
                p.shaders["mesh"]->setUniform("transform.mvp", transform);
                p.shaders["mesh"]->setUniform("color", color);

                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                if (!p.vbos["mesh"] || (p.vbos["mesh"] && p.vbos["mesh"]->getSize() < size * 3))
                {
                    p.vbos["mesh"] = gl::VBO::create(size * 3, gl::VBOType::Pos2_F32);
                    p.vaos["mesh"].reset();
                }
                if (p.vbos["mesh"])
                {
                    p.vbos["mesh"]->copy(convert(mesh, gl::VBOType::Pos2_F32));
                }

                if (!p.vaos["mesh"] && p.vbos["mesh"])
                {
                    p.vaos["mesh"] = gl::VAO::create(p.vbos["mesh"]->getType(), p.vbos["mesh"]->getID());
                }
                if (p.vaos["mesh"] && p.vbos["mesh"])
                {
                    p.vaos["mesh"]->bind();
                    p.vaos["mesh"]->draw(GL_TRIANGLES, 0, size * 3);
                }
            }
        }
        
        void Render::drawColorMesh(
            const core::TriMesh2F& mesh,
            const core::Color4F& color,
            const core::V2F& pos)
        {
            TG_P();
            const size_t size = mesh.triangles.size();
            if (size > 0)
            {
                p.shaders["colorMesh"]->bind();
                const auto transform =
                    p.transform *
                    core::translate(core::V3F(pos.x(), pos.y(), 0.F));
                p.shaders["colorMesh"]->setUniform("transform.mvp", transform);
                p.shaders["colorMesh"]->setUniform("color", color);

                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                if (!p.vbos["colorMesh"] || (p.vbos["colorMesh"] && p.vbos["colorMesh"]->getSize() < size * 3))
                {
                    p.vbos["colorMesh"] = gl::VBO::create(size * 3, gl::VBOType::Pos2_F32_Color_F32);
                    p.vaos["colorMesh"].reset();
                }
                if (p.vbos["colorMesh"])
                {
                    p.vbos["colorMesh"]->copy(convert(mesh, gl::VBOType::Pos2_F32_Color_F32));
                }

                if (!p.vaos["colorMesh"] && p.vbos["colorMesh"])
                {
                    p.vaos["colorMesh"] = gl::VAO::create(p.vbos["colorMesh"]->getType(), p.vbos["colorMesh"]->getID());
                }
                if (p.vaos["colorMesh"] && p.vbos["colorMesh"])
                {
                    p.vaos["colorMesh"]->bind();
                    p.vaos["colorMesh"]->draw(GL_TRIANGLES, 0, size * 3);
                }
            }
        }
    }
}

