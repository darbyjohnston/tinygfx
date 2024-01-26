// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIApp/Window.h>

#include <tgGL/GL.h>
#include <tgGL/OffscreenBuffer.h>
#include <tgGL/Render.h>
#include <tgGL/Window.h>
#if defined(TINYGFX_API_GLES_2)
#include <tgGL/Mesh.h>
#include <tgGL/Shader.h>
#endif // TINYGFX_API_GLES_2

#include <tgUI/IconLibrary.h>
#include <tgUI/Style.h>

#include <tgCore/Context.h>
#include <tgCore/Format.h>
#include <tgCore/LogSystem.h>
#include <tgCore/FontSystem.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct Window::Private
        {
            std::weak_ptr<Context> context;
            std::shared_ptr<gl::Window> window;
            bool refresh = true;
            Size2I bufferSize = Size2I(0, 0);
            V2F contentScale = V2F(1.F, 1.F);
            std::shared_ptr<gl::OffscreenBuffer> buffer;
            std::shared_ptr<gl::Render> render;
#if defined(TINYGFX_API_GLES_2)
            std::shared_ptr<gl::Shader> shader;
#endif // TINYGFX_API_GLES_2
        };
        
        Window::Window(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            const Size2I& size) :
            _p(new Private)
        {
            IWindow::_init(context, name, nullptr);
            TG_P();
            
            p.context = context;

            p.window = gl::Window::create(context, name, size);
            p.window->setSizeCallback(
                [this](const Size2I& value)
                {
                    _updates |= Update::Size;
                    _updates |= Update::Draw;
                });
            p.window->setFrameBufferSizeCallback(
                [this](const Size2I& value)
                {
                    _p->bufferSize = value;
                    _updates |= Update::Size;
                    _updates |= Update::Draw;
                });
            p.window->setContentScaleCallback(
                [this](const V2F& value)
                {
                    _p->contentScale = value;
                    _updates |= Update::Size;
                    _updates |= Update::Draw;
                });
            p.window->setRefreshCallback(
                [this]()
                {
                    _p->refresh = true;
                });

            p.bufferSize = p.window->getFrameBufferSize();
            p.contentScale = p.window->getContentScale();
            p.render = gl::Render::create(context);

            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        Window::~Window()
        {
            TG_P();
            p.window->makeCurrent();
            p.render.reset();
            p.buffer.reset();
            p.window->doneCurrent();
        }
        
        std::shared_ptr<Window> Window::create(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            const Size2I& size)
        {
            return std::shared_ptr<Window>(new Window(context, name, size));
        }

        const Size2I& Window::getFrameBufferSize() const
        {
            return _p->bufferSize;
        }

        float Window::getDisplayScale() const
        {
            return _p->contentScale.x;
        }

        bool Window::shouldClose() const
        {
            return _p->window->shouldClose();
        }

        bool Window::shouldRefresh() const
        {
            return _p->refresh;
        }

        void Window::setGeometry(const Box2I& value)
        {
            IWindow::setGeometry(value);
            for (const auto& i : _children)
            {
                i->setGeometry(value);
            }
        }

        void Window::setVisible(bool value)
        {
            IWindow::setVisible(value);
            TG_P();
            if (value)
            {
                p.window->show();
            }
            else
            {
                p.window->hide();
            }
        }

        void Window::tickEvent(
            bool parentsVisible,
            bool parentsEnabled,
            const TickEvent& event)
        {
            IWindow::tickEvent(parentsVisible, parentsEnabled, event);
            TG_P();

            if (_hasSizeUpdate(shared_from_this()))
            {
                SizeHintEvent sizeHintEvent(
                    event.fontSystem,
                    p.contentScale.x,
                    event.style,
                    event.iconLibrary);
                _sizeHintEventRecursive(shared_from_this(), sizeHintEvent);

                setGeometry(Box2I(V2I(), p.bufferSize));

                _clipEventRecursive(
                    shared_from_this(),
                    _geometry,
                    !isVisible(false));
            }
            
            if (p.refresh || _hasDrawUpdate(shared_from_this()))
            {
                p.window->makeCurrent();

                gl::OffscreenBufferOptions bufferOptions;
                bufferOptions.color = gl::offscreenColorDefault;
                if (gl::doCreate(p.buffer, p.bufferSize, bufferOptions))
                {
                    p.buffer = gl::OffscreenBuffer::create(p.bufferSize, bufferOptions);
                }

                if (_updates & Update::Draw && p.buffer)
                {
                    gl::OffscreenBufferBinding bufferBinding(p.buffer);
                    p.render->begin(p.bufferSize);
                    DrawEvent drawEvent(
                        event.fontSystem,
                        _p->contentScale.x,
                        event.style,
                        event.iconLibrary,
                        p.render);
                    this->drawEvent(Box2I(V2I(), p.bufferSize), drawEvent);
                    p.render->end();
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
                        p.bufferSize.w,
                        p.bufferSize.h,
                        0,
                        0,
                        p.bufferSize.w,
                        p.bufferSize.h,
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
                                "tg::ui::Window",
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
                            static_cast<float>(p.bufferSize.w),
                            0.F,
                            static_cast<float>(p.bufferSize.h),
                            -1.F,
                            1.F));
                    p.shader->setUniform("textureSampler", 0);

                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0));
                    glBindTexture(GL_TEXTURE_2D, p.buffer->getColorID());

                    auto mesh = core::mesh(Box2I(
                        0,
                        0,
                        p.bufferSize.w,
                        p.bufferSize.h));
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
            }
        }

        bool Window::_hasSizeUpdate(const std::shared_ptr<IWidget>& widget) const
        {
            bool out = widget->getUpdates() & Update::Size;
            if (out)
            {
                //std::cout << "Size update: " << widget->getObjectName() << std::endl;
            }
            else
            {
                for (const auto& child : widget->getChildren())
                {
                    out |= _hasSizeUpdate(child);
                }
            }
            return out;
        }

        void Window::_sizeHintEventRecursive(
            const std::shared_ptr<IWidget>& widget,
            const SizeHintEvent& event)
        {
            for (const auto& child : widget->getChildren())
            {
                _sizeHintEventRecursive(child, event);
            }
            widget->sizeHintEvent(event);
        }

        bool Window::_hasDrawUpdate(const std::shared_ptr<IWidget>& widget) const
        {
            bool out = false;
            if (!widget->isClipped())
            {
                out = widget->getUpdates() & Update::Draw;
                if (out)
                {
                    //std::cout << "Draw update: " << widget->getObjectName() << std::endl;
                }
                else
                {
                    for (const auto& child : widget->getChildren())
                    {
                        out |= _hasDrawUpdate(child);
                    }
                }
            }
            return out;
        }

        void Window::_drawEventRecursive(
            const std::shared_ptr<IWidget>& widget,
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            const Box2I& g = widget->getGeometry();
            if (!widget->isClipped() && g.w() > 0 && g.h() > 0)
            {
                event.render->setClipRect(drawRect);
                widget->drawEvent(drawRect, event);
                const Box2I childrenClipRect = intersect(
                    widget->getChildrenClipRect(),
                    drawRect);
                event.render->setClipRect(childrenClipRect);
                for (const auto& child : widget->getChildren())
                {
                    const Box2I& childGeometry = child->getGeometry();
                    if (intersects(childGeometry, childrenClipRect))
                    {
                        _drawEventRecursive(
                            child,
                            intersect(childGeometry, childrenClipRect),
                            event);
                    }
                }
                event.render->setClipRect(drawRect);
                widget->drawOverlayEvent(drawRect, event);
            }
        }
    }
}

