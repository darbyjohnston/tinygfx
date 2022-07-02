// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgApp/IWindow.h>

#include <tgGL/Mesh.h>
#include <tgGL/OffscreenBuffer.h>
#include <tgGL/Shader.h>

#include <tgCore/ValueObserver.h>

namespace tg
{
    class App;
    class Mesh;

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
        void _mouseDelta(const math::Vector2f&) override;
        void _mouseButton(int button, int action, int mods) override;
        void _drop(const std::vector<std::string>&) override;

    private:
        void _meshUpdate();
        void _quadUpdate();

        std::shared_ptr<Mesh> _mesh;
        std::shared_ptr<observer::ValueObserver<std::shared_ptr<Mesh> > > _meshObserver;

        math::Vector3f _polarCamera = math::Vector3f(15.F, 45.F, 5);

        int _button = -1;

        std::shared_ptr<gl::VBO> _meshVBO;
        std::shared_ptr<gl::VAO> _meshVAO;
        std::shared_ptr<gl::VBO> _quadVBO;
        std::shared_ptr<gl::VAO> _quadVAO;
        std::shared_ptr<gl::OffscreenBuffer> _buffer;
        std::shared_ptr<gl::Shader> _shader3D;
        std::shared_ptr<gl::Shader> _shader2D;
    };
}
