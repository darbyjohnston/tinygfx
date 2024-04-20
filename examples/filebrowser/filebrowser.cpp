// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "filebrowser.h"

#include <tgUIApp/App.h>

#include <tgUI/FileBrowser.h>
#include <tgUI/FileEdit.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ScrollWidget.h>

#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace examples
    {
        namespace filebrowser
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

                // Create the file widgets.
                for (size_t i = 0; i < 10; ++i)
                {
                    FileEdit::create(context, scrollLayout);
                }
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
        auto app = App::create(context, args, "filebrowser", "File browser example");
        r = app->getExit();
        if (0 == r)
        {
            context->getSystem<tg::ui::FileBrowserSystem>()->setNativeFileDialog(false);
            auto window = tg::examples::filebrowser::Window::create(
                context,
                "filebrowser",
                Size2I(1280, 720));
            app->addWindow(window);
            window->show();
            r = app->run();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

