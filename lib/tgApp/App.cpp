// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgApp/App.h>

#include <tgApp/IWindow.h>

#include <algorithm>
#include <iostream>

namespace tg
{
    namespace app
    {
        namespace
        {
            void glfwErrorCallback(int, const char* description)
            {
                std::cerr << "GLFW ERROR: " << description << std::endl;
            }
        }

        void App::_init(int& argc, char** argv)
        {
            glfwSetErrorCallback(glfwErrorCallback);
            int glfwMajor = 0;
            int glfwMinor = 0;
            int glfwRevision = 0;
            glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRevision);
            //std::cout << "GLFW version: " << glfwMajor << "." << glfwMinor << "." << glfwRevision << std::endl;
            if (!glfwInit())
            {
                throw std::runtime_error("Cannot initialize GLFW");
            }
        }

        App::App()
        {}

        App::~App()
        {}

        std::shared_ptr<App> App::create(int& argc, char** argv)
        {
            auto out = std::shared_ptr<App>(new App);
            out->_init(argc, argv);
            return out;
        }

        const std::list<std::shared_ptr<IWindow> >& App::getWindows() const
        {
            return _windows;
        }

        int App::run()
        {
            int out = 0;
            while (_running && !_windows.empty())
            {
                _tick();
                auto window = _windows.begin();
                while (window != _windows.end())
                {
                    if (glfwWindowShouldClose((*window)->_glfwWindow))
                    {
                        window = _windows.erase(window);
                    }
                    else
                    {
                        if ((*window)->_repaint)
                        {
                            (*window)->_paint();
                            (*window)->_repaint = false;
                            glfwSwapBuffers((*window)->_glfwWindow);
                        }
                        ++window;
                    }
                }
                glfwPollEvents();
            }
            return out;
        }

        void App::exit()
        {
            _running = false;
        }

        void App::_tick()
        {}

        void App::_addWindow(const std::shared_ptr<IWindow>& window)
        {
            _windows.push_back(window);
        }

        void App::_removeWindow(const std::shared_ptr<IWindow>& window)
        {
            const auto i = std::find(_windows.begin(), _windows.end(), window);
            if (i != _windows.end())
            {
                _windows.erase(i);
            }
        }
    }
}