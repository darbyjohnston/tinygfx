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
                std::vector<std::string>& argv)
            {
                ui::IApp::_init(
                    context,
                    argv,
                    "simple",
                    "Simple render example");
            }

            App::App() :
                _p(new Private)
            {}

            App::~App()
            {}
            
            std::shared_ptr<App> App::create(
                const std::shared_ptr<Context>& context,
                std::vector<std::string>& argv)
            {
                auto out = std::shared_ptr<App>(new App);
                out->_init(context, argv);
                return out;
            }
            
            int App::run()
            {
                TG_P();
                if (0 == _exit)
                {
                    p.window = Window::create(_context, "simple", Size2I(1280, 720));
                    addWindow(p.window);
                    p.window->show();
                }
                return IApp::run();
            }
        }
    }
}

