// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/TabBarTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/TabBar.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        TabBarTest::TabBarTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::TabBarTest")
        {}

        TabBarTest::~TabBarTest()
        {}

        std::shared_ptr<TabBarTest> TabBarTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<TabBarTest>(new TabBarTest(context));
        }
                
        void TabBarTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("TabBarTest");
                auto app = App::create(
                    context,
                    argv,
                    "TabBarTest",
                    "Tab bar test.");
                auto window = Window::create(context, app, "TabBarTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget = TabBar::create(context, layout);
                std::vector<std::string> tabs =
                {
                    "Tab 0",
                    "Tab 1",
                };
                widget->setTabs(tabs);
                widget->setTabs(tabs);
                TG_ASSERT(tabs == widget->getTabs());
                widget->addTab("Tab 2");
                tabs.push_back("Tab 2");
                TG_ASSERT(tabs == widget->getTabs());
                widget->clearTabs();
                TG_ASSERT(widget->getTabs().empty());
                widget->setTabs(tabs);
                int tab = 0;
                widget->setCallback(
                    [&tab](int value)
                    {
                        tab = value;
                    });
                widget->setCurrentTab(2);
                widget->setCurrentTab(2);
                TG_ASSERT(2 == widget->getCurrentTab());
            }
        }
    }
}

