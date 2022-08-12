// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Window.h"

#include "App.h"
#include "Sol.h"

#include <tgGL/Mesh.h>

namespace tg
{
    namespace
    {
        const size_t samples = 16;

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
            "uniform float transition;\n"
            "uniform sampler2D textureSampler;\n"
            "uniform sampler2D textureSamplerB;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    vec4 a = texture(textureSampler, fTexture);\n"
            "    vec4 b = texture(textureSamplerB, fTexture);\n"
            "    fColor.r = a.r * (1.0 - transition) + b.r * transition;\n"
            "    fColor.g = a.g * (1.0 - transition) + b.g * transition;\n"
            "    fColor.b = a.b * (1.0 - transition) + b.b * transition;\n"
            "    fColor.a = a.a + b.a;\n"
            "}\n";
    }

    void Window::_init(const std::shared_ptr<app::App>& app)
    {
        IWindow::_init(app, "sol");

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
        if (auto app = std::dynamic_pointer_cast<App>(_app.lock()))
        {
            const auto& solData = app->getSolData();
            const auto& size = getSize();

            if (solData.a)
            {
                if (gl::doCreate(_buffersA.first, size))
                {
                    gl::OffscreenBufferOptions options;
                    options.colorFormat = image::Format::RGBA;
                    options.colorType = image::Type::Float;
                    options.samples = samples;
                    _buffersA.first = gl::OffscreenBuffer::create(size, options);
                }
                {
                    auto binding = gl::OffscreenBufferBinding(_buffersA.first);
                    solData.a->render(size);
                }
                if (gl::doCreate(_buffersA.second, size))
                {
                    gl::OffscreenBufferOptions options;
                    options.colorFormat = image::Format::RGBA;
                    options.colorType = image::Type::Float;
                    _buffersA.second = gl::OffscreenBuffer::create(size, options);
                }
                glBindFramebuffer(GL_READ_FRAMEBUFFER, _buffersA.first->getID());
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _buffersA.second->getID());
                glBlitFramebuffer(
                    0, 0, size[0], size[1],
                    0, 0, size[0], size[1],
                    GL_COLOR_BUFFER_BIT,
                    GL_NEAREST);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }

            if (solData.b)
            {
                if (gl::doCreate(_buffersB.first, size))
                {
                    gl::OffscreenBufferOptions options;
                    options.colorFormat = image::Format::RGBA;
                    options.colorType = image::Type::Float;
                    options.samples = samples;
                    _buffersB.first = gl::OffscreenBuffer::create(size, options);
                }
                if (gl::doCreate(_buffersB.second, size))
                {
                    gl::OffscreenBufferOptions options;
                    options.colorFormat = image::Format::RGBA;
                    options.colorType = image::Type::Float;
                    _buffersB.second = gl::OffscreenBuffer::create(size, options);
                }
                {
                    auto binding = gl::OffscreenBufferBinding(_buffersB.first);
                    solData.b->render(size);
                }
                glBindFramebuffer(GL_READ_FRAMEBUFFER, _buffersB.first->getID());
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _buffersB.second->getID());
                glBlitFramebuffer(
                    0, 0, size[0], size[1],
                    0, 0, size[0], size[1],
                    GL_COLOR_BUFFER_BIT,
                    GL_NEAREST);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }

            glViewport(0, 0, size[0], size[1]);
            glClearColor(0.F, 0.F, 0.F, 0.F);
            glClear(GL_COLOR_BUFFER_BIT);

            _shader->bind();
            const auto mvp = math::ortho<float>(0.F, size[0], size[1], 0.F, -1.F, 1.F);
            _shader->setUniform("transform.mvp", mvp);
            _shader->setUniform("transition", solData.transition);
            if (_buffersA.second)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, _buffersA.second->getColorID());
                _shader->setUniform("textureSampler", 0);
            }
            if (_buffersB.second)
            {
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, _buffersB.second->getColorID());
                _shader->setUniform("textureSamplerB", 1);
            }

            auto mesh = geom::bbox(math::BBox2f(0.F, 0.F, size[0], size[1]));
            auto vaoVbo = gl::create(mesh, gl::Mesh2DType::V2F_T2F);
            vaoVbo.second->bind();
            vaoVbo.second->draw(GL_TRIANGLES, 0, mesh.triangles.size() * 3);
        }
    }
}
