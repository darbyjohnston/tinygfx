// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Render.h"

#include <tgGL/Mesh.h>

#include <tgCore/Math.h>

namespace tg
{
    namespace
    {
        struct VBOData
        {
            float vx;
            float vy;
        };

        const std::string vertexSource =
            "#version 410\n"
            "\n"
            "in vec3 vPos;\n"
            "in vec2 vTexture;\n"
            "out vec2 fTexture;\n"
            "\n"
            "struct Transform\n"
            "{\n"
            "    mat4 mvp;\n"
            "};\n"
            "\n"
            "uniform Transform transform;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_Position = transform.mvp * vec4(vPos, 1.0);\n"
            "    fTexture = vTexture;\n"
            "}\n";

        const std::string fragmentSource =
            "#version 410\n"
            "\n"
            "in vec2 fTexture;\n"
            "out vec4 fColor;\n"
            "\n"
            "uniform vec4 color;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    fColor = color;\n"
            "}\n";
    }

    void Render::_init()
    {
        _shader = gl::Shader::create(vertexSource, fragmentSource);
    }

    Render::Render()
    {}

    std::shared_ptr<Render> Render::create()
    {
        auto out = std::shared_ptr<Render>(new Render);
        out->_init();
        return out;
    }

    void Render::begin(const math::Vector2i& size)
    {
        _size = size;
    }

    void Render::end()
    {
        glViewport(0, 0, _size.x, _size.y);
        glClearColor(0.F, 0.F, 0.F, 1.F);
        glClear(GL_COLOR_BUFFER_BIT);

        _shader->bind();
        const auto mvp = math::ortho<float>(0.F, _size.x, 0.F, _size.y, -1.F, 1.F);
        _shader->setUniform("transform.mvp", mvp);

        size_t triangleCount = 0;
        std::vector<math::SizeTRange> ranges;
        for (const auto& mesh : _meshes)
        {
            ranges.push_back(math::SizeTRange(
                triangleCount,
                triangleCount + mesh.triangles.size() - 1));
            triangleCount += mesh.triangles.size();
        }

        std::vector<uint8_t> vboData;
        vboData.resize(triangleCount * 3 * sizeof(VBOData));
        auto vboP = reinterpret_cast<VBOData*>(vboData.data());
        for (const auto& mesh : _meshes)
        {
            const size_t trianglesSize = mesh.triangles.size();
            for (size_t i = 0; i < trianglesSize; ++i)
            {
                vboP->vx = mesh.v[mesh.triangles[i].v[0] - 1].x;
                vboP->vy = mesh.v[mesh.triangles[i].v[0] - 1].y;
                ++vboP;
                vboP->vx = mesh.v[mesh.triangles[i].v[1] - 1].x;
                vboP->vy = mesh.v[mesh.triangles[i].v[1] - 1].y;
                ++vboP;
                vboP->vx = mesh.v[mesh.triangles[i].v[2] - 1].x;
                vboP->vy = mesh.v[mesh.triangles[i].v[2] - 1].y;
                ++vboP;
            }
        }

        auto vbo = gl::VBO::create(triangleCount * 3, sizeof(VBOData));
        vbo->copy(vboData);

        auto vao = gl::VAO::create(vbo->getID());
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        for (size_t i = 0; i < _meshes.size(); ++i)
        {
            _shader->setUniform("color", _colors[i]);
            const auto& range = ranges[i];
            vao->draw(
                GL_TRIANGLES,
                range.getMin() * 3,
                (range.getMax() - range.getMin() + 1) * 3);
        }

        _meshes.clear();
        _colors.clear();
    }

    void Render::setColor(const math::Vector4f& color)
    {
        _color = color;
    }

    void Render::draw(const Line& line)
    {
        const math::Vector2f v = math::normalize(line.p[1] - line.p[0]);
        const float a = std::atan2(v.y, v.x);
        const math::Vector2f e(
            std::cosf(a + math::pi_2) * line.width / 2.F,
            std::sinf(a + math::pi_2) * line.width / 2.F);

        geom::Mesh2D mesh;
        mesh.v.push_back(line.p[0] + e);
        mesh.v.push_back(line.p[1] + e);
        mesh.v.push_back(line.p[1] - e);
        mesh.v.push_back(line.p[0] - e);
        geom::Mesh2D::Triangle t;
        t.v[0] = 0 + 1;
        t.v[1] = 1 + 1;
        t.v[2] = 2 + 1;
        mesh.triangles.push_back(t);
        t.v[0] = 2 + 1;
        t.v[1] = 3 + 1;
        t.v[2] = 0 + 1;
        mesh.triangles.push_back(t);

        _meshes.push_back(std::move(mesh));
        _colors.push_back(_color);
    }

    void Render::draw(const Polyline& polyline)
    {
        for (size_t i = 1; i < polyline.p.size(); ++i)
        {
            Line line;
            line.p[0] = polyline.p[i - 1];
            line.p[1] = polyline.p[i];
            line.width = polyline.width;
            draw(line);
        }
    }

    void Render::draw(const Bezier& bezier)
    {
        Polyline polyline;
        const size_t resolution = 32;
        for (size_t i = 0; i < resolution; ++i)
        {
            const float v = i / static_cast<float>(resolution - 1);
            const float v_3 = std::powf(v, 3.F);
            const float v_2 = std::powf(v, 2.F);
            polyline.p.push_back(
                bezier.p[0] * (-v_3 + 3.F * v_2 - 3.F * v + 1.F) +
                bezier.p[1] * (3.F * v_3 - 6.F * v_2 + 3.F * v) +
                bezier.p[2] * (-3.F * v_3 + 3.F * v_2) +
                bezier.p[3] * v_3);
        }
        polyline.width = bezier.width;
        draw(polyline);
    }

    void Render::draw(const Disc& disc)
    {
        geom::Mesh2D mesh;
        mesh.v.push_back(disc.p);
        for (size_t i = 0; i < disc.resolution; ++i)
        {
            const float v = i / static_cast<float>(disc.resolution);
            const float r = v * math::pi2;
            mesh.v.push_back(disc.p +
                math::Vector2f(std::cosf(r), std::sinf(r)) * disc.radius);
        }
        for (size_t i = 0; i < disc.resolution - 1; ++i)
        {
            geom::Mesh2D::Triangle t;
            t.v[0] = 0 + 1;
            t.v[1] = 1 + i + 1;
            t.v[2] = 1 + i + 1 + 1;
            mesh.triangles.push_back(t);
        }
        geom::Mesh2D::Triangle t;
        t.v[0] = 0 + 1;
        t.v[1] = 1 + disc.resolution - 1 + 1;
        t.v[2] = 1 + 0 + 1;
        mesh.triangles.push_back(t);

        _meshes.push_back(std::move(mesh));
        _colors.push_back(_color);
    }
}