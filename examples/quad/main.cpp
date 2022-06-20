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
            glClearColor(0.F, 0.F, 1.F, 0.F);
            glClear(GL_COLOR_BUFFER_BIT);

            _shader->bind();
            const auto& size = getSize();
            const auto mvp = math::ortho<float>(0.F, size.x, size.y, 0.F, -1.F, 1.F);
            _shader->setUniform("transform.mvp", mvp);

            std::vector<uint8_t> vboData;
            struct VBOData
            {
                float vx;
                float vy;
                uint16_t tx;
                uint16_t ty;
            };
            vboData.resize(4 * sizeof(VBOData));
            auto* vboP = reinterpret_cast<VBOData*>(vboData.data());
            vboP[0].vx = 0.F;
            vboP[0].vy = 0.F;
            vboP[0].tx = 0;
            vboP[0].ty = 0;
            vboP[1].vx = size.x;
            vboP[1].vy = 0.F;
            vboP[1].tx = 65535;
            vboP[1].ty = 0;
            vboP[2].vx = 0.F;
            vboP[2].vy = size.y;
            vboP[2].tx = 0;
            vboP[2].ty = 65535;
            vboP[3].vx = size.x;
            vboP[3].vy = size.y;
            vboP[3].tx = 65535;
            vboP[3].ty = 65535;
            auto vbo = gl::VBO::create(4, sizeof(VBOData));
            vbo->copy(vboData);

            auto vao = gl::VAO::create(vbo->getID());
            vao->bind();
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_UNSIGNED_SHORT, GL_TRUE, sizeof(VBOData), (GLvoid*)8);
            glEnableVertexAttribArray(1);
            vao->draw(GL_TRIANGLE_STRIP, 0, 4);
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
