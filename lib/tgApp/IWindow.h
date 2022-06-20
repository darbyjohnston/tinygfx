// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Vector.h>

#include <tgGlad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>
#include <string>

namespace tg
{
    namespace app
    {
        class App;

        //! Base class for windows.
        class IWindow : public std::enable_shared_from_this<IWindow>
        {
        protected:
            void _init(const std::shared_ptr<App>&, const std::string& name);

            IWindow();

        public:
            virtual ~IWindow() = 0;

            //! Get the window size.
            const math::Vector2i& getSize() const;

            //! Get the window content scaling.
            const math::Vector2f& getContentScale() const;

            //! Show the window.
            void show();

            //! Hide the window.
            void hide();

            //! Repaint the window.
            void repaint();

        protected:
            virtual void _resize(const math::Vector2i&);
            virtual void _paint();

            std::weak_ptr<App> _app;

        private:
            static void _frameBufferSizeCallback(GLFWwindow*, int, int);
            static void _windowContentScaleCallback(GLFWwindow*, float, float);
            static void _keyCallback(GLFWwindow*, int, int, int, int);

            GLFWwindow* _glfwWindow = nullptr;
            math::Vector2i _size = math::Vector2i(1280, 720);
            math::Vector2f _contentScale = math::Vector2f(1.F, 1.F);
            bool _repaint = true;

            friend class App;
        };
    }
}
