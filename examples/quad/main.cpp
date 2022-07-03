// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgApp/App.h>
#include <tgApp/IWindow.h>

#include <tgGL/Mesh.h>
#include <tgGL/Shader.h>

#include <iostream>

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
            "void main()\n"
            "{\n"
            "    fColor.r = fTexture.x;\n"
            "    fColor.g = fTexture.y;\n"
            "    fColor.b = 0.0;\n"
            "    fColor.a = 1.0;\n"
            "}\n";
    }

    class Window : public app::IWindow
    {
    protected:
        void _init(const std::shared_ptr<app::App>& app)
        {
            IWindow::_init(app, "quad");

            _shader = gl::Shader::create(vertexSource, fragmentSource);
        }

    public:
        static std::shared_ptr<Window> create(const std::shared_ptr<app::App>& app)
        {
            auto out = std::shared_ptr<Window>(new Window);
            out->_init(app);
            return out;
        }

    protected:
        void _resize(const math::Vector2i& size) override
        {
            glViewport(0, 0, size.x, size.y);
        }

        void _paint() override
        {
            glClearColor(0.F, 0.F, 0.F, 0.F);
            glClear(GL_COLOR_BUFFER_BIT);

            _shader->bind();
            const auto& size = getSize();
            const auto mvp = math::ortho<float>(0.F, size.x, size.y, 0.F, -1.F, 1.F);
            _shader->setUniform("transform.mvp", mvp);

            auto mesh = geom::bbox(math::BBox2f(0.F, 0.F, size.x, size.y));
            auto vboVao = gl::create(mesh, gl::Mesh2DType::V2F_T2F);
            vboVao.second->bind();
            vboVao.second->draw(GL_TRIANGLES, 0, mesh.triangles.size() * 3);
        }

    private:
        std::shared_ptr<gl::Shader> _shader;
    };
}

int main(int argc, char* argv[])
{
    int r = 0;
    try
    {
        auto app = tg::app::App::create(argc, argv);
        auto window = tg::Window::create(app);
        window->show();
        r = app->run();
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    return r;
}
