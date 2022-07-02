// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Window.h"

#include "Mesh.h"

#include <tgGL/Mesh.h>

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
            //"    fColor = texture(textureSampler, fTexture);\n"
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

    void Window::_init(
        const std::shared_ptr<app::App>& app,
        const std::shared_ptr<Mesh>& mesh)
    {
        IWindow::_init(app, "paint3d");

        _mesh = mesh;

        _shader3D = gl::Shader::create(vertexSource3D, fragmentSource3D);
        _shader2D = gl::Shader::create(vertexSource2D, fragmentSource2D);
    }

    std::shared_ptr<Window> Window::create(
        const std::shared_ptr<app::App>& app,
        const std::shared_ptr<Mesh>& mesh)
    {
        auto out = std::shared_ptr<Window>(new Window);
        out->_init(app, mesh);
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

            glViewport(0, 0, size.x, size.y);
            glClearColor(1.F, 0.F, 0.F, 0.F);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

            _shader3D->bind();
            math::Matrix4x4f mvp;
            mvp = math::rotateX(180.F) * mvp;
            mvp = math::rotateY(-_polarCamera.x) * mvp;
            mvp = math::rotateX(-_polarCamera.y) * mvp;
            mvp = math::translate(math::Vector3f(0.F, 0.F, -_polarCamera.z)) * mvp;
            mvp = math::perspective(
                60.F,
                size.x / static_cast<float>(size.y),
                .1F,
                10000.F) * mvp;
            _shader3D->setUniform("transform.mvp", mvp);

            std::vector<uint8_t> vboData;
            struct VBOData
            {
                float vx;
                float vy;
                float vz;
                float tx;
                float ty;
                float nx;
                float ny;
                float nz;
            };
            vboData.resize(_mesh->triangles.size() * 3 * sizeof(VBOData));
            VBOData* vboP = reinterpret_cast<VBOData*>(vboData.data());
            const auto& v = _mesh->v;
            const auto& t = _mesh->t;
            const auto& n = _mesh->n;
            for (size_t i = 0; i < _mesh->triangles.size(); ++i)
            {
                const auto &triangle = _mesh->triangles[i];
                vboP[0].vx = v[triangle.v[0] - 1].x;
                vboP[0].vy = v[triangle.v[0] - 1].y;
                vboP[0].vz = v[triangle.v[0] - 1].z;
                vboP[0].tx = triangle.t[0] > 0 ? t[triangle.t[0] - 1].x : 0.F;
                vboP[0].ty = triangle.t[0] > 0 ? t[triangle.t[0] - 1].y : 0.F;
                vboP[0].nx = triangle.n[0] > 0 ? n[triangle.n[0] - 1].x : 0.F;
                vboP[0].ny = triangle.n[0] > 0 ? n[triangle.n[0] - 1].y : 0.F;
                vboP[0].nz = triangle.n[0] > 0 ? n[triangle.n[0] - 1].z : 0.F;

                vboP[1].vx = v[triangle.v[1] - 1].x;
                vboP[1].vy = v[triangle.v[1] - 1].y;
                vboP[1].vz = v[triangle.v[1] - 1].z;
                vboP[1].tx = triangle.t[1] > 0 ? t[triangle.t[1] - 1].x : 0.F;
                vboP[1].ty = triangle.t[1] > 0 ? t[triangle.t[1] - 1].y : 0.F;
                vboP[1].nx = triangle.n[1] > 0 ? n[triangle.n[1] - 1].x : 0.F;
                vboP[1].ny = triangle.n[1] > 0 ? n[triangle.n[1] - 1].y : 0.F;
                vboP[1].nz = triangle.n[1] > 0 ? n[triangle.n[1] - 1].z : 0.F;

                vboP[2].vx = v[triangle.v[2] - 1].x;
                vboP[2].vy = v[triangle.v[2] - 1].y;
                vboP[2].vz = v[triangle.v[2] - 1].z;
                vboP[2].tx = triangle.t[2] > 0 ? t[triangle.t[2] - 1].x : 0.F;
                vboP[2].ty = triangle.t[2] > 0 ? t[triangle.t[2] - 1].y : 0.F;
                vboP[2].nx = triangle.n[2] > 0 ? n[triangle.n[2] - 1].x : 0.F;
                vboP[2].ny = triangle.n[2] > 0 ? n[triangle.n[2] - 1].y : 0.F;
                vboP[2].nz = triangle.n[2] > 0 ? n[triangle.n[2] - 1].z : 0.F;

                vboP += 3;
            }
            auto vbo = gl::VBO::create(_mesh->triangles.size() * 3, sizeof(VBOData));
            vbo->copy(vboData);

            auto vao = gl::VAO::create(vbo->getID());
            vao->bind();
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)12);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)20);
            glEnableVertexAttribArray(2);
            vao->draw(GL_TRIANGLES, 0, _mesh->triangles.size() * 3);
        }

        glViewport(0, 0, size.x, size.y);
        glClearColor(0.F, 0.F, 0.F, 0.F);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);

        _shader2D->bind();
        const auto mvp = math::ortho<float>(0.F, size.x, size.y, 0.F, -1.F, 1.F);
        _shader2D->setUniform("transform.mvp", mvp);
        if (_buffer)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _buffer->getColorID());
            _shader2D->setUniform("textureSampler", 0);
        }

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

    void Window::_mouseDelta(const math::Vector2f& pos)
    {
        switch (_button)
        {
        case 0:
            _polarCamera.x -= pos.x;
            _polarCamera.y += pos.y;
            repaint();
            break;
        case 1:
            _polarCamera.z -= (pos.x + pos.y) / 10.F;
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
}
