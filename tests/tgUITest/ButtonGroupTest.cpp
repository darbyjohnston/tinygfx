// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/ButtonGroupTest.h>

#include <tgUI/ButtonGroup.h>
#include <tgUI/PushButton.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        ButtonGroupTest::ButtonGroupTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::ButtonGroupTest")
        {}

        ButtonGroupTest::~ButtonGroupTest()
        {}

        std::shared_ptr<ButtonGroupTest> ButtonGroupTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ButtonGroupTest>(new ButtonGroupTest(context));
        }
                
        void ButtonGroupTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ButtonGroupTest");
                _app = App::create(context, argv, "ButtonGroupTest", "Button group test.");
                _window = Window::create(context, "ButtonGroupTest", Size2I(1280, 960));
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->run();

                auto button0 = PushButton::create(context, "Button 0", _layout);
                auto button1 = PushButton::create(context, "Button 0", _layout);
                auto button2 = PushButton::create(context, "Button 0", _layout);
                auto group = ButtonGroup::create(context, ButtonGroupType::Click);
                group->addButton(button0);
                TG_ASSERT(!group->getButtons().empty());
                group->clearButtons();
                TG_ASSERT(group->getButtons().empty());
                group->addButton(button0);
                group->addButton(button1);
                group->addButton(button2);
                int clicked = -1;
                group->setClickedCallback(
                    [&clicked](int value)
                    {
                        clicked = value;
                    });
                _window->cursorEnter(true);
                _app->run();
                _window->key(Key::Tab, true, 0);
                _app->run();
                _window->key(Key::Tab, false, 0);
                _app->run();
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT(0 == clicked);
                _window->key(Key::Tab, true, 0);
                _app->run();
                _window->key(Key::Tab, false, 0);
                _app->run();
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT(1 == clicked);

                group = ButtonGroup::create(context, ButtonGroupType::Check);
                group->addButton(button0);
                group->addButton(button1);
                group->addButton(button2);
                clicked = -1;
                bool checked = false;
                group->setCheckedCallback(
                    [&clicked, &checked](int index, bool value)
                    {
                        clicked = index;
                        checked = value;
                    });
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT(1 == clicked);
                TG_ASSERT(checked);
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT(!checked);

                group = ButtonGroup::create(context, ButtonGroupType::Radio);
                group->addButton(button0);
                group->addButton(button1);
                group->addButton(button2);
                clicked = -1;
                checked = false;
                group->setCheckedCallback(
                    [&clicked, &checked](int index, bool value)
                    {
                        clicked = index;
                        checked = value;
                    });
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT(1 == clicked);
                TG_ASSERT(checked);
                _window->key(Key::Tab, true, 0);
                _app->run();
                _window->key(Key::Tab, false, 0);
                _app->run();
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT(2 == clicked);
                TG_ASSERT(checked);

                group = ButtonGroup::create(context, ButtonGroupType::Toggle);
                group->addButton(button0);
                group->addButton(button1);
                group->addButton(button2);
                clicked = -1;
                checked = false;
                group->setCheckedCallback(
                    [&clicked, &checked](int index, bool value)
                    {
                        clicked = index;
                        checked = value;
                    });
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT(2 == clicked);
                TG_ASSERT(!checked);
                _window->key(Key::Tab, true, 0);
                _app->run();
                _window->key(Key::Tab, false, 0);
                _app->run();
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT(0 == clicked);
                TG_ASSERT(checked);
            }
        }
    }
}

