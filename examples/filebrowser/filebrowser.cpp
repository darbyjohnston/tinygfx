// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIApp/App.h>
#include <tgUIApp/Window.h>

#include <tgUI/FileBrowser.h>
#include <tgUI/FileEdit.h>
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
        auto app = App::create(context, args, "filebrowser", "File browser example");
        if (app->getExit() != 0)
            return app->getExit();
        context->getSystem<tg::ui::FileBrowserSystem>()->setNativeFileDialog(false);

        // Create the window.
        auto window = Window::create(
            context,
            "filebrowser",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both, window);
        scrollWidget->setWidget(layout);

        // Create the file widgets.
        for (size_t i = 0; i < 10; ++i)
        {
            FileEdit::create(context, layout);
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

