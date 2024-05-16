// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIApp/App.h>
#include <tgUIApp/Window.h>

#include <tgUI/CheckBox.h>
#include <tgUI/PushButton.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ScrollWidget.h>
#include <tgUI/TabWidget.h>
#include <tgUI/ToolButton.h>

#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

TG_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = tg::app::convert(argc, argv);
        auto app = App::create(context, args, "tabs", "Tabs example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = Window::create(
            context,
            "tabs",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the tab widget.
        auto tabWidget = TabWidget::create(context, window);

        // Add a tab.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        layout->setSpacingRole(SizeRole::SpacingSmall);
        for (size_t i = 0; i < 10; ++i)
        {
            PushButton::create(context, Format("Push Button {0}").arg(i), layout);
        }
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setWidget(layout);
        tabWidget->addTab("Push Buttons", scrollWidget);

        // Add a tab.
        layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        layout->setSpacingRole(SizeRole::None);
        const std::vector<std::string> icons =
        {
            "Audio",
            "Close",
            "Copy",
            "Directory",
            "File",
            "FrameNext",
            "FramePrev",
            "Mute",
            "Search",
            "Volume"
        };
        for (size_t i = 0; i < 10; ++i)
        {
            auto button = ToolButton::create(context, Format("Tool Button {0}").arg(i), layout);
            if (i < icons.size())
            {
                button->setIcon(icons[i]);
            }
        }
        scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setWidget(layout);
        tabWidget->addTab("Tool Buttons", scrollWidget);

        // Add a tab.
        layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        layout->setSpacingRole(SizeRole::None);
        for (size_t i = 0; i < 10; ++i)
        {
            CheckBox::create(context, Format("Check Box {0}").arg(i), layout);
        }
        scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setWidget(layout);
        tabWidget->addTab("Check Boxes", scrollWidget);

        window->show();
        app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

