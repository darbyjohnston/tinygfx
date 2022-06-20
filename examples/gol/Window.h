// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgApp/IWindow.h>

#include <tgGL/Mesh.h>
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
        size_t _vboCount = 0;
        std::vector<uint8_t> _vboData;
        std::shared_ptr<gl::VBO> _vbo;
        std::shared_ptr<gl::VAO> _vao;
    };
}
