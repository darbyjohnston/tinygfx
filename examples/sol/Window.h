// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgApp/IWindow.h>

#include <tgGL/Mesh.h>
#include <tgGL/OffscreenBuffer.h>
#include <tgGL/Shader.h>

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
        void _resize(const math::Vector2i& size) override;

        void _paint() override;

    private:
        std::shared_ptr<gl::Shader> _shader;
        std::pair<std::shared_ptr<gl::OffscreenBuffer>,
            std::shared_ptr<gl::OffscreenBuffer> > _buffersA;
        std::pair<std::shared_ptr<gl::OffscreenBuffer>,
            std::shared_ptr<gl::OffscreenBuffer> > _buffersB;
    };
}
