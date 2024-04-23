// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/IntEditTest.h>

#include <tgUI/IntEdit.h>

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
                _app = App::create(context, argv, "IntEditTest", "Integer edit test.");
                _window = Window::create(context, "ButtonTest", Size2I(1280, 960));
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->run();

                auto edit = IntEdit::create(context, nullptr, _layout);
                TG_ASSERT(edit->getModel());
                int value = 0;
                edit->setCallback([&value](int v) { value = v; });

                edit->setValue(11);
                _app->run();
                TG_ASSERT(11 == edit->getValue());
                TG_ASSERT(11 == value);

                edit->setRange(RangeI(0, 10));
                _app->run();
                TG_ASSERT(RangeI(0, 10) == edit->getRange());
                TG_ASSERT(10 == value);

                edit->setStep(2);
                TG_ASSERT(2 == edit->getStep());
                edit->setLargeStep(3);
                TG_ASSERT(3 == edit->getLargeStep());

                edit->setFontRole(FontRole::Label);
                TG_ASSERT(FontRole::Label == edit->getFontRole());
                edit->setFontRole(FontRole::Mono);

                _window->cursorEnter(true);
                _app->run();
                _window->key(Key::Tab, true, 0);
                _app->run();
                _window->key(Key::Tab, false, 0);
                _app->run();
                _window->key(Key::A, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::A, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Delete, true, 0);
                _app->run();
                _window->key(Key::Delete, false, 0);
                _app->run();
                _window->text("1");
                _app->run();
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT(1 == value);

                _window->key(Key::Up, true, 0);
                _app->run();
                _window->key(Key::Up, false, 0);
                _app->run();
                TG_ASSERT(3 == value);
                _window->key(Key::PageUp, true, 0);
                _app->run();
                _window->key(Key::PageUp, false, 0);
                _app->run();
                TG_ASSERT(6 == value);
                _window->key(Key::PageDown, true, 0);
                _app->run();
                _window->key(Key::PageDown, false, 0);
                _app->run();
                TG_ASSERT(3 == value);
                _window->key(Key::Down, true, 0);
                _app->run();
                _window->key(Key::Down, false, 0);
                _app->run();
                TG_ASSERT(1 == value);
            }
        }
    }
}

