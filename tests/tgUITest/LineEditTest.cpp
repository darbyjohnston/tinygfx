// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/LineEditTest.h>

#include <tgUI/IClipboard.h>
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
                edit->setText("Test");
                TG_ASSERT("Test" == edit->getText());
                edit->clearText();
                TG_ASSERT(edit->getText().empty());

                edit->setFormat("00.00");
                edit->setFormat("00.00");
                TG_ASSERT("00.00" == edit->getFormat());
                edit->setFormat("");

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

                _window->key(Key::A, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::A, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::C, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::C, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                TG_ASSERT("Test" == _window->getClipboard()->getText());
                _window->key(Key::X, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::X, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                TG_ASSERT(textChanged.empty());
                _window->key(Key::V, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::V, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                TG_ASSERT("Test" == textChanged);
                _window->key(Key::A, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::A, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::V, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::V, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                TG_ASSERT("Test" == textChanged);

                _window->key(Key::Left, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Left, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Right, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Right, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Home, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Home, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Delete, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Delete, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                TG_ASSERT("est" == textChanged);
                _window->key(Key::End, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::End, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Backspace, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Backspace, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                TG_ASSERT("es" == textChanged);
                _window->key(Key::A, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::A, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Backspace, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Backspace, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                TG_ASSERT(textChanged.empty());

                _window->key(Key::Escape, true, static_cast<int>(KeyModifier::Control));
                _app->run();
                _window->key(Key::Escape, false, static_cast<int>(KeyModifier::Control));
                _app->run();
                TG_ASSERT(!edit->hasKeyFocus());

                edit->hide();
                _app->run();
                edit->show();
                _app->run();
                edit->setEnabled(false);
                _app->run();
                edit->setEnabled(true);
            }
        }
    }
}

