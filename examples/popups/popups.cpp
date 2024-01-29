// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "popups.h"

#include <tgUIApp/App.h>

#include <tgUI/ComboBox.h>
#include <tgUI/ColorSwatch.h>
#include <tgUI/GroupBox.h>
#include <tgUI/RowLayout.h>

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
    
    // Create combo boxes.
    auto groupBox = GroupBox::create(context, "Combo Boxes", layout);
    auto vLayout = VerticalLayout::create(context, groupBox);
    auto comboBox = ComboBox::create(context, getEndianLabels(), vLayout);
    comboBox = ComboBox::create(context, getImageTypeLabels(), vLayout);
    
    // Create color swatches.
    groupBox = GroupBox::create(context, "Color Popups", layout);
    auto hLayout = HorizontalLayout::create(context, groupBox);
    const std::vector<Color4F> colors =
    {
        Color4F(1.F, .5F, .5F),
        Color4F(.5F, 1.F, .5F),
        Color4F(.5F, .5F, 1.F),
        Color4F(1.F, 1.F, .5F),
        Color4F(.5F, 1.F, 1.F),
        Color4F(1.F, .5F, 1.F)
    };
    for (const auto& color : colors)
    {
        auto colorSwatch = ColorSwatch::create(context, hLayout);
        colorSwatch->setColor(color);
        colorSwatch->setEditable(true);
    }
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
        auto app = App::create(context, args, "popups", "Popups example");
        if (0 == app->getExit())
        {
            auto window = MainWindow::create(context, "popups", Size2I(1280, 720));
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

