// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/ColorWidgetTest.h>

#include <tgUI/ColorSwatch.h>
#include <tgUI/ColorWidget.h>

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
                _app = App::create(
                    context,
                    argv,
                    "ColorWidgetTest",
                    "Color widget test.");
                _window = Window::create(context, _app, "ColorWidgetTest");
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->tick();

                auto widget = ColorSwatch::create(context, _layout);
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

                _window->setCursorEnter(true);
                Box2I g = widget->getGeometry();
                V2I c = center(g);
                _window->setCursorPos(c);
                _window->setButton(0);
                _window->setKey(Key::Tab);
                _window->setKey(Key::Home);
                _window->setKey(Key::Tab);
                _window->setKey(Key::Tab);
                _window->setKey(Key::Home);
                _window->setKey(Key::Tab);
                _window->setKey(Key::Tab);
                _window->setKey(Key::Home);
                _window->setKey(Key::Tab);
                _window->setKey(Key::Tab);
                _window->setKey(Key::Home);
                _window->setKey(Key::Escape);
                TG_ASSERT(Color4F(0.F, 0.F, 0.F, 0.F) == color);
            }
        }
    }
}

