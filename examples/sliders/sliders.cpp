// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIApp/App.h>
#include <tgUIApp/Window.h>

#include <tgUI/GroupBox.h>
#include <tgUI/DoubleEditSlider.h>
#include <tgUI/FloatEditSlider.h>
#include <tgUI/IntEditSlider.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ScrollWidget.h>

#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

TG_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = tg::app::convert(argc, argv);
        auto app = App::create(context, args, "sliders", "Sliders example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = Window::create(
            context,
            "sliders",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both, window);
        scrollWidget->setWidget(layout);

        // Create integer sliders.
        auto groupBox = GroupBox::create(context, "Integer Sliders", layout);
        auto vLayout = VerticalLayout::create(context, groupBox);
        auto intEditSlider = IntEditSlider::create(context, nullptr, vLayout);
        intEditSlider->setCallback(
            [](int value)
            {
                std::cout << Format("Int: {0}").arg(value) << std::endl;
            });
        intEditSlider = IntEditSlider::create(context, nullptr, vLayout);
        intEditSlider->setRange(RangeI(100, 200));
        intEditSlider->setCallback(
            [](int value)
            {
                std::cout << Format("Int: {0}").arg(value) << std::endl;
            });
        intEditSlider = IntEditSlider::create(context, nullptr, vLayout);
        intEditSlider->setRange(RangeI(-100, 100));
        intEditSlider->setCallback(
            [](int value)
            {
                std::cout << Format("Int: {0}").arg(value) << std::endl;
            });

        // Create float sliders.
        groupBox = GroupBox::create(context, "Float Sliders", layout);
        vLayout = VerticalLayout::create(context, groupBox);
        auto floatEditSlider = FloatEditSlider::create(context, nullptr, vLayout);
        floatEditSlider->setCallback(
            [](float value)
            {
                std::cout << Format("Float: {0}").arg(value) << std::endl;
            });
        floatEditSlider = FloatEditSlider::create(context, nullptr, vLayout);
        floatEditSlider->setRange(RangeF(100.F, 200.F));
        floatEditSlider->setCallback(
            [](float value)
            {
                std::cout << Format("Float: {0}").arg(value) << std::endl;
            });
        floatEditSlider = FloatEditSlider::create(context, nullptr, vLayout);
        floatEditSlider->setRange(RangeF(-100.F, 100.F));
        floatEditSlider->setCallback(
            [](float value)
            {
                std::cout << Format("Float: {0}").arg(value) << std::endl;
            });

        // Create double sliders.
        groupBox = GroupBox::create(context, "Double Sliders", layout);
        vLayout = VerticalLayout::create(context, groupBox);
        auto doubleEditSlider = DoubleEditSlider::create(context, nullptr, vLayout);
        doubleEditSlider->setCallback(
            [](double value)
            {
                std::cout << Format("Double: {0}").arg(value) << std::endl;
            });
        doubleEditSlider = DoubleEditSlider::create(context, nullptr, vLayout);
        doubleEditSlider->setRange(RangeD(100.0, 200.0));
        doubleEditSlider->setCallback(
            [](double value)
            {
                std::cout << Format("Double: {0}").arg(value) << std::endl;
            });
        doubleEditSlider = DoubleEditSlider::create(context, nullptr, vLayout);
        doubleEditSlider->setRange(RangeD(-100.0, 100.0));
        doubleEditSlider->setCallback(
            [](double value)
            {
                std::cout << Format("Double: {0}").arg(value) << std::endl;
            });

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

