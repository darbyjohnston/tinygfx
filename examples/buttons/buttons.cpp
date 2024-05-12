// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "buttons.h"

#include <tgUIApp/App.h>

#include <tgUI/CheckBox.h>
#include <tgUI/GroupBox.h>
#include <tgUI/PushButton.h>
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

                // Create the layout.
                auto layout = VerticalLayout::create(context);
                layout->setMarginRole(SizeRole::Margin);
                auto scrollWidget = ScrollWidget::create(
                    context,
                    ScrollType::Both,
                    shared_from_this());
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
                pushButton = PushButton::create(context, "Disabled", hLayout);
                pushButton->setEnabled(false);

                // Create tool buttons.
                groupBox = GroupBox::create(context, "Tool Buttons", layout);
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
                auto toolButton = ToolButton::create(context, "Disabled", hLayout);
                toolButton->setEnabled(false);
                _toolButtonGroup->addButton(toolButton);

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
        r = app->getExit();
        if (0 == r)
        {
            auto window = tg::examples::buttons::Window::create(
                context,
                "buttons",
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

