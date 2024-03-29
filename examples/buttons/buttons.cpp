// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "buttons.h"

#include <tgUIApp/App.h>

#include <tgUI/CheckBox.h>
#include <tgUI/GroupBox.h>
#include <tgUI/PushButton.h>
#include <tgUI/ListButton.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ScrollWidget.h>
#include <tgUI/ToolButton.h>

#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace examples
    {
        namespace buttons
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

                // Create push buttons.
                auto groupBox = GroupBox::create(context, "Push Buttons", scrollLayout);
                auto hLayout = HorizontalLayout::create(context, groupBox);
                auto pushButton = PushButton::create(
                    context,
                    "Push",
                    hLayout);
                pushButton->setClickedCallback(
                    []
                    {
                        std::cout << "Push" << std::endl;
                    });
                pushButton = PushButton::create(
                    context,
                    "Disabled",
                    hLayout);
                pushButton->setEnabled(false);

                // Create list buttons.
                groupBox = GroupBox::create(context, "List Buttons", scrollLayout);
                auto vLayout = VerticalLayout::create(context, groupBox);
                vLayout->setSpacingRole(SizeRole::None);
                _listButtonGroup = ButtonGroup::create(context, ButtonGroupType::Toggle);
                _listButtonGroup->setCheckedCallback(
                    [](int index, bool value)
                    {
                        std::cout << Format("List {0}: {1}").arg(index).arg(value) << std::endl;
                    });
                for (size_t i = 0; i < 3; ++i)
                {
                    auto listButton = ListButton::create(
                        context,
                        Format("List {0}").arg(i),
                        vLayout);
                    listButton->setCheckable(true);
                    _listButtonGroup->addButton(listButton);
                }
                auto listButton = ListButton::create(
                    context,
                    "Disabled",
                    vLayout);
                listButton->setEnabled(false);
                _listButtonGroup->addButton(listButton);

                // Create tool buttons.
                groupBox = GroupBox::create(context, "Tool Buttons", scrollLayout);
                hLayout = HorizontalLayout::create(context, groupBox);
                hLayout->setSpacingRole(SizeRole::None);
                _toolButtonGroup = ButtonGroup::create(context, ButtonGroupType::Radio);
                _toolButtonGroup->setCheckedCallback(
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
                for (size_t i = 0; i < 3; ++i)
                {
                    auto toolButton = ToolButton::create(context, hLayout);
                    toolButton->setCheckable(true);
                    toolButton->setChecked(0 == i);
                    toolButton->setIcon(toolIcons[i]);
                    _toolButtonGroup->addButton(toolButton);
                }
                auto toolButton = ToolButton::create(
                    context,
                    "Disabled",
                    hLayout);
                toolButton->setEnabled(false);
                _toolButtonGroup->addButton(toolButton);

                // Create check boxes.
                groupBox = GroupBox::create(context, "Check Boxes", scrollLayout);
                vLayout = VerticalLayout::create(context, groupBox);
                auto checkBox = CheckBox::create(
                    context,
                    "Check",
                    vLayout);
                checkBox->setCheckedCallback(
                    [](bool value)
                    {
                        std::cout << Format("Check: {0}").arg(value) << std::endl;
                    });
                checkBox = CheckBox::create(
                    context,
                    "Disabled",
                    vLayout);
                checkBox->setEnabled(false);
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
        auto app = App::create(context, args, "buttons", "Buttons example");
        if (0 == app->getExit())
        {
            auto window = tg::examples::buttons::Window::create(
                context,
                "buttons",
                Size2I(1280, 720));
            app->addWindow(window);
            window->show();
        }
        r = app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

