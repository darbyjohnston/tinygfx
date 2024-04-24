// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/IntSliderTest.h>

#include <tgUI/IntSlider.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        IntSliderTest::IntSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::IntSliderTest")
        {}

        IntSliderTest::~IntSliderTest()
        {}

        std::shared_ptr<IntSliderTest> IntSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IntSliderTest>(new IntSliderTest(context));
        }
                
        void IntSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("IntSliderTest");
                _app = App::create(context, argv, "IntSliderTest", "Integer slider test.");
                _window = Window::create(context, "IntSliderTest", Size2I(1280, 960));
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->run();

                auto slider = IntSlider::create(context, nullptr, _layout);
                TG_ASSERT(slider->getModel());
                int value = 0;
                slider->setCallback([&value](int v) { value = v; });

                slider->setValue(11);
                _app->run();
                TG_ASSERT(11 == slider->getValue());
                TG_ASSERT(11 == value);

                slider->setRange(RangeI(0, 10));
                _app->run();
                TG_ASSERT(RangeI(0, 10) == slider->getRange());
                TG_ASSERT(10 == value);

                slider->setStep(2);
                TG_ASSERT(2 == slider->getStep());
                slider->setLargeStep(3);
                TG_ASSERT(3 == slider->getLargeStep());

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
            }
        }
    }
}

