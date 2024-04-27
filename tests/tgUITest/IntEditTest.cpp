// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/IntEditTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/IntEdit.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        IntEditTest::IntEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::IntEditTest")
        {}

        IntEditTest::~IntEditTest()
        {}

        std::shared_ptr<IntEditTest> IntEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IntEditTest>(new IntEditTest(context));
        }
                
        void IntEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("IntEditTest");
                auto app = App::create(
                    context,
                    argv,
                    "IntEditTest",
                    "Integer edit test.");
                auto window = Window::create(context, app, "IntEditTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto edit = IntEdit::create(context, nullptr, layout);
                TG_ASSERT(edit->getModel());
                int value = 0;
                edit->setCallback([&value](int v) { value = v; });
                edit->setValue(11);
                app->tick();
                TG_ASSERT(11 == edit->getValue());
                TG_ASSERT(11 == value);
                edit->setRange(RangeI(0, 10));
                app->tick();
                TG_ASSERT(RangeI(0, 10) == edit->getRange());
                TG_ASSERT(10 == value);
                edit->setStep(2);
                TG_ASSERT(2 == edit->getStep());
                edit->setLargeStep(3);
                TG_ASSERT(3 == edit->getLargeStep());
                edit->setFontRole(FontRole::Label);
                TG_ASSERT(FontRole::Label == edit->getFontRole());
                edit->setFontRole(FontRole::Mono);

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::Delete);
                window->setText("1");
                window->setKey(Key::Enter);
                TG_ASSERT(1 == value);

                window->setKey(Key::Up);
                TG_ASSERT(3 == value);
                window->setKey(Key::PageUp);
                TG_ASSERT(6 == value);
                window->setKey(Key::PageDown);
                TG_ASSERT(3 == value);
                window->setKey(Key::Down);
                TG_ASSERT(1 == value);
            }
        }
    }
}

