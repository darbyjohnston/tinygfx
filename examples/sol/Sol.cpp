// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Sol.h"

#include <tgGL/Mesh.h>

#include <tgCore/Math.h>
#include <tgCore/Random.h>

#include <algorithm>

namespace tg
{
    namespace
    {
        const float lineWidth = .1F;

        const std::string vertexSource =
            "#version 410\n"
            "\n"
            "in vec3 vPos;\n"
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
            "}\n";

        const std::string fragmentSource =
            "#version 410\n"
            "\n"
            "out vec4 fColor;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    fColor.r = 0.0;\n"
            "    fColor.g = 0.0;\n"
            "    fColor.b = 0.0;\n"
            "    fColor.a = 1.0;\n"
            "}\n";
    }

    Sol::Sol(float duration) :
        _duration(duration)
    {}

    std::shared_ptr<Sol> Sol::create(float duration)
    {
        return std::shared_ptr<Sol>(new Sol(duration));
    }

    void Sol::tick(float delta)
    {
        _t += delta;
    }

    void Sol::render(const math::Vector2i& size)
    {
        if (size != _size)
        {
            _size = size;

            _pts.clear();
            for (size_t i = 0; i < 50; ++i)
            {
                _pts.push_back(math::Vector2f(
                    _size[0] * math::getRandom(),
                    _size[1] * math::getRandom()));
            }

            _lines.clear();
            for (size_t i = 0; i < _pts.size(); ++i)
            {
                for (size_t j = 0; j < _pts.size(); ++j)
                {
                    if (i != j)
                    {
                        const std::pair<size_t, size_t> line(std::min(i, j), std::max(i, j));
                        const auto it = std::find(_lines.begin(), _lines.end(), line);
                        if (it == _lines.end())
                        {
                            _lines.push_back(line);
                        }
                    }
                }
            }
        }

        glViewport(0, 0, size[0], size[1]);
        glClearColor(1.F, 1.F, 1.F, 0.F);
        glClear(GL_COLOR_BUFFER_BIT);

        if (!_shader)
        {
            _shader = gl::Shader::create(vertexSource, fragmentSource);
        }
        _shader->bind();
        const auto mvp = math::ortho<float>(0.F, size[0], size[1], 0.F, -1.F, 1.F);
        _shader->setUniform("transform.mvp", mvp);

        std::vector<uint8_t> vboData;
        struct VBOData
        {
            float vx;
            float vy;
        };
        vboData.resize(_lines.size() * 2 * 3 * sizeof(VBOData));
        auto* vboP = reinterpret_cast<VBOData*>(vboData.data());
        for (const auto& line : _lines)
        {
            const auto& p0 = _pts[line.first];
            const auto& p1 = _pts[line.second];
            const float l = sqrtf(powf(p1[0] - p0[0], 2) + powf(p1[1] - p0[1], 2));
            const float t = std::min(_t * 100.F, l);
            const math::Vector2f p2(
                p0[0] + (p1[0] - p0[0]) / l * t,
                p0[1] + (p1[1] - p0[1]) / l * t);
            const float a = atan2f(
                p0[1] - p1[1],
                p0[0] - p1[0]);
            const math::Vector2f v0(
                cosf(a + math::pi / 2),
                sinf(a + math::pi / 2));
            const math::Vector2f v1(
                cosf(a - math::pi / 2),
                sinf(a - math::pi / 2));

            vboP[0].vx = p0[0] + v0[0] * lineWidth;
            vboP[0].vy = p0[1] + v0[1] * lineWidth;
            vboP[1].vx = p2[0] + v0[0] * lineWidth;
            vboP[1].vy = p2[1] + v0[1] * lineWidth;
            vboP[2].vx = p2[0] + v1[0] * lineWidth;
            vboP[2].vy = p2[1] + v1[1] * lineWidth;
            vboP += 3;

            vboP[0].vx = p2[0] + v1[0] * lineWidth;
            vboP[0].vy = p2[1] + v1[1] * lineWidth;
            vboP[1].vx = p0[0] + v1[0] * lineWidth;
            vboP[1].vy = p0[1] + v1[1] * lineWidth;
            vboP[2].vx = p0[0] + v0[0] * lineWidth;
            vboP[2].vy = p0[1] + v0[1] * lineWidth;
            vboP += 3;
        }
        auto vbo = gl::VBO::create(_lines.size() * 2 * 3, sizeof(VBOData));
        vbo->copy(vboData);

        auto vao = gl::VAO::create(vbo->getID());
        vao->bind();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        vao->draw(GL_TRIANGLES, 0, _lines.size() * 2 * 3);
    }
}
