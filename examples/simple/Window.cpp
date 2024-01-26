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
                ui::Window(context, name, size)
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
            
            void Window::drawEvent(const Box2I& drawRect, const ui::DrawEvent& event)
            {
                ui::Window::drawEvent(drawRect, event);
                
                const Box2F box(0, 0, _geometry.w(), _geometry.h());
                event.render->drawRect(box, Color4F(1.F, 1.F, 1.F));

                FontInfo fontInfo;
                fontInfo.size = 100 * event.displayScale;
                const FontMetrics fontMetrics = event.fontSystem->getMetrics(fontInfo);
                const std::string text = "Hello world";
                const Size2I textSize = event.fontSystem->getSize(text, fontInfo);
                const auto glyphs = event.fontSystem->getGlyphs(text, fontInfo);
                event.render->drawText(
                    glyphs,
                    center(box) - V2F(textSize.w, textSize.h) / 2.F + V2F(0.F, fontMetrics.ascender),
                    Color4F(0.F, 0.F, 0.F));
            }
        }
    }
}

