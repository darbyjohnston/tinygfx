// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/Window.h>

#include <tgUI/IClipboard.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        namespace
        {
            class Clipboard : public IClipboard
            {
            protected:
                Clipboard()
                {}

            public:
                virtual ~Clipboard()
                {}

                static std::shared_ptr<Clipboard> create(
                    const std::shared_ptr<Context>& context)
                {
                    auto out = std::shared_ptr<Clipboard>(new Clipboard);
                    out->_init(context);
                    return out;
                }

                std::string getText() const override
                {
                    return _text;
                }

                void setText(const std::string& value) override
                {
                    _text = value;
                }

            private:
                std::string _text;
            };

            class Render : public IRender
            {
            public:
                static std::shared_ptr<Render> create(const std::shared_ptr<Context>&);

                void begin(
                    const Size2I&,
                    const RenderOptions& = RenderOptions()) override;
                void end() override {}
                Size2I getRenderSize() const override;
                void setRenderSize(const Size2I&) override;
                Box2I getViewport() const override;
                void setViewport(const Box2I&) override;
                void clearViewport(const Color4F&) override {}
                bool getClipRectEnabled() const override;
                void setClipRectEnabled(bool) override;
                Box2I getClipRect() const override;
                void setClipRect(const Box2I&) override;
                M44F getTransform() const override;
                void setTransform(const M44F&) override;
                void drawRect(
                    const Box2F&,
                    const Color4F&) override {}
                void drawRects(
                    const std::vector<Box2F>&,
                    const Color4F&) override {}
                void drawLine(
                    const V2F&,
                    const V2F&,
                    const Color4F&,
                    const LineOptions& = LineOptions()) override {}
                void drawLines(
                    const std::vector<std::pair<V2F, V2F> >&,
                    const Color4F&,
                    const LineOptions& = LineOptions()) override {}
                void drawMesh(
                    const TriMesh2F&,
                    const Color4F & = Color4F(1.F, 1.F, 1.F, 1.F),
                    const V2F& pos = V2F()) override {}
                void drawColorMesh(
                    const TriMesh2F&,
                    const Color4F & = Color4F(1.F, 1.F, 1.F, 1.F),
                    const V2F& pos = V2F()) override {};
                void drawText(
                    const std::vector<std::shared_ptr<Glyph> >&,
                    const FontMetrics&,
                    const V2F& position,
                    const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F)) override {}
                void drawImage(
                    const std::shared_ptr<Image>&,
                    const Box2F&,
                    const Color4F & = Color4F(1.F, 1.F, 1.F, 1.F),
                    const ImageOptions& = ImageOptions()) override {}

            private:
                Size2I _renderSize;
                Box2I _viewport;
                bool _clipRectEnabled = false;
                Box2I _clipRect;
                M44F _transform;
            };

            std::shared_ptr<Render> Render::create(const std::shared_ptr<Context>& context)
            {
                auto out = std::shared_ptr<Render>(new Render);
                out->_init(context);
                return out;
            }

            void Render::begin(
                const Size2I& size,
                const RenderOptions&)
            {
                _renderSize = size;
            }

            Size2I Render::getRenderSize() const 
            {
                return _renderSize;
            }

            void Render::setRenderSize(const Size2I& value)
            {
                _renderSize = value;
            }

            Box2I Render::getViewport() const
            {
                return _viewport;
            }

            void Render::setViewport(const Box2I& value)
            {
                _viewport = value;
            }

            bool Render::getClipRectEnabled() const
            {
                return _clipRectEnabled;
            }

            void Render::setClipRectEnabled(bool value)
            {
                _clipRectEnabled = value;
            }

            Box2I Render::getClipRect() const
            {
                return _clipRect;
            }

            void Render::setClipRect(const Box2I& value)
            {
                _clipRect = value;
            }

            M44F Render::getTransform() const
            {
                return _transform;
            }

            void Render::setTransform(const M44F& value)
            {
                _transform = value;
            }
        }

        struct Window::Private
        {
            std::weak_ptr<Context> context;
            Size2I bufferSize = Size2I(0, 0);
            V2F contentScale = V2F(1.F, 1.F);
            bool refresh = true;
            int modifiers = 0;
            std::shared_ptr<Render> render;
        };

        void Window::_init(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            const Size2I& size)
        {
            IWindow::_init(context, name, nullptr);
            TG_P();

            p.context = context;

            p.bufferSize = size;
            p.render = Render::create(context);

            setClipboard(Clipboard::create(context));

            _setSizeUpdate();
            _setDrawUpdate();
        }

        Window::Window() :
            _p(new Private)
        {}

        Window::~Window()
        {}

        std::shared_ptr<Window> Window::create(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            const Size2I& size)
        {
            auto out = std::shared_ptr<Window>(new Window);
            out->_init(context, name, size);
            return out;
        }

        void Window::setGeometry(const Box2I& value)
        {
            IWindow::setGeometry(value);
            for (const auto& child : getChildren())
            {
                child->setGeometry(value);
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
                    getGeometry(),
                    !isVisible(false));
            }

            const bool drawUpdate = _hasDrawUpdate(shared_from_this());
            if (p.refresh || drawUpdate)
            {
                p.render->begin(p.bufferSize);
                p.render->setClipRectEnabled(true);
                DrawEvent drawEvent(
                    event.fontSystem,
                    _p->contentScale.x,
                    event.style,
                    event.iconLibrary,
                    p.render);
                _drawEventRecursive(
                    shared_from_this(),
                    Box2I(V2I(), p.bufferSize),
                    drawEvent);
                p.render->setClipRectEnabled(false);
                p.render->end();

                p.refresh = false;
            }
        }

        void Window::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            Size2I sizeHint;
            for (const auto& child : getChildren())
            {
                const Size2I& childSizeHint = child->getSizeHint();
                sizeHint.w = std::max(sizeHint.w, childSizeHint.w);
                sizeHint.h = std::max(sizeHint.h, childSizeHint.h);
            }
            _setSizeHint(sizeHint);
        }
    }
}

