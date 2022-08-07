// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgApp/IWindow.h>

#include <tgGL/OffscreenBuffer.h>
#include <tgGL/Shader.h>
#include <tgGL/Texture.h>

namespace tg
{
    //! Window.
    class Window : public app::IWindow
    {
    protected:
        void _init(const std::shared_ptr<app::App>& app);

    public:
        static std::shared_ptr<Window> create(const std::shared_ptr<app::App>& app);

    protected:
        void _paint() override;

    private:
        std::shared_ptr<gl::Texture> _texture;
        std::shared_ptr<gl::Shader> _shader;
        std::shared_ptr<gl::OffscreenBuffer> _buffer;
    };
}
