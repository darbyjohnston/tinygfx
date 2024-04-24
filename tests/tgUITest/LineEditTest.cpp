// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/LineEditTest.h>

#include <tgUI/LineEdit.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        LineEditTest::LineEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::LineEditTest")
        {}

        LineEditTest::~LineEditTest()
        {}

        std::shared_ptr<LineEditTest> LineEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<LineEditTest>(new LineEditTest(context));
        }
                
        void LineEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("LineEditTest");
                _app = App::create(context, argv, "LineEditTest", "Line edit test.");
                _window = Window::create(context, "LineEditTest", Size2I(1280, 960));
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->run();

                auto edit = LineEdit::create(context, _layout);
                std::string text;
                edit->setTextCallback(
                    [&text](const std::string& value)
                    {
                        text = value;
                    });
                std::string textChanged;
                edit->setTextChangedCallback(
                    [&textChanged](const std::string& value)
                    {
                        textChanged = value;
                    });

                edit->setText("Test");
                TG_ASSERT("Test" == edit->getText());
                edit->clearText();
                TG_ASSERT(edit->getText().empty());

                edit->setFontRole(FontRole::Mono);
                edit->setFontRole(FontRole::Mono);
                TG_ASSERT(FontRole::Mono == edit->getFontRole());
                edit->setFontRole(FontRole::Label);

                _window->cursorEnter(true);
                _app->run();
                _window->key(Key::Tab, true, 0);
                _app->run();
                _window->key(Key::Tab, false, 0);
                _app->run();
                _window->text("T");
                _app->run();
                TG_ASSERT("T" == textChanged);
                _window->text("e");
                _app->run();
                TG_ASSERT("Te" == textChanged);
                _window->text("s");
                _app->run();
                TG_ASSERT("Tes" == textChanged);
                _window->text("t");
                _app->run();
                TG_ASSERT("Test" == textChanged);
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT("Test" == text);
            }
        }
    }
}

