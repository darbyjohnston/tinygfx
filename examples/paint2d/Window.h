// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgApp/IWindow.h>

#include <tgGL/OffscreenBuffer.h>
#include <tgGL/Shader.h>
#include <tgGL/Texture.h>

#include <array>

namespace tg
{
    class App;

    //! Window.
    class Window : public app::IWindow
    {
    protected:
        void _init(const std::shared_ptr<App>&);

    public:
        static std::shared_ptr<Window> create(const std::shared_ptr<App>&);

    protected:
        void _resize(const math::Vector2i&) override;
        void _paint() override;
        void _mousePos(const math::Vector2f&) override;
        void _mouseButton(int button, int action, int mods) override;

    private:
        size_t _getNextBuffer() const;

        void _paintUpdate();

        std::shared_ptr<image::Image> _brush;
        std::shared_ptr<gl::Texture> _brushTexture;
        std::array<std::shared_ptr<gl::OffscreenBuffer>, 2> _buffers;
        size_t _currentBuffer = 0;
        std::shared_ptr<gl::Shader> _shader;
        math::Vector2f _mouse = math::Vector2f(0.F, 0.F);
        int _button = -1;
    };
}
