// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIApp/App.h>

#include <tgUIApp/Window.h>

#include <tgGL/Init.h>

#include <tgUI/IconLibrary.h>
#include <tgUI/Style.h>

#include <tgCore/Context.h>
#include <tgCore/Time.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>
#include <list>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        namespace
        {
            const std::chrono::milliseconds timeout(5);
        }
        
        struct App::Private
        {
            std::shared_ptr<FontSystem> fontSystem;
            std::shared_ptr<ui::Style> style;
            std::shared_ptr<ui::IconLibrary> iconLibrary;
            std::list<std::shared_ptr<Window> > windows;
        };
        
        void App::_init(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<app::ICmdLineArg> >& cmdLineArgs,
            const std::vector<std::shared_ptr<app::ICmdLineOption> >& cmdLineOptions)
        {
            app::IApp::_init(context, argv, name, summary, cmdLineArgs, cmdLineOptions);
            TG_P();
            gl::init(context);
            p.fontSystem = context->getSystem<FontSystem>();
            p.style = ui::Style::create(context);
            p.iconLibrary = ui::IconLibrary::create(context);
        }

        App::App() :
            _p(new Private)
        {}

        App::~App()
        {}

        std::shared_ptr<App> App::create(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<app::ICmdLineArg> >& cmdLineArgs,
            const std::vector<std::shared_ptr<app::ICmdLineOption> >& cmdLineOptions)
        {
            auto out = std::shared_ptr<App>(new App);
            out->_init(context, argv, name, summary, cmdLineArgs, cmdLineOptions);
            return out;
        }
        
        void App::addWindow(const std::shared_ptr<Window>& window)
        {
            TG_P();
            p.windows.push_back(window);
        }

        void App::removeWindow(const std::shared_ptr<Window>& window)
        {
            TG_P();
            const auto i = std::find(p.windows.begin(), p.windows.end(), window);
            if (i != p.windows.end())
            {
                p.windows.erase(i);
            }
        }
        
        int App::run()
        {
            TG_P();
            const int exit = getExit();
            if (0 == exit)
            {
                auto t0 = std::chrono::steady_clock::now();                
                while (!p.windows.empty())
                {
                    glfwPollEvents();

                    _context->tick();

                    auto i = p.windows.begin();
                    while (i != p.windows.end())
                    {
                        ui::TickEvent tickEvent(
                            p.fontSystem,
                            p.style,
                            p.iconLibrary);
                        (*i)->tickEvent(true, true, tickEvent);

                        if ((*i)->shouldClose())
                        {
                            i = p.windows.erase(i);
                        }
                        else
                        {
                            ++i;
                        }
                    }

                    auto t1 = std::chrono::steady_clock::now();
                    sleep(timeout, t0, t1);
                    t1 = std::chrono::steady_clock::now();
                    const std::chrono::duration<double> diff = t1 - t0;
                    //std::cout << "tick: " << diff.count() << std::endl;
                    t0 = t1;
                }
            }
            return exit;
        }
    }
}

