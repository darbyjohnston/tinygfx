// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "App.h"

#include "Window.h"

using namespace tg::core;

namespace tg
{
    namespace examples
    {
        namespace simple
        {
            struct App::Private
            {
                std::shared_ptr<Window> window;
            };
            
            void App::_init(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                std::vector<std::string>& args)
            {
                ui::IApp::_init(context, name, args);
                TG_P();
                p.window = Window::create(context, name, Size2I(1280, 720));
                addWindow(p.window);
                p.window->show();
            }

            App::App() :
                _p(new Private)
            {}

            App::~App()
            {}
            
            std::shared_ptr<App> App::create(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                std::vector<std::string>& args)
            {
                auto out = std::shared_ptr<App>(new App);
                out->_init(context, name, args);
                return out;
            }
        }
    }
}

