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
                _app = App::create(
                    context,
                    argv,
                    "LineEditTest",
                    "Line edit test.");
                _window = Window::create(context, _app, "LineEditTest");
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->tick();

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

                _window->setCursorEnter(true);
                _window->setKey(Key::Tab);
                _window->setText("T");
                TG_ASSERT("T" == textChanged);
                _window->setText("e");
                TG_ASSERT("Te" == textChanged);
                _window->setText("s");
                TG_ASSERT("Tes" == textChanged);
                _window->setText("t");
                TG_ASSERT("Test" == textChanged);
                _window->setKey(Key::Enter);
                TG_ASSERT("Test" == text);

                _window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                _window->setKey(Key::C, static_cast<int>(KeyModifier::Control));
                TG_ASSERT("Test" == _window->getClipboard()->getText());
                _window->setKey(Key::X, static_cast<int>(KeyModifier::Control));
                TG_ASSERT(textChanged.empty());
                _window->setKey(Key::V, static_cast<int>(KeyModifier::Control));
                TG_ASSERT("Test" == textChanged);
                _window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                _window->setKey(Key::V, static_cast<int>(KeyModifier::Control));
                TG_ASSERT("Test" == textChanged);

                _window->setKey(Key::Left, static_cast<int>(KeyModifier::Control));
                _window->setKey(Key::Right, static_cast<int>(KeyModifier::Control));
                _window->setKey(Key::Home, static_cast<int>(KeyModifier::Control));
                _window->setKey(Key::Delete, static_cast<int>(KeyModifier::Control));
                TG_ASSERT("est" == textChanged);
                _window->setKey(Key::End, static_cast<int>(KeyModifier::Control));
                _window->setKey(Key::Backspace, static_cast<int>(KeyModifier::Control));
                TG_ASSERT("es" == textChanged);
                _window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                _window->setKey(Key::Backspace, static_cast<int>(KeyModifier::Control));
                TG_ASSERT(textChanged.empty());
                _window->setText("T");
                _window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                _window->setText("t");
                TG_ASSERT("t" == textChanged);

                _window->setKey(Key::Escape, static_cast<int>(KeyModifier::Control));
                TG_ASSERT(!edit->hasKeyFocus());

                Box2I g = edit->getGeometry();
                const V2I c = center(g);
                _window->setCursorPos(c);
                _window->setButton(0, true);
                _window->setCursorPos(V2I(g.max.x, c.y));
                _window->setButton(0, false);

                edit->takeKeyFocus();
                edit->hide();
                _app->tick();
                edit->show();
                _app->tick();
                TG_ASSERT(!edit->hasKeyFocus());

                edit->takeKeyFocus();
                edit->setEnabled(false);
                _app->tick();
                edit->setEnabled(true);
                _app->tick();
                TG_ASSERT(!edit->hasKeyFocus());
            }
        }
    }
}

