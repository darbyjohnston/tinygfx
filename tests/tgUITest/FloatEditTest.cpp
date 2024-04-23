// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/FloatEditTest.h>

#include <tgUI/FloatEdit.h>

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
                _app = App::create(context, argv, "FloatEditTest", "Float edit test.");
                _window = Window::create(context, "ButtonTest", Size2I(1280, 960));
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->run();

                auto edit = FloatEdit::create(context, nullptr, _layout);
                float value = 0.F;
                edit->setCallback([&value](float v) { value = v; });

                edit->setValue(.9F);
                _app->run();
                TG_ASSERT(.9F == edit->getValue());
                TG_ASSERT(.9F == value);

                edit->setRange(RangeF(0.F, .5F));
                _app->run();
                TG_ASSERT(RangeF(0.F, .5F) == edit->getRange());
                TG_ASSERT(.5F == value);

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
                TG_ASSERT(.1F == value);
            }
        }
    }
}

