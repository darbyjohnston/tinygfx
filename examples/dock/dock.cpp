// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "dock.h"

#include <tgUIApp/App.h>
#include <tgUIApp/Window.h>

#include <tgUI/Label.h>
#include <tgUI/RowLayout.h>
#include <tgUI/Splitter.h>
#include <tgUI/ToolButton.h>

#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

int widgetCount = 0;

void createWidget(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    auto layout = VerticalLayout::create(context, parent);
    layout->setBackgroundRole(ColorRole::Blue);
    auto label = Label::create(context, Format("Widget {0}").arg(widgetCount), layout);
    label->setStretch(Stretch::Expanding);
    auto button = ToolButton::create(context, "Close", layout);
    auto layoutWeak = std::weak_ptr<IWidget>(layout);
    button->setClickedCallback(
        [layoutWeak]
        {
            if (auto layout = layoutWeak.lock())
            {
                layout->setParent(nullptr);
            }
        });
    ++widgetCount;
}

TG_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = tg::app::convert(argc, argv);
        auto app = App::create(context, args, "dock", "Dock layout example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = Window::create(
            context,
            "dock",
            Size2I(1280, 960));
        app->addWindow(window);

        auto layout = VerticalLayout::create(context, window);
        layout->setSpacingRole(SizeRole::None);
        auto splitter = Splitter::create(context, Orientation::Horizontal, layout);
        createWidget(context, splitter);
        createWidget(context, splitter);
        createWidget(context, splitter);
        auto addButton = ToolButton::create(context, "Add", layout);
        addButton->setClickedCallback(
            [context, splitter]
            {
                createWidget(context, splitter);
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

