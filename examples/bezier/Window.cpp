// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Window.h"

#include "App.h"

#include <tgGL/Mesh.h>

namespace tg
{
    void Window::_init(const std::shared_ptr<App>& app)
    {
        IWindow::_init(app, "bezier");

        const auto& size = getSize();
        _bezier.p[0] = math::Vector2f(size.x / 4.F, size.y / 4.F);
        _bezier.p[1] = math::Vector2f(size.x / 4.F, size.y / 4.F * 3.F);
        _bezier.p[2] = math::Vector2f(size.x / 4.F * 3.F, size.y / 4.F * 3.F);
        _bezier.p[3] = math::Vector2f(size.x / 4.F * 3.F, size.y / 4.F);
        _bezier.width = 20.F;

        _render = Render::create();
    }

    std::shared_ptr<Window> Window::create(const std::shared_ptr<App>& app)
    {
        auto out = std::shared_ptr<Window>(new Window);
        out->_init(app);
        return out;
    }

    void Window::_resize(const math::Vector2i& size)
    {}

    void Window::_paint()
    {
        const auto& size = getSize();

        if (gl::doCreate(_buffer, size))
        {
            gl::OffscreenBufferOptions options;
            options.colorFormat = image::Format::RGBA;
            options.colorType = image::Type::Float;
            options.samples = 16;
            _buffer = gl::OffscreenBuffer::create(size, options);
        }

        if (_buffer)
        {
            auto binding = gl::OffscreenBufferBinding(_buffer);

            _render->begin(size);

            _render->setColor(math::Vector4f(.5F, 1.F, .5F, 1.F));
            _render->draw(_bezier);

            _render->setColor(math::Vector4f(1.F, .7F, 0.F, 1.F));
            for (size_t i = 0; i < _bezier.p.size(); ++i)
            {
                Disc disc;
                disc.p = _bezier.p[i];
                disc.radius = 10.F;
                _render->draw(disc);
            }

            _render->end();
        }

        glBindFramebuffer(GL_READ_FRAMEBUFFER, _buffer->getID());
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(
            0, 0, size.x, size.y,
            0, 0, size.x, size.y,
            GL_COLOR_BUFFER_BIT,
            GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Window::_mousePos(const math::Vector2f& pos)
    {
        _mouse = pos;
        switch (_button)
        {
        case 0:
        {
            if (_pt != -1)
            {
                _bezier.p[_pt] = _mouse;
                repaint();
            }
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
                _pt = -1;
                for (size_t i = 0; i < _bezier.p.size(); ++i)
                {
                    if (math::distance(_mouse, _bezier.p[i]) < 10.F)
                    {
                        _pt = i;
                    }
                }
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
}
