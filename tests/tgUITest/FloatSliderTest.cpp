// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/FloatSliderTest.h>

#include <tgUI/FloatSlider.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        FloatSliderTest::FloatSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::FloatSliderTest")
        {}

        FloatSliderTest::~FloatSliderTest()
        {}

        std::shared_ptr<FloatSliderTest> FloatSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FloatSliderTest>(new FloatSliderTest(context));
        }

        void FloatSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FloatSliderTest");
                _app = App::create(
                    context,
                    argv,
                    "FloatSliderTest",
                    "Float slider test.");
                _window = Window::create(context, _app, "FloatSliderTest");
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->tick();

                auto slider = FloatSlider::create(context, nullptr, _layout);
                TG_ASSERT(slider->getModel());
                float value = 0.F;
                slider->setCallback([&value](float v) { value = v; });
                slider->setValue(.9F);
                _app->tick();
                TG_ASSERT(.9F == slider->getValue());
                TG_ASSERT(.9F == value);
                slider->setRange(RangeF(0.F, .5F));
                _app->tick();
                TG_ASSERT(RangeF(0.F, .5F) == slider->getRange());
                TG_ASSERT(.5F == value);
                slider->setStep(.2F);
                TG_ASSERT(.2F == slider->getStep());
                slider->setLargeStep(.3F);
                TG_ASSERT(.3F == slider->getLargeStep());

                Box2I g = slider->getGeometry();
                V2I c = center(g);
                _window->setCursorPos(c);
                _window->setButton(0, true);
                _window->setCursorPos(V2I(g.max.x, c.y));
                _window->setButton(0, false);

                _window->setKey(Key::Home);
                TG_ASSERT(value == 0.F);
                _window->setKey(Key::Right);
                TG_ASSERT(fuzzyCompare(value, .2F));
                _window->setKey(Key::PageUp);
                TG_ASSERT(fuzzyCompare(value, .5F));
                _window->setKey(Key::Left);
                TG_ASSERT(fuzzyCompare(value, .3F));
                _window->setKey(Key::PageDown);
                TG_ASSERT(fuzzyCompare(value, 0.F));
                _window->setKey(Key::End);
                TG_ASSERT(value == .5F);
                _window->setKey(Key::Escape);
                TG_ASSERT(!slider->hasKeyFocus());
            }
        }
    }
}

