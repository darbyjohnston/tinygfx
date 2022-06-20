// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Window.h"

#include "App.h"
#include "GOL.h"

#include <tgGL/Mesh.h>

namespace tg
{
    namespace
    {
        const int cellSize = 7;
        const int cellBorder = 1;

        const std::string vertexSource =
            "#version 410\n"
            "\n"
            "in vec3 vPos;\n"
            "in vec3 vC;\n"
            "out vec3 fC;\n"
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
            "    fC = vC;\n"
            "}\n";

        const std::string fragmentSource =
            "#version 410\n"
            "\n"
            "in vec3 fC;\n"
            "out vec4 fColor;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    fColor.r = fC.r;\n"
            "    fColor.g = fC.b;\n"
            "    fColor.b = fC.g;\n"
            "    fColor.a = 1.0;\n"
            "}\n";
    }

    void Window::_init(const std::shared_ptr<app::App>& app)
    {
        IWindow::_init(app, "gol");

        _shader = gl::Shader::create(vertexSource, fragmentSource);
    }

    std::shared_ptr<Window> Window::create(const std::shared_ptr<app::App>& app)
    {
        auto out = std::shared_ptr<Window>(new Window);
        out->_init(app);
        return out;
    }

    namespace
    {
        struct VBOData
        {
            float vx;
            float vy;
            float cr;
            float cg;
            float cb;
        };
    }

    void Window::_resize(const math::Vector2i& size)
    {
        glViewport(0, 0, size.x, size.y);

        if (auto app = std::dynamic_pointer_cast<App>(_app.lock()))
        {
            const auto& gol = app->getGOL();
            const auto& golSize = gol->getSize();

            app->getGOL()->resize(math::Vector2i(size.x / cellSize, size.y / cellSize));

            _vboData.resize(golSize.x * golSize.y * 6 * sizeof(VBOData));
            _vbo = gl::VBO::create(golSize.x * golSize.y * 6, sizeof(VBOData));
            _vao = gl::VAO::create(_vbo->getID());
        }
    }

    void Window::_paint()
    {
        glClearColor(0.F, 0.F, 0.F, 0.F);
        glClear(GL_COLOR_BUFFER_BIT);

        if (auto app = std::dynamic_pointer_cast<App>(_app.lock()))
        {
            const auto& gol = app->getGOL();
            const auto& golSize = gol->getSize();
            const auto& golBuffer = gol->getBuffer();

            _shader->bind();
            const auto& size = getSize();
            const auto mvp = math::ortho<float>(0.F, size.x, size.y, 0.F, -1.F, 1.F);
            _shader->setUniform("transform.mvp", mvp);

            _vboCount = 0;
            auto* vboP = reinterpret_cast<VBOData*>(_vboData.data());
            for (math::Vector2i pos(0, 0); pos.y < golSize.y; ++pos.y)
            {
                for (pos.x = 0; pos.x < golSize.x; ++pos.x)
                {
                    const auto& c = golBuffer.get(pos);
                    if (c.alive)
                    {
                        ++_vboCount;

                        const float cx = pos.x / static_cast<float>(golSize.x) * size.x;
                        const float cy = pos.y / static_cast<float>(golSize.y) * size.y;
                        const float cw = 1.F / static_cast<float>(golSize.x) * size.x;
                        const float ch = 1.F / static_cast<float>(golSize.y) * size.y;

                        vboP[0].vx = cx + cellBorder;
                        vboP[0].vy = cy + cellBorder;
                        vboP[0].cr = c.color.x;
                        vboP[0].cg = c.color.y;
                        vboP[0].cb = c.color.z;
                        vboP[1].vx = cx + cw - cellBorder;
                        vboP[1].vy = cy + cellBorder;
                        vboP[1].cr = c.color.x;
                        vboP[1].cg = c.color.y;
                        vboP[1].cb = c.color.z;
                        vboP[2].vx = cx + cw - cellBorder;
                        vboP[2].vy = cy + ch - cellBorder;
                        vboP[2].cr = c.color.x;
                        vboP[2].cg = c.color.y;
                        vboP[2].cb = c.color.z;

                        vboP[3].vx = cx + cw - cellBorder;
                        vboP[3].vy = cy + ch - cellBorder;
                        vboP[3].cr = c.color.x;
                        vboP[3].cg = c.color.y;
                        vboP[3].cb = c.color.z;
                        vboP[4].vx = cx + cellBorder;
                        vboP[4].vy = cy + ch - cellBorder;
                        vboP[4].cr = c.color.x;
                        vboP[4].cg = c.color.y;
                        vboP[4].cb = c.color.z;
                        vboP[5].vx = cx + cellBorder;
                        vboP[5].vy = cy + cellBorder;
                        vboP[5].cr = c.color.x;
                        vboP[5].cg = c.color.y;
                        vboP[5].cb = c.color.z;

                        vboP += 6;
                    }
                }
            }

            _vbo->copy(_vboData);

            _vao->bind();
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)8);
            glEnableVertexAttribArray(1);
            _vao->draw(GL_TRIANGLES, 0, _vboCount * 6);
        }
    }
}
