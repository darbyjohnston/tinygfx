// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/FloatEditSliderTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/FloatEditSlider.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        FloatEditSliderTest::FloatEditSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::FloatEditSliderTest")
        {}

        FloatEditSliderTest::~FloatEditSliderTest()
        {}

        std::shared_ptr<FloatEditSliderTest> FloatEditSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FloatEditSliderTest>(new FloatEditSliderTest(context));
        }

        void FloatEditSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FloatEditSliderTest");
                auto app = App::create(
                    context,
                    argv,
                    "FloatEditSliderTest",
                    "Float edit slider test.");
                auto window = Window::create(context, app, "FloatEditSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = FloatEditSlider::create(context, nullptr, layout);
                TG_ASSERT(slider->getModel());
                float value = 0.F;
                slider->setCallback([&value](float v) { value = v; });
                slider->setValue(.9F);
                app->tick();
                TG_ASSERT(.9F == slider->getValue());
                TG_ASSERT(.9F == value);
                slider->setRange(RangeF(0.F, .5F));
                app->tick();
                TG_ASSERT(RangeF(0.F, .5F) == slider->getRange());
                TG_ASSERT(.5F == value);
                slider->setStep(.2F);
                TG_ASSERT(.2F == slider->getStep());
                slider->setLargeStep(.3F);
                TG_ASSERT(.3F == slider->getLargeStep());
                slider->setPrecision(3);
                TG_ASSERT(3 == slider->getPrecision());
                slider->setPrecision(2);
                slider->setDefaultValue(0.F);
                TG_ASSERT(0.F == slider->getDefaultValue());
                slider->setFontRole(FontRole::Label);
                TG_ASSERT(FontRole::Label == slider->getFontRole());
                slider->setFontRole(FontRole::Mono);

                Box2I g = slider->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0, true);
                window->setCursorPos(V2I(g.max.x, c.y));
                window->setButton(0, false);
            }
        }
    }
}

