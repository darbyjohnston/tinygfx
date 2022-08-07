// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include "Render.h"

#include <tgApp/IWindow.h>

#include <tgGL/OffscreenBuffer.h>

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
        Bezier _bezier;
        std::shared_ptr<gl::OffscreenBuffer> _buffer;
        std::shared_ptr<Render> _render;
        math::Vector2f _mouse = math::Vector2f(0.F, 0.F);
        int _button = -1;
        int _pt = -1;
    };
}
