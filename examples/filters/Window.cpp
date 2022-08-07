// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Window.h"

#include "App.h"
#include "Filter.h"

#include <tgGL/Mesh.h>

namespace tg
{
    namespace
    {
        const std::string vertexSource =
            "#version 410\n"
            "\n"
            "in vec3 vPos;\n"
            "in vec2 vTexture;\n"
            "\n"
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
            "\n"
            "out vec4 fColor;\n"
            "\n"
            "uniform sampler2D textureSampler;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    fColor = vec4(0.0, 0.0, 0.0, 0.0);\n"
            "    const int size = 7;\n"
            "    const float w = 1.0 / float(size * size);\n"
            "    for (int j = 0; j < size; ++j)\n"
            "    {\n"
            "        for (int i = 0; i < size; ++i)\n"
            "        {\n"
            "            float u = (i - (size / 2.0)) / 1280.0;\n"
            "            float v = (j - (size / 2.0)) / 720.0;\n"
            "            fColor += texture(textureSampler, vec2(fTexture.x + u, fTexture.y + v)) * w;\n"
            "        }\n"
            "    }\n"
            "}\n";
    }

    void Window::_init(const std::shared_ptr<app::App>& app)
    {
        IWindow::_init(app, "filters");

        auto image = testGrid();
        _texture = gl::Texture::create(image->getInfo());
        _texture->copy(image);

        _shader = gl::Shader::create(vertexSource, fragmentSource);
    }

    std::shared_ptr<Window> Window::create(const std::shared_ptr<app::App>& app)
    {
        auto out = std::shared_ptr<Window>(new Window);
        out->_init(app);
        return out;
    }

    void Window::_paint()
    {
        const auto& size = getSize();
        glViewport(0, 0, size.x, size.y);
        glClearColor(0.F, 0.F, 0.F, 0.F);
        glClear(GL_COLOR_BUFFER_BIT);

        _shader->bind();
        const auto mvp = math::ortho<float>(0.F, size.x, size.y, 0.F, -1.F, 1.F);
        _shader->setUniform("transform.mvp", mvp);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture->getID());
        _shader->setUniform("textureSampler", 0);

        auto mesh = geom::bbox(math::BBox2f(0.F, 0.F, size.x, size.y));
        auto vaoVbo = gl::create(mesh, gl::Mesh2DType::V2F_T2F);
        vaoVbo.second->bind();
        vaoVbo.second->draw(GL_TRIANGLES, 0, mesh.triangles.size() * 3);
    }
}
