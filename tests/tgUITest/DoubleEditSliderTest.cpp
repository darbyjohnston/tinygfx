// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/DoubleEditSliderTest.h>

#include <tgUI/DoubleEditSlider.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        DoubleEditSliderTest::DoubleEditSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::DoubleEditSliderTest")
        {}

        DoubleEditSliderTest::~DoubleEditSliderTest()
        {}

        std::shared_ptr<DoubleEditSliderTest> DoubleEditSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<DoubleEditSliderTest>(new DoubleEditSliderTest(context));
        }
                
        void DoubleEditSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("DoubleEditSliderTest");
                _app = App::create(
                    context,
                    argv,
                    "DoubleEditSliderTest",
                    "Double edit slider test.");
                _window = Window::create(context, _app, "DoubleEditSliderTest");
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->tick();

                auto slider = DoubleEditSlider::create(context, nullptr, _layout);
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
                slider->setPrecision(3);
                TG_ASSERT(3 == slider->getPrecision());
                slider->setPrecision(2);
                slider->setDefaultValue(0.0);
                TG_ASSERT(0.0 == slider->getDefaultValue());
                slider->setFontRole(FontRole::Label);
                TG_ASSERT(FontRole::Label == slider->getFontRole());
                slider->setFontRole(FontRole::Mono);

                Box2I g = slider->getGeometry();
                V2I c = center(g);
                _window->setCursorPos(c);
                _window->setButton(0, true);
                _window->setCursorPos(V2I(g.max.x, c.y));
                _window->setButton(0, false);
            }
        }
    }
}

