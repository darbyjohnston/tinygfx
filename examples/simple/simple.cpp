// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "simple.h"

#include <tgUIApp/App.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace examples
    {
        namespace simple
        {
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

            void Window::drawEvent(const Box2I& drawRect, const DrawEvent& event)
            {
                ui::Window::drawEvent(drawRect, event);
                const std::string text = "Hello world";
                FontInfo fontInfo;
                fontInfo.size = 0;
                Size2I textSize;
                const Box2I g = margin(getGeometry(), -100);
                while (textSize.w < g.w() && textSize.h < g.h())
                {
                    fontInfo.size += 10;
                    textSize = event.fontSystem->getSize(text, fontInfo);
                }
                const auto textGlyphs = event.fontSystem->getGlyphs(text, fontInfo);
                const auto fontMetrics = event.fontSystem->getMetrics(fontInfo);
                event.render->drawText(
                    textGlyphs,
                    fontMetrics,
                    convert(center(g) - V2I(textSize.w, textSize.h) / 2),
                    Color4F(1.F, 1.F, 1.F));
            }
        }
    }
}

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = tg::app::convert(argc, argv);
        auto app = App::create(context, args, "simple", "Simple example");
        r = app->getExit();
        if (0 == r)
        {
            auto window = tg::examples::simple::Window::create(
                context,
                "simple",
                Size2I(1280, 720));
            app->addWindow(window);
            window->show();
            app->run();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

