// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIApp/IApp.h>

#include <tgUIApp/IWindow.h>

#include <tgGL/Init.h>

#include <tgCore/Context.h>
#include <tgCore/Time.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>
#include <list>

namespace tg
{
    namespace ui
    {
        namespace
        {
            const std::chrono::milliseconds timeout(5);
        }
        
        struct IApp::Private
        {
            std::list<std::shared_ptr<IWindow> > windows;
        };
        
        void IApp::_init(
            const std::shared_ptr<core::Context>& context,
            std::vector<std::string>& argv,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<app::ICmdLineArg> >& cmdLineArgs,
            const std::vector<std::shared_ptr<app::ICmdLineOption> >& cmdLineOptions)
        {
            app::IApp::_init(context, argv, name, summary, cmdLineArgs, cmdLineOptions);
            gl::init(context);
        }

        IApp::IApp() :
            _p(new Private)
        {}

        IApp::~IApp()
        {}
        
        void IApp::addWindow(const std::shared_ptr<IWindow>& window)
        {
            TG_P();
            p.windows.push_back(window);
        }

        void IApp::removeWindow(const std::shared_ptr<IWindow>& window)
        {
            TG_P();
            const auto i = std::find(p.windows.begin(), p.windows.end(), window);
            if (i != p.windows.end())
            {
                p.windows.erase(i);
            }
        }
        
        int IApp::run()
        {
            TG_P();
            if (0 == _exit)
            {
                auto t0 = std::chrono::steady_clock::now();                
                while (!p.windows.empty())
                {
                    glfwPollEvents();

                    _context->tick();

                    auto i = p.windows.begin();
                    while (i != p.windows.end())
                    {
                        (*i)->tick();

                        if ((*i)->shouldRedraw())
                        {
                            (*i)->draw();
                        }

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
                    core::sleep(timeout, t0, t1);
                    t1 = std::chrono::steady_clock::now();
                    const std::chrono::duration<double> diff = t1 - t0;
                    //std::cout << "tick: " << diff.count() << std::endl;
                    t0 = t1;
                }
            }
            return _exit;
        }
    }
}

