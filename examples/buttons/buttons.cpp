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
#include <tgUI/ToolButton.h>

#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

void MainWindow::_init(
    const std::shared_ptr<Context>& context,
    const std::string& name,
    const Size2I& size)
{
    Window::_init(context, name, size);
    
    // Create the layout and scroll widget.
    auto layout = VerticalLayout::create(context);
    layout->setMarginRole(SizeRole::Margin);
    _scrollWidget = ScrollWidget::create(
        context,
        ScrollType::Both,
        shared_from_this());
    _scrollWidget->setWidget(layout);
    
    // Create push buttons.
    auto groupBox = GroupBox::create(context, "Push Buttons", layout);
    auto hLayout = HorizontalLayout::create(context, groupBox);
    auto pushButton = PushButton::create(
        context,
        "Push",
        hLayout);
    pushButton = PushButton::create(
        context,
        "Disabled",
        hLayout);
    pushButton->setEnabled(false);

    // Create list buttons.
    groupBox = GroupBox::create(context, "List Buttons", layout);
    auto vLayout = VerticalLayout::create(context, groupBox);
    vLayout->setSpacingRole(SizeRole::None);
    _listButtonGroup = ButtonGroup::create(context, ButtonGroupType::Toggle);
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
    groupBox = GroupBox::create(context, "Tool Buttons", layout);
    hLayout = HorizontalLayout::create(context, groupBox);
    hLayout->setSpacingRole(SizeRole::None);
    _toolButtonGroup = ButtonGroup::create(context, ButtonGroupType::Radio);
    for (size_t i = 0; i < 3; ++i)
    {
        auto toolButton = ToolButton::create(
            context,
            Format("Tool {0}").arg(i),
            hLayout);
        toolButton->setCheckable(true);
        toolButton->setChecked(0 == i);
        _toolButtonGroup->addButton(toolButton);
    }
    auto toolButton = ToolButton::create(
        context,
        "Disabled",
        hLayout);
    toolButton->setEnabled(false);
    _toolButtonGroup->addButton(toolButton);
    
    // Create check boxes.
    groupBox = GroupBox::create(context, "Check Boxes", layout);
    vLayout = VerticalLayout::create(context, groupBox);
    auto checkBox = CheckBox::create(
        context,
        "Check",
        vLayout);
    checkBox = CheckBox::create(
        context,
        "Disabled",
        vLayout);
    checkBox->setEnabled(false);
}

MainWindow::~MainWindow()
{}

std::shared_ptr<MainWindow> MainWindow::create(
    const std::shared_ptr<Context>& context,
    const std::string& name,
    const Size2I& size)
{
    auto out = std::shared_ptr<MainWindow>(new MainWindow);
    out->_init(context, name, size);
    return out;
}

void MainWindow::setGeometry(const Box2I& value)
{
    Window::setGeometry(value);
    _scrollWidget->setGeometry(value);
}

void MainWindow::sizeHintEvent(const SizeHintEvent& event)
{
    Window::sizeHintEvent(event);
    _sizeHint = _scrollWidget->getSizeHint();
}

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = app::convert(argc, argv);
        auto app = App::create(context, args, "buttons", "Buttons example");
        if (0 == app->getExit())
        {
            auto window = MainWindow::create(context, "buttons", Size2I(1280, 720));
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

