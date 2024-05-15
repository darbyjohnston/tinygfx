// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIApp/App.h>
#include <tgUIApp/Window.h>

#include <tgUI/ColorWidget.h>
#include <tgUI/MDICanvas.h>
#include <tgUI/MDIWidget.h>
#include <tgUI/ScrollWidget.h>

#include <tgCore/Format.h>
#include <tgCore/Random.h>

using namespace tg::core;
using namespace tg::ui;

TG_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = tg::app::convert(argc, argv);
        auto app = App::create(context, args, "mdi", "MDI example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        const Size2I size(1280, 720);
        auto window = Window::create(context, "mdi", size);
        app->addWindow(window);

        // Create the scroll widget.
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both, window);

        // Create the MDI canvas.
        auto canvas = MDICanvas::create(context);
        scrollWidget->setWidget(canvas);

        // Create the MDI widgets.
        Random random;
        for (size_t i = 0; i < 10; ++i)
        {
            auto colorWidget = ColorWidget::create(context);
            colorWidget->setColor(Color4F(random.getF(), random.getF(), random.getF()));
            canvas->addWidget(
                Format("Color {0}").arg(i),
                V2I(random.getI(0, size.w), random.getI(0, size.h)),
                colorWidget);
        }

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

