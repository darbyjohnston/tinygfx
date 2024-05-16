// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/TabWidgetTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/Label.h>
#include <tgUI/RowLayout.h>
#include <tgUI/TabBar.h>
#include <tgUI/TabWidget.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        TabWidgetTest::TabWidgetTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::TabWidgetTest")
        {}

        TabWidgetTest::~TabWidgetTest()
        {}

        std::shared_ptr<TabWidgetTest> TabWidgetTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<TabWidgetTest>(new TabWidgetTest(context));
        }
                
        void TabWidgetTest::run()
        {
            _bar();
            _widget();
        }

        void TabWidgetTest::_bar()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("TabWidgetTest");
                auto app = App::create(
                    context,
                    argv,
                    "TabWidgetTest",
                    "Tab widget test.");
                auto window = Window::create(context, app, "TabWidgetTest");
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
                app->tick();
                widget->addTab("Tab 2");
                tabs.push_back("Tab 2");
                TG_ASSERT(tabs == widget->getTabs());
                app->tick();
                widget->clearTabs();
                TG_ASSERT(widget->getTabs().empty());
                app->tick();
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
                app->tick();
            }
        }

        void TabWidgetTest::_widget()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("TabWidgetTest");
                auto app = App::create(
                    context,
                    argv,
                    "TabWidgetTest",
                    "Tab widget test.");
                auto window = Window::create(context, app, "TabWidgetTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget = TabWidget::create(context, layout);
                std::vector<std::string> tabs =
                {
                    "Tab 0",
                    "Tab 1",
                };
                auto label0 = Label::create(context, "Label 0");
                widget->addTab(tabs[0], label0);
                auto label1 = Label::create(context, "Label 1");
                widget->addTab(tabs[1], label1);
                TG_ASSERT(tabs == widget->getTabs());
                app->tick();
                widget->clearTabs();
                TG_ASSERT(widget->getTabs().empty());
                app->tick();
                widget->addTab(tabs[0], label0);
                widget->addTab(tabs[1], label1);
                int tab = 0;
                widget->setCallback(
                    [&tab](int value)
                    {
                        tab = value;
                    });
                widget->setCurrentTab(1);
                widget->setCurrentTab(1);
                TG_ASSERT(1 == widget->getCurrentTab());
                app->tick();

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::Right);
                window->setKey(Key::Left);
                window->setKey(Key::End);
                window->setKey(Key::Home);
                window->setKey(Key::Enter);
                TG_ASSERT(0 == widget->getCurrentTab());
                window->setKey(Key::Escape);
            }
        }
    }
}

