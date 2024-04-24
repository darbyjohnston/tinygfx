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
                _app = App::create(context, argv, "FloatSliderTest", "Float slider test.");
                _window = Window::create(context, "FloatSliderTest", Size2I(1280, 960));
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->run();

                auto slider = FloatSlider::create(context, nullptr, _layout);
                TG_ASSERT(slider->getModel());
                float value = 0.F;
                slider->setCallback([&value](float v) { value = v; });

                slider->setValue(.9F);
                _app->run();
                TG_ASSERT(.9F == slider->getValue());
                TG_ASSERT(.9F == value);

                slider->setRange(RangeF(0.F, .5F));
                _app->run();
                TG_ASSERT(RangeF(0.F, .5F) == slider->getRange());
                TG_ASSERT(.5F == value);

                slider->setStep(.2F);
                TG_ASSERT(.2F == slider->getStep());
                slider->setLargeStep(.3F);
                TG_ASSERT(.3F == slider->getLargeStep());

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
                TG_ASSERT(value == 0.F);
                _window->key(Key::Right, true, 0);
                _app->run();
                _window->key(Key::Right, false, 0);
                _app->run();
                TG_ASSERT(fuzzyCompare(value, .2F));
                _window->key(Key::PageUp, true, 0);
                _app->run();
                _window->key(Key::PageUp, false, 0);
                _app->run();
                TG_ASSERT(fuzzyCompare(value, .5F));
                _window->key(Key::Left, true, 0);
                _app->run();
                _window->key(Key::Left, false, 0);
                _app->run();
                TG_ASSERT(fuzzyCompare(value, .3F));
                _window->key(Key::PageDown, true, 0);
                _app->run();
                _window->key(Key::PageDown, false, 0);
                _app->run();
                TG_ASSERT(fuzzyCompare(value, .0F));
                _window->key(Key::Escape, true, 0);
                _app->run();
                _window->key(Key::Escape, false, 0);
                _app->run();
                TG_ASSERT(!slider->hasKeyFocus());
            }
        }
    }
}

