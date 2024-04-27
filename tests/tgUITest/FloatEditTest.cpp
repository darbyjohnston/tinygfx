// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/FloatEditTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/FloatEdit.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        FloatEditTest::FloatEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::FloatEditTest")
        {}

        FloatEditTest::~FloatEditTest()
        {}

        std::shared_ptr<FloatEditTest> FloatEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FloatEditTest>(new FloatEditTest(context));
        }

        void FloatEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FloatEditTest");
                auto app = App::create(
                    context,
                    argv,
                    "FloatEditTest",
                    "Float edit test.");
                auto window = Window::create(context, app, "FloatEditTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto edit = FloatEdit::create(context, nullptr, layout);
                TG_ASSERT(edit->getModel());
                float value = 0.F;
                edit->setCallback([&value](float v) { value = v; });
                edit->setValue(.9F);
                app->tick();
                TG_ASSERT(.9F == edit->getValue());
                TG_ASSERT(.9F == value);
                edit->setRange(RangeF(0.F, .5F));
                app->tick();
                TG_ASSERT(RangeF(0.F, .5F) == edit->getRange());
                TG_ASSERT(.5F == value);
                edit->setStep(.2F);
                TG_ASSERT(.2F == edit->getStep());
                edit->setLargeStep(.3F);
                TG_ASSERT(.3F == edit->getLargeStep());
                edit->setPrecision(3);
                TG_ASSERT(3 == edit->getPrecision());
                edit->setPrecision(2);
                edit->setFontRole(FontRole::Label);
                TG_ASSERT(FontRole::Label == edit->getFontRole());
                edit->setFontRole(FontRole::Mono);

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::Delete);
                window->setText("0.1");
                window->setKey(Key::Enter);
                TG_ASSERT(.1F == value);

                window->setKey(Key::Up);
                TG_ASSERT(fuzzyCompare(.3F, value));
                window->setKey(Key::PageUp);
                TG_ASSERT(fuzzyCompare(.5F, value));
                window->setKey(Key::PageDown);
                TG_ASSERT(fuzzyCompare(.2F, value));
                window->setKey(Key::Down);
                TG_ASSERT(fuzzyCompare(.0F, value));
            }
        }
    }
}

