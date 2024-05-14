// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIApp/App.h>
#include <tgUIApp/Window.h>

#include <tgUI/Bellows.h>
#include <tgUI/CheckBox.h>
#include <tgUI/PushButton.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ScrollWidget.h>
#include <tgUI/ToolButton.h>

#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = tg::app::convert(argc, argv);
        auto app = App::create(context, args, "bellows", "Bellows example");
        r = app->getExit();
        if (0 == r)
        {
            // Create a window.
            auto window = Window::create(
                context,
                "bellows",
                Size2I(1280, 720));
            app->addWindow(window);

            // Create the layout.
            auto scrollWidget = ScrollWidget::create(context, ScrollType::Both, window);
            auto layout = VerticalLayout::create(context);
            layout->setSpacingRole(SizeRole::None);
            scrollWidget->setWidget(layout);

            // Add a bellows.
            auto vLayout = VerticalLayout::create(context);
            vLayout->setMarginRole(SizeRole::Margin);
            vLayout->setSpacingRole(SizeRole::Spacing);
            for (size_t i = 0; i < 10; ++i)
            {
                PushButton::create(context, Format("Push Button {0}").arg(i), vLayout);
            }
            auto bellows = Bellows::create(context, "Push Buttons", layout);
            bellows->setWidget(vLayout);

            // Add a bellows.
            vLayout = VerticalLayout::create(context);
            vLayout->setMarginRole(SizeRole::Margin);
            vLayout->setSpacingRole(SizeRole::Spacing);
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
                auto button = ToolButton::create(context, Format("Tool Button {0}").arg(i), vLayout);
                if (i < icons.size())
                {
                    button->setIcon(icons[i]);
                }
            }
            bellows = Bellows::create(context, "Tool Buttons", layout);
            bellows->setWidget(vLayout);

            // Add a bellows.
            vLayout = VerticalLayout::create(context);
            vLayout->setMarginRole(SizeRole::Margin);
            vLayout->setSpacingRole(SizeRole::Spacing);
            for (size_t i = 0; i < 10; ++i)
            {
                CheckBox::create(context, Format("Check Box {0}").arg(i), vLayout);
            }
            bellows = Bellows::create(context, "Check Boxes", layout);
            bellows->setWidget(vLayout);

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

