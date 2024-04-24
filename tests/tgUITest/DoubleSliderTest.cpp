// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/DoubleSliderTest.h>

#include <tgUI/DoubleSlider.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        DoubleSliderTest::DoubleSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::DoubleSliderTest")
        {}

        DoubleSliderTest::~DoubleSliderTest()
        {}

        std::shared_ptr<DoubleSliderTest> DoubleSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<DoubleSliderTest>(new DoubleSliderTest(context));
        }
                
        void DoubleSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("DoubleSliderTest");
                _app = App::create(context, argv, "DoubleSliderTest", "Double slider test.");
                _window = Window::create(context, "DoubleSliderTest", Size2I(1280, 960));
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->run();

                auto slider = DoubleSlider::create(context, nullptr, _layout);
                TG_ASSERT(slider->getModel());
                double value = 0.0;
                slider->setCallback([&value](double v) { value = v; });

                slider->setValue(0.9);
                _app->run();
                TG_ASSERT(0.9 == slider->getValue());
                TG_ASSERT(0.9 == value);

                slider->setRange(RangeD(0.0, 0.5));
                _app->run();
                TG_ASSERT(RangeD(0.0, 0.5) == slider->getRange());
                TG_ASSERT(0.5 == value);

                slider->setStep(0.2);
                TG_ASSERT(0.2 == slider->getStep());
                slider->setLargeStep(0.3);
                TG_ASSERT(0.3 == slider->getLargeStep());

                Box2I g = slider->getGeometry();
                V2I c = center(g);
                _window->cursorPos(c);
                _app->run();
                _window->button(0, true, 0);
                _app->run();
                _window->cursorPos(V2I(g.max.x, c.y));
                _app->run();
                _window->button(0, false, 0);
                _app->run();

                _window->key(Key::Home, true, 0);
                _app->run();
                _window->key(Key::Home, false, 0);
                _app->run();
                TG_ASSERT(value == 0.0);
                _window->key(Key::Right, true, 0);
                _app->run();
                _window->key(Key::Right, false, 0);
                _app->run();
                TG_ASSERT(fuzzyCompare(value, 0.2));
                _window->key(Key::PageUp, true, 0);
                _app->run();
                _window->key(Key::PageUp, false, 0);
                _app->run();
                TG_ASSERT(fuzzyCompare(value, 0.5));
                _window->key(Key::Left, true, 0);
                _app->run();
                _window->key(Key::Left, false, 0);
                _app->run();
                TG_ASSERT(fuzzyCompare(value, 0.3));
                _window->key(Key::PageDown, true, 0);
                _app->run();
                _window->key(Key::PageDown, false, 0);
                _app->run();
                TG_ASSERT(fuzzyCompare(value, 0.0));
                _window->key(Key::Escape, true, 0);
                _app->run();
                _window->key(Key::Escape, false, 0);
                _app->run();
                TG_ASSERT(!slider->hasKeyFocus());
            }
        }
    }
}

