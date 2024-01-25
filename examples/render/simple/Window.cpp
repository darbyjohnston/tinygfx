// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "Window.h"

#include <tgRender/IRender.h>

using namespace tg::core;

namespace tg
{
    namespace examples
    {
        namespace simple
        {
            Window::Window(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                const Size2I& size) :
                IWindow(context, name, size)
            {}

            Window::~Window()
            {}
            
            std::shared_ptr<Window> Window::create(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                const Size2I& size)
            {
                return std::shared_ptr<Window>(new Window(context, name, size));
            }
            
            void Window::_draw(
                const V2F& contentScale,
                const std::shared_ptr<FontSystem>& fontSystem,
                const std::shared_ptr<render::IRender>& render)
            {
                render->begin(getFrameBufferSize());

                const Box2F box(0, 0, getWidth(), getHeight());
                render->drawRect(box, Color4F(1.F, 1.F, 1.F));
                    
                FontInfo fontInfo;
                fontInfo.size = 100 * contentScale.x;
                const FontMetrics fontMetrics = fontSystem->getMetrics(fontInfo);
                const std::string text = "Hello world";
                const Size2I textSize = fontSystem->getSize(text, fontInfo);
                const auto glyphs = fontSystem->getGlyphs(text, fontInfo);
                render->drawText(
                    glyphs,
                    center(box) - V2F(textSize.w, textSize.h) / 2.F + V2F(0.F, fontMetrics.ascender),
                    Color4F(0.F, 0.F, 0.F));

                render->end();
            }
        }
    }
}

