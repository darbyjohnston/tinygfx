// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Window.h"

#include "App.h"

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
            "uniform sampler2D textureSampler;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    fColor = texture(textureSampler, fTexture);\n"
            "}\n";
    }

    void Window::_init(const std::shared_ptr<App>& app)
    {
        IWindow::_init(app, "paint2d");

        const image::Info brushInfo(
            math::Vector2i(128, 128),
            image::Format::RGBA,
            image::Type::Float);
        _brush = image::Image::create(brushInfo);
        float* brushP = reinterpret_cast<float*>(_brush->getData());
        for (int y = 0; y < brushInfo.size.y; ++y)
        {
            for (int x = 0; x < brushInfo.size.x; ++x)
            {
                const math::Vector2f h = math::Vector2f(brushInfo.size) / 2.F;
                const math::Vector2f v(x - h.x, y - h.y);
                const float l = math::length(v);
                *brushP++ = 1.F;
                *brushP++ = 1.F;
                *brushP++ = 1.F;
                *brushP++ = std::max(h.x - l, 0.F) / h.x;
            }
        }
        _brushTexture = gl::Texture::create(brushInfo);
        _brushTexture->copy(_brush);

        _shader = gl::Shader::create(vertexSource, fragmentSource);
    }

    std::shared_ptr<Window> Window::create(const std::shared_ptr<App>& app)
    {
        auto out = std::shared_ptr<Window>(new Window);
        out->_init(app);
        return out;
    }

    void Window::_resize(const math::Vector2i& size)
    {
        {
            gl::OffscreenBufferOptions options;
            options.colorFormat = image::Format::RGBA;
            options.colorType = image::Type::Float;
            _buffers[_currentBuffer] = gl::OffscreenBuffer::create(size, options);

            gl::OffscreenBufferBinding binding(_buffers[_currentBuffer]);

            glViewport(0, 0, size.x, size.y);
            glClearColor(0.F, 0.F, 0.F, 1.F);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        {
            gl::OffscreenBufferOptions options;
            options.colorFormat = image::Format::RGBA;
            options.colorType = image::Type::Float;
            _buffers[_getNextBuffer()] = gl::OffscreenBuffer::create(size, options);
        }
    }

    void Window::_paint()
    {
        const auto& size = getSize();
        glViewport(0, 0, size.x, size.y);
        glClearColor(0.F, 0.F, 0.F, 0.F);
        glClear(GL_COLOR_BUFFER_BIT);

        _shader->bind();
        const auto mvp = math::ortho<float>(0.F, size.x, 0.F, size.y, -1.F, 1.F);
        _shader->setUniform("transform.mvp", mvp);
        
        if (_buffers[_currentBuffer])
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _buffers[_currentBuffer]->getColorID());
            _shader->setUniform("textureSampler", 0);

            const auto& bufferSize = _buffers[_currentBuffer]->getSize();
            auto mesh = geom::bbox(math::BBox2f(0.F, 0.F, bufferSize.x, bufferSize.y));
            auto vaoVbo = gl::create(mesh, gl::Mesh2DType::V2F_T2F);
            vaoVbo.second->bind();
            vaoVbo.second->draw(GL_TRIANGLES, 0, mesh.triangles.size() * 3);
        }
    }

    void Window::_mousePos(const math::Vector2f& pos)
    {
        _mouse = pos;
        switch (_button)
        {
        case 0:
        {
            _paintUpdate();
            repaint();
            break;
        }
        }
    }

    void Window::_mouseButton(int button, int action, int mods)
    {
        switch (action)
        {
        case GLFW_PRESS:
            _button = button;
            switch (_button)
            {
            case 0:
            {
                _paintUpdate();
                repaint();
                break;
            }
            }
            break;
        case GLFW_RELEASE:
            _button = -1;
            break;
        default: break;
        }
    }

    size_t Window::_getNextBuffer() const
    {
        size_t out = _currentBuffer + 1;
        if (out > 1)
        {
            out = 0;
        }
        return out;
    }

    void Window::_paintUpdate()
    {
        const size_t index = _getNextBuffer();
        gl::OffscreenBufferBinding binding(_buffers[index]);

        const auto& bufferSize = _buffers[index]->getSize();
        glViewport(0, 0, bufferSize.x, bufferSize.y);
        glClearColor(0.F, 0.F, 0.F, 0.F);
        glClear(GL_COLOR_BUFFER_BIT);

        _shader->bind();
        const auto mvp = math::ortho<float>(0.F, bufferSize.x, 0.F, bufferSize.y, -1.F, 1.F);
        _shader->setUniform("transform.mvp", mvp);

        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _buffers[_currentBuffer]->getColorID());
            _shader->setUniform("textureSampler", 0);

            auto mesh = geom::bbox(math::BBox2f(0.F, 0.F, bufferSize.x, bufferSize.y));
            auto vaoVbo = gl::create(mesh, gl::Mesh2DType::V2F_T2F);
            vaoVbo.second->bind();
            vaoVbo.second->draw(GL_TRIANGLES, 0, mesh.triangles.size() * 3);
        }

        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _brushTexture->getID());
            _shader->setUniform("textureSampler", 0);

            const auto& size = _brush->getInfo().size;
            auto mesh = geom::bbox(math::BBox2f(
                _mouse.x - size.x / 2.F,
                _mouse.y - size.y / 2.F,
                size.x,
                size.y));
            auto vaoVbo = gl::create(mesh, gl::Mesh2DType::V2F_T2F);
            vaoVbo.second->bind();
            vaoVbo.second->draw(GL_TRIANGLES, 0, mesh.triangles.size() * 3);

            glDisable(GL_BLEND);
        }

        _currentBuffer = index;
    }
}
