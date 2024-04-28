// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/ListWidgetTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/ListWidget.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        ListWidgetTest::ListWidgetTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::ListWidgetTest")
        {}

        ListWidgetTest::~ListWidgetTest()
        {}

        std::shared_ptr<ListWidgetTest> ListWidgetTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ListWidgetTest>(new ListWidgetTest(context));
        }
                
        void ListWidgetTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ListWidgetTest");
                auto app = App::create(
                    context,
                    argv,
                    "ListWidgetTest",
                    "List widget test.");
                auto window = Window::create(context, app, "ListWidgetTest");
                app->addWindow(window);
                window->show();
                app->tick();
                _test(context, app, window, ButtonGroupType::Click);
                _test(context, app, window, ButtonGroupType::Check);
                _test(context, app, window, ButtonGroupType::Radio);
                _test(context, app, window, ButtonGroupType::Toggle);
            }
        }

        void ListWidgetTest::_test(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Window>& window,
            ButtonGroupType type)
        {
            auto widget = ListWidget::create(context, type, window);
            std::vector<std::string> items =
            {
                "Item 0",
                "Item 1",
                "Item 2",
                "Item 3"
            };
            widget->setItems(items);
            widget->setItems(items);
            TG_ASSERT(items == widget->getItems());
            app->tick();
            items.push_back("Item 4");
            widget->setItems(items);
            app->tick();
            if (ButtonGroupType::Radio == type)
            {
                widget->setCurrentItem(1);
                widget->setCurrentItem(1);
                TG_ASSERT(1 == widget->getCurrentItem());
                app->tick();
            }
            widget->setSearch("4");
            widget->setSearch("4");
            TG_ASSERT("4" == widget->getSearch());
            app->tick();
            widget->clearSearch();
            TG_ASSERT(widget->getSearch().empty());
            app->tick();

            window->setCursorEnter(true);
            window->setKey(Key::Tab);
            window->setKey(Key::Enter);
        }
    }
}

