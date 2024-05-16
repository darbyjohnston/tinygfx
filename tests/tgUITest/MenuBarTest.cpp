// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/MenuBarTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/MenuBar.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>
#include <tgCore/Time.h>

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
                auto app = App::create(
                    context,
                    argv,
                    "MenuBarTest",
                    "Menu bar test.");
                auto window = Window::create(context, app, "MenuBarTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto menuBar = MenuBar::create(context, layout);

                auto menu = Menu::create(context);
                bool action1 = false;
                menu->addItem(std::make_shared<Action>(
                    "Action 1",
                    "FileOpen",
                    Key::O,
                    static_cast<int>(KeyModifier::Control),
                    [&action1] { action1 = true; }));
                bool action2 = false;
                auto item = std::make_shared<Action>(
                    "Action 2",
                    "Mute",
                    Key::M,
                    static_cast<int>(KeyModifier::Control),
                    [&action2](bool value) { action2 = value; });
                menu->addItem(item);
                menu->setItemChecked(item, true);
                menu->setItemEnabled(item, false);
                auto subMenu = menu->addSubMenu("Sub Menu");
                bool action3 = false;
                subMenu->addItem(std::make_shared<Action>(
                    "Action 3",
                    [&action3] { action3 = true; }));
                menuBar->addMenu("Menu 1", menu);
                app->tick();

                menu = Menu::create(context);
                bool action4 = false;
                menu->addItem(std::make_shared<Action>(
                    "Action 4",
                    Key::_4,
                    static_cast<int>(KeyModifier::Control),
                    [&action4] { action4 = true; }));
                menuBar->addMenu("Menu 2", menu);
                app->tick();

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                Box2I g = menuBar->getGeometry();
                V2I c = center(g);
                for (int x = g.min.x; x < g.max.x; ++x)
                {
                    window->setCursorPos(V2I(x, c.y));
                }
                window->setKey(Key::Escape);
                window->setKey(Key::Escape);

                window->setKey(Key::Tab);
                window->setKey(Key::Home);
                window->setKey(Key::Enter);
                window->setKey(Key::Enter);
                TG_ASSERT(action1);

                window->setKey(Key::Enter);
                window->setKey(Key::Down);
                window->setKey(Key::Up);
                window->setKey(Key::End);
                window->setKey(Key::Home);
                window->setKey(Key::Enter);

                window->setKey(Key::Right);
                window->setKey(Key::Left);
                window->setKey(Key::End);
                window->setKey(Key::Home);

                window->setKey(Key::Enter);
                window->setKey(Key::Escape);
                window->setKey(Key::Escape);

                menuBar->shortcut(Key::_4, static_cast<int>(KeyModifier::Control));
                TG_ASSERT(action4);

                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                app->setDisplayScale(2.F);
                app->tick(1000);
                app->setDisplayScale(1.F);
                app->tick(1000);

                menu->clear();
            }
        }
    }
}

