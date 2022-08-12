// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Window.h"

#include "App.h"
#include "Mesh.h"

namespace tg
{
    namespace
    {
        const std::string vertexSource3D =
            "#version 410\n"
            "\n"
            "in vec3 vPos;\n"
            "in vec2 vTexture;\n"
            "in vec3 vNormal;\n"
            "\n"
            "out vec2 fTexture;\n"
            "out vec3 fNormal;\n"
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
            "    fNormal = vNormal;\n"
            "}\n";

        const std::string fragmentSource3D =
            "#version 410\n"
            "\n"
            "in vec2 fTexture;\n"
            "in vec3 fNormal;\n"
            "\n"
            "out vec4 fColor;\n"
            "\n"
            "uniform sampler2D textureSampler;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    fColor = texture(textureSampler, fTexture);\n"
            "    fColor.r = fTexture.x;\n"
            "    fColor.g = fTexture.y;\n"
            "    fColor.b = 0.0;\n"
            //"    fColor.r = fNormal.x;\n"
            //"    fColor.g = fNormal.y;\n"
            //"    fColor.b = fNormal.z;\n"
            "    fColor.a = 1.0;\n"
            "}\n";

        const std::string vertexSource2D =
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

        const std::string fragmentSource2D =
            "#version 410\n"
            "\n"
            "in vec2 fTexture;\n"
            "out vec4 fColor;\n"
            "\n"
            "uniform sampler2D textureSampler;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    fColor = texture(textureSampler, fTexture);\n"
            "}\n";
    }

    void Window::_init(const std::shared_ptr<App>& app)
    {
        IWindow::_init(app, "paint3d");

        _meshObserver = observer::ValueObserver<std::shared_ptr<geom::Mesh3D> >::create(
            app->observeMesh(),
            [this](const std::shared_ptr<geom::Mesh3D>& value)
            {
                _mesh = value;
                if (_mesh)
                {
                    _meshVBOVAO = gl::create(*_mesh, gl::Mesh3DType::V3F_T2F_N3F);
                }
                else
                {
                    _meshVBOVAO.first.reset();
                    _meshVBOVAO.second.reset();
                }
                repaint();
            });

        _shader3D = gl::Shader::create(vertexSource3D, fragmentSource3D);
        _shader2D = gl::Shader::create(vertexSource2D, fragmentSource2D);
    }

    std::shared_ptr<Window> Window::create(const std::shared_ptr<App>& app)
    {
        auto out = std::shared_ptr<Window>(new Window);
        out->_init(app);
        return out;
    }

    void Window::_paint()
    {
        const auto& size = getSize();
        if (gl::doCreate(_buffer, size))
        {
            gl::OffscreenBufferOptions options;
            options.colorFormat = image::Format::RGBA;
            options.colorType = image::Type::Float;
            options.depth = gl::OffscreenDepth::_24;
            _buffer = gl::OffscreenBuffer::create(size, options);
        }
        if (_buffer)
        {
            auto binding = gl::OffscreenBufferBinding(_buffer);

            glViewport(0, 0, size[0], size[1]);
            glClearColor(.5F, .5F, .5F, 0.F);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);

            _shader3D->bind();
            math::Matrix4x4f mvp;
            //mvp = math::rotateX(180.F) * mvp;
            mvp = math::rotateY(-_polarCamera[0]) * mvp;
            mvp = math::rotateX(-_polarCamera[1]) * mvp;
            mvp = math::translate(math::Vector3f(0.F, 0.F, -_polarCamera[2])) * mvp;
            mvp = math::perspective(
                60.F,
                size[0] / static_cast<float>(size[1]),
                .1F,
                10000.F) * mvp;
            _shader3D->setUniform("transform.mvp", mvp);

            if (_mesh && _meshVBOVAO.second)
            {
                _meshVBOVAO.second->bind();
                _meshVBOVAO.second->draw(GL_TRIANGLES, 0, _mesh->triangles.size() * 3);
            }

            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }

        glViewport(0, 0, size[0], size[1]);
        glClearColor(0.F, 0.F, 0.F, 0.F);
        glClear(GL_COLOR_BUFFER_BIT);

        _shader2D->bind();
        const auto mvp = math::ortho<float>(0.F, size[0], 0.F, size[1], -1.F, 1.F);
        _shader2D->setUniform("transform.mvp", mvp);
        if (_buffer)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _buffer->getColorID());
            _shader2D->setUniform("textureSampler", 0);
        }

        auto mesh = geom::bbox(math::BBox2f(0.F, 0.F, size[0], size[1]));
        auto vaoVbo = gl::create(mesh, gl::Mesh2DType::V2F_T2F);
        vaoVbo.second->bind();
        vaoVbo.second->draw(GL_TRIANGLES, 0, mesh.triangles.size() * 3);
    }

    void Window::_mouseDelta(const math::Vector2f& pos)
    {
        switch (_button)
        {
        case 0:
            _polarCamera[0] -= pos[0];
            _polarCamera[1] += pos[1];
            repaint();
            break;
        case 1:
            _polarCamera[2] -= (pos[0] + pos[1]) / 10.F;
            repaint();
            break;
        }
    }

    void Window::_mouseButton(int button, int action, int mods)
    {
        switch (action)
        {
        case GLFW_PRESS:
            _button = button;
            break;
        case GLFW_RELEASE:
            _button = -1;
            break;
        default: break;
        }
    }

    void Window::_drop(const std::vector<std::string>& paths)
    {
        if (auto app = std::dynamic_pointer_cast<App>(_app.lock()))
        {
            if (!paths.empty())
            {
                app->open(paths.front());
            }
        }
    }
}
