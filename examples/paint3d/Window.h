// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgApp/IWindow.h>

#include <tgGL/OffscreenBuffer.h>
#include <tgGL/Shader.h>

namespace tg
{
    class Mesh;

    //! Window.
    class Window : public app::IWindow
    {
    protected:
        void _init(
            const std::shared_ptr<app::App>&,
            const std::shared_ptr<Mesh>&);

    public:
        static std::shared_ptr<Window> create(
            const std::shared_ptr<app::App>&,
            const std::shared_ptr<Mesh>&);

    protected:
        void _paint() override;
        void _mouseDelta(const math::Vector2f&) override;
        void _mouseButton(int button, int action, int mods) override;

    private:
        math::Vector3f _polarCamera = math::Vector3f(30.F, 30.F, 10);
        int _button = -1;
        std::shared_ptr<Mesh> _mesh;
        std::shared_ptr<gl::OffscreenBuffer> _buffer;
        std::shared_ptr<gl::Shader> _shader3D;
        std::shared_ptr<gl::Shader> _shader2D;
    };
}
