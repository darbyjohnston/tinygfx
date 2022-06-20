// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgGlad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>
#include <list>

namespace tg
{
    namespace app
    {
        class IWindow;

        //! Application.
        class App : public std::enable_shared_from_this<App>
        {
        protected:
            void _init(int& argc, char** argv);

            App();

        public:
            virtual ~App();

            //! Create a new application.
            static std::shared_ptr<App> create(int& argc, char** argv);

            //! Get the list of windows.
            const std::list<std::shared_ptr<IWindow> >& getWindows() const;

            //! Run the application.
            int run();

            //! Exit the application.
            void exit();

        protected:
            virtual void _tick();

        private:
            void _addWindow(const std::shared_ptr<IWindow>&);
            void _removeWindow(const std::shared_ptr<IWindow>&);

            bool _running = true;
            std::list<std::shared_ptr<IWindow> > _windows;

            friend class IWindow;
        };
    }
}
