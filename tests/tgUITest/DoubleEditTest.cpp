// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/DoubleEditTest.h>

#include <tgUI/DoubleEdit.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        DoubleEditTest::DoubleEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::DoubleEditTest")
        {}

        DoubleEditTest::~DoubleEditTest()
        {}

        std::shared_ptr<DoubleEditTest> DoubleEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<DoubleEditTest>(new DoubleEditTest(context));
        }
                
        void DoubleEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("DoubleEditTest");
                _app = App::create(context, argv, "DoubleEditTest", "Double edit test.");
                _window = Window::create(context, "ButtonTest", Size2I(1280, 960));
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->run();

                auto edit = DoubleEdit::create(context, nullptr, _layout);
                TG_ASSERT(edit->getModel());
                double value = 0.0;
                edit->setCallback([&value](double v) { value = v; });

                edit->setValue(0.9);
                _app->run();
                TG_ASSERT(0.9 == edit->getValue());
                TG_ASSERT(0.9 == value);

                edit->setRange(RangeD(0.0, 0.5));
                _app->run();
                TG_ASSERT(RangeD(0.0, 0.5) == edit->getRange());
                TG_ASSERT(0.5 == value);

                edit->setStep(0.2);
                TG_ASSERT(0.2 == edit->getStep());
                edit->setLargeStep(0.3);
                TG_ASSERT(0.3 == edit->getLargeStep());

                edit->setPrecision(3);
                TG_ASSERT(3 == edit->getPrecision());
                edit->setPrecision(2);

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
                _window->text("0.1");
                _app->run();
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT(0.1 == value);

                _window->key(Key::Up, true, 0);
                _app->run();
                _window->key(Key::Up, false, 0);
                _app->run();
                TG_ASSERT(fuzzyCompare(0.3, value));
                _window->key(Key::PageUp, true, 0);
                _app->run();
                _window->key(Key::PageUp, false, 0);
                _app->run();
                TG_ASSERT(fuzzyCompare(0.5, value));
                _window->key(Key::PageDown, true, 0);
                _app->run();
                _window->key(Key::PageDown, false, 0);
                _app->run();
                TG_ASSERT(fuzzyCompare(0.2, value));
                _window->key(Key::Down, true, 0);
                _app->run();
                _window->key(Key::Down, false, 0);
                _app->run();
                TG_ASSERT(fuzzyCompare(0.0, value));
            }
        }
    }
}

