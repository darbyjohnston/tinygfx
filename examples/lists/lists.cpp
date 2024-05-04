// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "lists.h"

#include <tgUIApp/App.h>

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
                auto listWidget = ListWidget::create(context, ButtonGroupType::Click, scrollLayout);
                std::vector<std::string> items;
                for (size_t i = 0; i < 100; ++i)
                {
                    items.push_back(Format("Click {0}").arg(i));
                }
                listWidget->setItems(items);
                listWidget->setCallback(
                    [](int index, bool)
                    {
                        std::cout << "Click: " << index << std::endl;
                    });

                listWidget = ListWidget::create(context, ButtonGroupType::Radio, scrollLayout);
                items.clear();
                for (size_t i = 0; i < 100; ++i)
                {
                    items.push_back(Format("Radio {0}").arg(i));
                }
                listWidget->setItems(items);
                listWidget->setChecked(0);
                listWidget->setCallback(
                    [](int index, bool)
                    {
                        std::cout << "Radio: " << index << std::endl;
                    });

                listWidget = ListWidget::create(context, ButtonGroupType::Toggle, scrollLayout);
                items.clear();
                for (size_t i = 0; i < 100; ++i)
                {
                    items.push_back(Format("Toggle {0}").arg(i));
                }
                listWidget->setItems(items);
                listWidget->setChecked(0);
                listWidget->setChecked(1);
                listWidget->setChecked(2);
                listWidget->setChecked(4);
                listWidget->setCallback(
                    [](int index, bool)
                    {
                        std::cout << "Toggle: " << index << std::endl;
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
        r = app->getExit();
        if (0 == r)
        {
            auto window = tg::examples::lists::Window::create(
                context,
                "lists",
                Size2I(1280, 720));
            app->addWindow(window);
            window->show();
            app->run();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

