// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIApp/App.h>
#include <tgUIApp/Window.h>

#include <tgUI/ButtonGroup.h>
#include <tgUI/CheckBox.h>
#include <tgUI/GroupBox.h>
#include <tgUI/PushButton.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ScrollWidget.h>
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
        auto app = App::create(context, args, "buttons", "Buttons example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = Window::create(
            context,
            "buttons",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both, window);
        scrollWidget->setWidget(layout);

        // Create push buttons.
        auto groupBox = GroupBox::create(context, "Push Buttons", layout);
        auto hLayout = HorizontalLayout::create(context, groupBox);
        auto pushButton = PushButton::create(context, "Click", hLayout);
        pushButton->setClickedCallback(
            []
            {
                std::cout << "Click" << std::endl;
            });
        pushButton = PushButton::create(context, "Text", hLayout);
        pushButton->setIcon("Settings");
        pushButton = PushButton::create(context, "Disabled", hLayout);
        pushButton->setEnabled(false);

        // Create tool buttons.
        groupBox = GroupBox::create(context, "Tool Buttons", layout);
        hLayout = HorizontalLayout::create(context, groupBox);
        auto toolButtonGroup = ButtonGroup::create(context, ButtonGroupType::Radio);
        toolButtonGroup->setCheckedCallback(
            [](int index, bool value)
            {
                std::cout << Format("Tool {0}").arg(index) << std::endl;
            });
        const std::vector<std::string> toolIcons =
        {
            "PlaybackReverse",
            "PlaybackStop",
            "PlaybackForward"
        };
        auto hLayout2 = HorizontalLayout::create(context, hLayout);
        hLayout2->setSpacingRole(SizeRole::None);
        for (size_t i = 0; i < 3; ++i)
        {
            auto toolButton = ToolButton::create(context, hLayout2);
            toolButton->setCheckable(true);
            toolButton->setChecked(0 == i);
            toolButton->setIcon(toolIcons[i]);
            toolButtonGroup->addButton(toolButton);
        }
        auto toolButton = ToolButton::create(context, "Text", hLayout);
        toolButton = ToolButton::create(context, "Text", hLayout);
        toolButton->setIcon("Settings");
        toolButton = ToolButton::create(context, "Disabled", hLayout);
        toolButton->setEnabled(false);
        toolButtonGroup->addButton(toolButton);

        // Create check boxes.
        groupBox = GroupBox::create(context, "Check Boxes", layout);
        auto vLayout = VerticalLayout::create(context, groupBox);
        auto checkBox = CheckBox::create(context, "Checkable", vLayout);
        checkBox->setCheckedCallback(
            [](bool value)
            {
                std::cout << Format("Checked: {0}").arg(value) << std::endl;
            });
        checkBox = CheckBox::create(context, "Disabled", vLayout);
        checkBox->setEnabled(false);

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

