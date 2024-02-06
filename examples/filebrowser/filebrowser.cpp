// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "filebrowser.h"

#include <tgUIApp/App.h>

#include <tgUI/FileEdit.h>
#include <tgUI/RowLayout.h>

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

                // Create the layout.
                auto layout = VerticalLayout::create(context, shared_from_this());
                layout->setMarginRole(SizeRole::Margin);

                // Create the file widget.
                auto fileEdit = FileEdit::create(context, layout);
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
        if (0 == app->getExit())
        {
            auto window = tg::examples::filebrowser::Window::create(
                context,
                "filebrowser",
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

