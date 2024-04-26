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
                _app = App::create(
                    context,
                    argv,
                    "MenuBarTest",
                    "Menu bar test.");
                _window = Window::create(context, _app, "MenuBarTest");
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->tick();

                auto menuBar = MenuBar::create(context, _layout);

                auto menu = Menu::create(context);
                bool action1 = false;
                menu->addItem(std::make_shared<Action>(
                    "Action 1",
                    "FileOpen",
                    [&action1] { action1 = true; }));
                bool action2 = false;
                menu->addItem(std::make_shared<Action>(
                    "Action 2",
                    "Mute",
                    [&action2](bool value) { action2 = value; }));
                auto subMenu = menu->addSubMenu("Sub Menu");
                bool action3 = false;
                subMenu->addItem(std::make_shared<Action>(
                    "Action 3",
                    [&action3] { action3 = true; }));
                menuBar->addMenu("Menu 1", menu);

                menu = Menu::create(context);
                bool action4 = false;
                menu->addItem(std::make_shared<Action>(
                    "Action 4",
                    Key::_4,
                    static_cast<int>(KeyModifier::Control),
                    [&action4] { action4 = true; }));
                menuBar->addMenu("Menu 2", menu);

                _window->setCursorEnter(true);
                _window->setKey(Key::Tab);
                _window->setKey(Key::Enter);
                _window->setKey(Key::Enter);
                TG_ASSERT(action1);
                _window->setKey(Key::Enter);
                _window->setKey(Key::Escape);
                menuBar->shortcut(Key::_4, static_cast<int>(KeyModifier::Control));
                TG_ASSERT(action4);
            }
        }
    }
}

