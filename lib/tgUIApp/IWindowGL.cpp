// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIApp/IWindow.h>

#include <tgGL/GL.h>
#include <tgGL/OffscreenBuffer.h>
#include <tgGL/Render.h>
#include <tgGL/Window.h>
#if defined(TINYGFX_API_GLES_2)
#include <tgGL/Mesh.h>
#include <tgGL/Shader.h>
#endif // TINYGFX_API_GLES_2

#include <tgCore/Context.h>
#include <tgCore/Format.h>
#include <tgCore/LogSystem.h>
#include <tgCore/FontSystem.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct IWindow::Private
        {
            std::weak_ptr<Context> context;
            Size2I size = Size2I(0, 0);
            std::shared_ptr<gl::Window> window;
            bool refresh = true;
            bool redraw = true;
            Size2I bufferSize = Size2I(0, 0);
            V2F contentScale = V2F(1.F, 1.F);
            std::shared_ptr<FontSystem> fontSystem;
            std::shared_ptr<gl::OffscreenBuffer> buffer;
            std::shared_ptr<gl::Render> render;
#if defined(TINYGFX_API_GLES_2)
            std::shared_ptr<gl::Shader> shader;
#endif // TINYGFX_API_GLES_2
        };
        
        IWindow::IWindow(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            const Size2I& size) :
            _p(new Private)
        {
            TG_P();
            
            p.context = context;
            p.size = size;

            p.window = gl::Window::create(context, name, size);
            p.window->setSizeCallback(
                [this](const Size2I& value)
                {
                    _p->size = value;
                    _p->redraw = true;
                });
            p.window->setFrameBufferSizeCallback(
                [this](const Size2I& value)
                {
                    _p->bufferSize = value;
                    _p->redraw = true;
                });
            p.window->setContentScaleCallback(
                [this](const V2F& value)
                {
                    _p->contentScale = value;
                    _p->redraw = true;
                });
            p.window->setRefreshCallback(
                [this]()
                {
                    _p->refresh = true;
                });

            p.bufferSize = p.window->getFrameBufferSize();
            p.contentScale = p.window->getContentScale();
            p.fontSystem = context->getSystem<FontSystem>();
            p.render = gl::Render::create(context);
        }

        IWindow::~IWindow()
        {
            TG_P();
            p.window->makeCurrent();
            p.render.reset();
            p.buffer.reset();
            p.window->doneCurrent();
        }

        void IWindow::show()
        {
            _p->window->show();
        }

        void IWindow::hide()
        {
            _p->window->hide();
        }

        void IWindow::tick()
        {}

        const Size2I& IWindow::getSize() const
        {
            return _p->size;
        }

        int IWindow::getWidth() const
        {
            return _p->size.w();
        }

        int IWindow::getHeight() const
        {
            return _p->size.h();
        }

        void IWindow::redraw()
        {
            _p->redraw = true;
        }

        const Size2I& IWindow::getFrameBufferSize() const
        {
            return _p->bufferSize;
        }

        void IWindow::draw()
        {
            TG_P();
            
            p.window->makeCurrent();

            gl::OffscreenBufferOptions bufferOptions;
            bufferOptions.color = gl::offscreenColorDefault;
            if (gl::doCreate(p.buffer, p.bufferSize, bufferOptions))
            {
                p.buffer = gl::OffscreenBuffer::create(p.bufferSize, bufferOptions);
            }

            if (p.redraw && p.buffer)
            {
                gl::OffscreenBufferBinding bufferBinding(p.buffer);
                _draw(p.contentScale, p.fontSystem, p.render);
            }

#if defined(TINYGFX_API_GL_4_1)
            if (p.buffer)
            {
                glBindFramebuffer(
                    GL_READ_FRAMEBUFFER,
                    p.buffer->getID());
                glBlitFramebuffer(
                    0,
                    0,
                    p.bufferSize.w(),
                    p.bufferSize.h(),
                    0,
                    0,
                    p.bufferSize.w(),
                    p.bufferSize.h(),
                    GL_COLOR_BUFFER_BIT,
                    GL_LINEAR);
            }
#elif defined(TINYGFX_API_GLES_2)
            if (!p.shader)
            {
                try
                {
                    const std::string vertexSource =
                        "precision mediump float;\n"
                        "\n"
                        "attribute vec3 vPos;\n"
                        "attribute vec2 vTexture;\n"
                        "varying vec2 fTexture;\n"
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
                        "precision mediump float;\n"
                        "\n"
                        "varying vec2 fTexture;\n"
                        "\n"
                        "uniform sampler2D textureSampler;\n"
                        "\n"
                        "void main()\n"
                        "{\n"
                        "    gl_FragColor = texture2D(textureSampler, fTexture);\n"
                        "}\n";
                    p.shader = gl::Shader::create(vertexSource, fragmentSource);
                }
                catch (const std::exception& e)
                {
                    if (auto context = p.context.lock())
                    {
                        context->getSystem<LogSystem>()->print(
                            "tl::ui_app::Window",
                            Format("Cannot compile shader: {0}").arg(e.what()),
                            LogType::Error);
                    }
                }
            }
            if (p.shader)
            {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                glDisable(GL_BLEND);
                glDisable(GL_SCISSOR_TEST);

                p.shader->bind();
                p.shader->setUniform(
                    "transform.mvp",
                    ortho(
                        0.F,
                        static_cast<float>(p.bufferSize.w()),
                        0.F,
                        static_cast<float>(p.bufferSize.h()),
                        -1.F,
                        1.F));
                p.shader->setUniform("textureSampler", 0);

                glActiveTexture(static_cast<GLenum>(GL_TEXTURE0));
                glBindTexture(GL_TEXTURE_2D, p.buffer->getColorID());

                auto mesh = core::mesh(Box2I(
                    0,
                    0,
                    p.bufferSize.w(),
                    p.bufferSize.h()));
                auto vboData = gl::convert(
                    mesh,
                    gl::VBOType::Pos2_F32_UV_U16,
                    RangeSizeT(0, mesh.triangles.size() - 1));
                auto vbo = gl::VBO::create(mesh.triangles.size() * 3, gl::VBOType::Pos2_F32_UV_U16);
                vbo->copy(vboData);
                auto vao = gl::VAO::create(gl::VBOType::Pos2_F32_UV_U16, vbo->getID());
                vao->bind();
                vao->draw(GL_TRIANGLES, 0, mesh.triangles.size() * 3);
            }
#endif // TINYGFX_API_GL_4_1

            p.window->swap();
            p.window->doneCurrent();
            
            p.refresh = false;
            p.redraw = false;
        }

        bool IWindow::shouldRedraw() const
        {
            return _p->refresh || _p->redraw;
        }

        bool IWindow::shouldClose() const
        {
            return _p->window->shouldClose();
        }
    }
}

