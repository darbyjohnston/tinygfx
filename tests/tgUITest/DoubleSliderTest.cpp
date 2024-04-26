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
                _app = App::create(
                    context,
                    argv,
                    "DoubleSliderTest",
                    "Double slider test.");
                _window = Window::create(context, _app, "DoubleSliderTest");
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->tick();

                auto slider = DoubleSlider::create(context, nullptr, _layout);
                TG_ASSERT(slider->getModel());
                double value = 0.0;
                slider->setCallback([&value](double v) { value = v; });
                slider->setValue(0.9);
                _app->tick();
                TG_ASSERT(0.9 == slider->getValue());
                TG_ASSERT(0.9 == value);
                slider->setRange(RangeD(0.0, 0.5));
                _app->tick();
                TG_ASSERT(RangeD(0.0, 0.5) == slider->getRange());
                TG_ASSERT(0.5 == value);
                slider->setStep(0.2);
                TG_ASSERT(0.2 == slider->getStep());
                slider->setLargeStep(0.3);
                TG_ASSERT(0.3 == slider->getLargeStep());

                Box2I g = slider->getGeometry();
                V2I c = center(g);
                _window->setCursorPos(c);
                _window->setButton(0, true);
                _window->setCursorPos(V2I(g.max.x, c.y));
                _window->setButton(0, false);

                _window->setKey(Key::Home);
                TG_ASSERT(value == 0.0);
                _window->setKey(Key::Right);
                TG_ASSERT(fuzzyCompare(value, 0.2));
                _window->setKey(Key::PageUp);
                TG_ASSERT(fuzzyCompare(value, 0.5));
                _window->setKey(Key::Left);
                TG_ASSERT(fuzzyCompare(value, 0.3));
                _window->setKey(Key::PageDown);
                TG_ASSERT(fuzzyCompare(value, 0.0));
                _window->setKey(Key::End);
                TG_ASSERT(value == 0.5);
                _window->setKey(Key::Escape);
                TG_ASSERT(!slider->hasKeyFocus());
            }
        }
    }
}

