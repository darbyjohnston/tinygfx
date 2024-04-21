// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/ButtonTest.h>

#include <tgUI/CheckBox.h>
#include <tgUI/ListButton.h>
#include <tgUI/PushButton.h>
#include <tgUI/ToolButton.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        ButtonTest::ButtonTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::ButtonTest")
        {}

        ButtonTest::~ButtonTest()
        {}

        std::shared_ptr<ButtonTest> ButtonTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ButtonTest>(new ButtonTest(context));
        }

        void ButtonTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ButtonTest");
                _app = App::create(context, argv, "ButtonTest", "Button test.");
                _window = Window::create(context, "ButtonTest", Size2I(1280, 960));
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->run();

                PushButton::create(context, "Push", _layout);

                std::shared_ptr<IButton> button = PushButton::create(context, "Push", _layout);
                button->setObjectName("PushButton");
                _print(button->getObjectName());
                _print(button->getObjectPath());
                _test(button);
                button->setParent(nullptr);
                button.reset();

                button = ListButton::create(context, "List", _layout);
                _test(button);
                button->setParent(nullptr);
                button.reset();

                button = ToolButton::create(context, "Tool", _layout);
                _test(button);
                button->setParent(nullptr);
                button.reset();

                button = ToolButton::create(context, "Tool", _layout);
                _test(button);
                button->setParent(nullptr);
                button.reset();

                button = CheckBox::create(context, "CheckBox", _layout);
                _test(button);
                button->setParent(nullptr);
                button.reset();
            }
        }

        void ButtonTest::_test(const std::shared_ptr<ui::IButton>& button)
        {
            std::string text = "Playback";
            button->setText(text);
            button->setText(text);
            TG_ASSERT(text == button->getText());

            FontRole fontRole = FontRole::Mono;
            button->setFontRole(fontRole);
            button->setFontRole(fontRole);
            TG_ASSERT(fontRole == button->getFontRole());

            button->setCheckable(true);
            button->setCheckable(true);
            TG_ASSERT(button->isCheckable());
            button->setChecked(true);
            button->setChecked(true);
            TG_ASSERT(button->isChecked());
            button->setCheckable(false);
            TG_ASSERT(!button->isChecked());
            button->setCheckable(true);

            std::string icon = "PlaybackForward";
            button->setIcon(icon);
            button->setIcon(icon);
            TG_ASSERT(icon == button->getIcon());
            icon = "PlaybackStop";
            button->setCheckedIcon(icon);
            button->setCheckedIcon(icon);
            TG_ASSERT(icon == button->getCheckedIcon());

            ColorRole colorRole = ColorRole::Red;
            button->setBackgroundRole(colorRole);
            button->setBackgroundRole(colorRole);
            TG_ASSERT(colorRole == button->getBackgroundRole());
            colorRole = ColorRole::Green;
            button->setButtonRole(colorRole);
            button->setButtonRole(colorRole);
            TG_ASSERT(colorRole == button->getButtonRole());
            colorRole = ColorRole::Blue;
            button->setCheckedRole(colorRole);
            button->setCheckedRole(colorRole);
            TG_ASSERT(colorRole == button->getCheckedRole());

            button->hide();
            button->hide();
            _app->run();
            button->show();
            _app->run();

            button->setEnabled(false);
            button->setEnabled(false);
            _app->run();
            button->setEnabled(true);
            _app->run();

            bool hovered = false;
            button->setHoveredCallback([&hovered](bool value) { hovered = value; });
            bool pressed = false;
            button->setPressedCallback([&pressed] { pressed = true; });
            int clicks = 0;
            button->setRepeatClick(true);
            TG_ASSERT(button->hasRepeatClick());
            button->setClickedCallback([&clicks] { ++clicks; });
            bool checked = false;
            button->setCheckedCallback([&checked](bool value) { checked = value; });

            _window->cursorEnter(true);
            _window->cursorPos(center(button->getGeometry()));
            _app->run();
            TG_ASSERT(hovered);
            _window->button(0, true, 0);
            _app->run();
            TG_ASSERT(pressed);
            _window->button(0, false, 0);
            _app->run();
            TG_ASSERT(clicks);
            TG_ASSERT(checked);
            if (button->acceptsKeyFocus())
            {
                TG_ASSERT(button->hasKeyFocus());
            }
            _window->cursorPos(V2I(0, 0));
            _app->run();
            TG_ASSERT(!hovered);
            _window->cursorPos(center(button->getGeometry()));
            _app->run();
            _window->cursorEnter(false);

            clicks = 0;

            _window->cursorEnter(true);
            _window->cursorPos(center(button->getGeometry()));
            _app->run();
            _window->key(Key::Enter, true, 0);
            _app->run();
            _window->key(Key::Enter, false, 0);
            _app->run();
            TG_ASSERT(clicks);
            TG_ASSERT(!checked);

            _window->key(Key::Escape, true, 0);
            _app->run();
            _window->key(Key::Escape, false, 0);
            _app->run();
            if (button->acceptsKeyFocus())
            {
                TG_ASSERT(!button->hasKeyFocus());
            }

            _window->key(Key::Tab, true, 0);
            _app->run();
            _window->key(Key::Tab, false, 0);
            _app->run();
            _window->key(Key::Tab, true, 0);
            _app->run();
            _window->key(Key::Tab, false, 0);
            _app->run();
            if (button->acceptsKeyFocus())
            {
                TG_ASSERT(button->hasKeyFocus());
            }
            _window->hide();
            _window->show();
            if (button->acceptsKeyFocus())
            {
                TG_ASSERT(!button->hasKeyFocus());
            }
            _window->cursorEnter(true);
            _app->run();
            _window->key(Key::Tab, true, static_cast<int>(KeyModifier::Shift));
            _app->run();
            _window->key(Key::Tab, false, static_cast<int>(KeyModifier::Shift));
            _app->run();
            if (button->acceptsKeyFocus())
            {
                TG_ASSERT(button->hasKeyFocus());
            }

            _window->cursorPos(center(button->getGeometry()));
            _app->run();
            _window->hide();
            _window->show();
            _window->cursorPos(center(button->getGeometry()));
            _app->run();
            _window->button(0, true, 0);
            _app->run();
            _window->hide();
            _window->show();
            _window->cursorPos(center(button->getGeometry()));
            _app->run();
            _window->key(Key::Enter, true, 0);
            _app->run();
            _window->hide();
            _window->show();
        }
    }
}

