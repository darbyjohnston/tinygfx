// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/IntSliderTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/IntSlider.h>
#include <tgUI/RowLayout.h>

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
                auto app = App::create(
                    context,
                    argv,
                    "IntSliderTest",
                    "Integer slider test.");
                auto window = Window::create(context, app, "IntSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = IntSlider::create(context, nullptr, layout);
                TG_ASSERT(slider->getModel());
                int value = 0;
                slider->setCallback([&value](int v) { value = v; });
                slider->setValue(11);
                app->tick();
                TG_ASSERT(11 == slider->getValue());
                TG_ASSERT(11 == value);
                slider->setRange(RangeI(0, 10));
                app->tick();
                TG_ASSERT(RangeI(0, 10) == slider->getRange());
                TG_ASSERT(10 == value);
                slider->setStep(2);
                TG_ASSERT(2 == slider->getStep());
                slider->setLargeStep(3);
                TG_ASSERT(3 == slider->getLargeStep());

                Box2I g = slider->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0, true);
                window->setCursorPos(V2I(g.max.x, c.y));
                window->setButton(0, false);

                window->setKey(Key::Home);
                TG_ASSERT(value == 0);
                window->setKey(Key::Right);
                TG_ASSERT(value == 2);
                window->setKey(Key::PageUp);
                TG_ASSERT(value == 5);
                window->setKey(Key::Left);
                TG_ASSERT(value == 3);
                window->setKey(Key::PageDown);
                TG_ASSERT(value == 0);
                window->setKey(Key::End);
                TG_ASSERT(value == 10);
                window->setKey(Key::Escape);
                TG_ASSERT(!slider->hasKeyFocus());
            }
        }
    }
}

