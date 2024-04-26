// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/MenuBarTest.h>

#include <tgUI/MenuBar.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        MenuBarTest::MenuBarTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::MenuBarTest")
        {}

        MenuBarTest::~MenuBarTest()
        {}

        std::shared_ptr<MenuBarTest> MenuBarTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<MenuBarTest>(new MenuBarTest(context));
        }
                
        void MenuBarTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("MenuBarTest");
                _app = App::create(context, argv, "MenuBarTest", "Menu bar test.");
                _window = Window::create(context, "MenuBarTest", Size2I(1280, 960));
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->run();

                auto menuBar = MenuBar::create(context, _layout);
                auto menu = Menu::create(context);
                bool action1 = false;
                menu->addItem(std::make_shared<Action>(
                    "Action 1",
                    [&action1] { action1 = true; }));
                menuBar->addMenu("Menu 1", menu);
                menu = Menu::create(context);
                bool action2 = false;
                menu->addItem(std::make_shared<Action>(
                    "Action 2",
                    Key::_2,
                    static_cast<int>(KeyModifier::Control),
                    [&action2] { action2 = true; }));
                menuBar->addMenu("Menu 2", menu);

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
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT(action1);
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                _window->key(Key::Escape, true, 0);
                _app->run();
                _window->key(Key::Escape, false, 0);
                _app->run();
                menuBar->shortcut(Key::_2, static_cast<int>(KeyModifier::Control));
                TG_ASSERT(action2);
            }
        }
    }
}

