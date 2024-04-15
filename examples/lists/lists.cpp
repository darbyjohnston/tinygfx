// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "lists.h"

#include <tgUIApp/App.h>

#include <tgUI/GroupBox.h>
#include <tgUI/Label.h>
#include <tgUI/ListWidget.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ScrollWidget.h>

#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace examples
    {
        namespace lists
        {
            void Window::_init(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                const Size2I& size)
            {
                ui::Window::_init(context, name, size);

                // Create the scroll widget.
                auto scrollWidget = ScrollWidget::create(
                    context,
                    ScrollType::Both,
                    shared_from_this());
                auto scrollLayout = VerticalLayout::create(context);
                scrollLayout->setMarginRole(SizeRole::Margin);
                scrollWidget->setWidget(scrollLayout);

                // Create list widgets.
                auto groupBox = GroupBox::create(context, "List Widgets", scrollLayout);
                auto hLayout = HorizontalLayout::create(context, groupBox);
                auto listWidget = ListWidget::create(context, ButtonGroupType::Click, hLayout);
                std::vector<std::string> items;
                for (size_t i = 0; i < 100; ++i)
                {
                    items.push_back(Format("Click {0}").arg(i));
                }
                listWidget->setItems(items);
                listWidget->setCallback(
                    [](int value)
                    {
                        std::cout << "Click: " << value << std::endl;
                    });
                listWidget = ListWidget::create(context, ButtonGroupType::Radio, hLayout);
                items.clear();
                for (size_t i = 0; i < 100; ++i)
                {
                    items.push_back(Format("Radio {0}").arg(i));
                }
                listWidget->setItems(items);
                listWidget->setCallback(
                    [](int value)
                    {
                        std::cout << "Radio: " << value << std::endl;
                    });
                listWidget = ListWidget::create(context, ButtonGroupType::Toggle, hLayout);
                items.clear();
                for (size_t i = 0; i < 100; ++i)
                {
                    items.push_back(Format("Toggle {0}").arg(i));
                }
                listWidget->setItems(items);
                listWidget->setCallback(
                    [](int value)
                    {
                        std::cout << "Toggle: " << value << std::endl;
                    });
            }

            Window::~Window()
            {}

            std::shared_ptr<Window> Window::create(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                const Size2I& size)
            {
                auto out = std::shared_ptr<Window>(new Window);
                out->_init(context, name, size);
                return out;
            }
        }
    }
}

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = tg::app::convert(argc, argv);
        auto app = App::create(context, args, "lists", "Lists example");
        if (0 == app->getExit())
        {
            auto window = tg::examples::lists::Window::create(
                context,
                "lists",
                Size2I(1280, 720));
            app->addWindow(window);
            window->show();
            r = app->run();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

