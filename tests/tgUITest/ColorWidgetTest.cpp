// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/ColorWidgetTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/ColorPopup.h>
#include <tgUI/ColorSwatch.h>
#include <tgUI/ColorWidget.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        ColorWidgetTest::ColorWidgetTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::ColorWidgetTest")
        {}

        ColorWidgetTest::~ColorWidgetTest()
        {}

        std::shared_ptr<ColorWidgetTest> ColorWidgetTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ColorWidgetTest>(new ColorWidgetTest(context));
        }
                
        void ColorWidgetTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ColorWidgetTest");
                auto app = App::create(
                    context,
                    argv,
                    "ColorWidgetTest",
                    "Color widget test.");
                auto window = Window::create(context, app, "ColorWidgetTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget = ColorSwatch::create(context, layout);
                Color4F color(1.F, 1.F, 1.F, 1.F);
                widget->setColor(color);
                widget->setColor(color);
                TG_ASSERT(color == widget->getColor());
                TG_ASSERT(!widget->isEditable());
                widget->setEditable(true);
                widget->setEditable(true);
                TG_ASSERT(widget->isEditable());
                widget->setCallback(
                    [&color](const Color4F& value)
                    {
                        color = value;
                    });
                widget->setSizeRole(SizeRole::Margin);
                widget->setSizeRole(SizeRole::Margin);
                TG_ASSERT(SizeRole::Margin == widget->getSizeRole());
                widget->setSizeRole(SizeRole::Swatch);

                window->setCursorEnter(true);
                Box2I g = widget->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0);
                window->setKey(Key::Tab);
                window->setKey(Key::Home);
                window->setKey(Key::Tab);
                window->setKey(Key::Tab);
                window->setKey(Key::Home);
                window->setKey(Key::Tab);
                window->setKey(Key::Tab);
                window->setKey(Key::Home);
                window->setKey(Key::Tab);
                window->setKey(Key::Tab);
                window->setKey(Key::Home);
                window->setKey(Key::Escape);
                window->setKey(Key::Escape);
                TG_ASSERT(Color4F(0.F, 0.F, 0.F, 0.F) == color);

                auto popup = ColorPopup::create(context, color);
                popup->setPopupRole(ColorRole::Red);
                popup->setPopupRole(ColorRole::Red);
                TG_ASSERT(ColorRole::Red == popup->getPopupRole());
                popup->open(window, widget->getGeometry());
                app->tick();
                TG_ASSERT(popup->isOpen());
                popup->close();
                app->tick();
                TG_ASSERT(!popup->isOpen());

                popup->open(window, widget->getGeometry());
                app->tick();
                TG_ASSERT(popup->isOpen());
                window->setKey(Key::Escape);
                window->setKey(Key::Escape);
                TG_ASSERT(!popup->isOpen());

                popup->open(window, widget->getGeometry());
                app->tick();
                TG_ASSERT(popup->isOpen());
                g = window->getGeometry();
                window->setCursorPos(V2I(g.w() - 1, g.h() - 1));
                window->setButton(0);
                popup->open(window, widget->getGeometry());
                app->tick();
                TG_ASSERT(popup->isOpen());
            }
        }
    }
}

