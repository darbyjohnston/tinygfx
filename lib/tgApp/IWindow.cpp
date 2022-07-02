// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgApp/IWindow.h>

#include <tgApp/App.h>

#include <iostream>

namespace tg
{
    namespace app
    {
        void IWindow::_init(const std::shared_ptr<App>& app, const std::string& name)
        {
            _app = app;

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
            //glfwWindowHint(GLFW_SAMPLES, 8);
            //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
            _glfwWindow = glfwCreateWindow(
                _size.x,
                _size.y,
                name.c_str(),
                NULL,
                NULL);
            if (!_glfwWindow)
            {
                throw std::runtime_error("Cannot create window");
            }
            glfwSetWindowUserPointer(_glfwWindow, this);
            glfwGetFramebufferSize(_glfwWindow, &_size.x, &_size.y);
            glfwGetWindowContentScale(_glfwWindow, &_contentScale.x, &_contentScale.y);
            glfwMakeContextCurrent(_glfwWindow);
            if (!gladLoaderLoadGL())
            {
                throw std::runtime_error("Cannot initialize GLAD");
            }

            const int glMajor = glfwGetWindowAttrib(_glfwWindow, GLFW_CONTEXT_VERSION_MAJOR);
            const int glMinor = glfwGetWindowAttrib(_glfwWindow, GLFW_CONTEXT_VERSION_MINOR);
            const int glRevision = glfwGetWindowAttrib(_glfwWindow, GLFW_CONTEXT_REVISION);
            //std::cout << "OpenGL version: " << glMajor << "." << glMinor << "." << glRevision << std::endl;
            glfwSetFramebufferSizeCallback(_glfwWindow, _frameBufferSizeCallback);
            glfwSetWindowContentScaleCallback(_glfwWindow, _windowContentScaleCallback);
            glfwSetCursorEnterCallback(_glfwWindow, _cursorEnterCallback);
            glfwSetCursorPosCallback(_glfwWindow, _cursorPosCallback);
            glfwSetMouseButtonCallback(_glfwWindow, _mouseButtonCallback);
            glfwSetKeyCallback(_glfwWindow, _keyCallback);

            app->_addWindow(shared_from_this());
        }

        IWindow::IWindow()
        {}

        IWindow::~IWindow()
        {}

        const math::Vector2i& IWindow::getSize() const
        {
            return _size;
        }

        const math::Vector2f& IWindow::getContentScale() const
        {
            return _contentScale;
        }

        void IWindow::show()
        {
            glfwShowWindow(_glfwWindow);
            _resize(_size);
        }

        void IWindow::hide()
        {
            glfwHideWindow(_glfwWindow);
        }

        void IWindow::repaint()
        {
            _repaint = true;
        }

        void IWindow::_resize(const math::Vector2i&)
        {}

        void IWindow::_paint()
        {}

        void IWindow::_mouseEnter()
        {}

        void IWindow::_mouseLeave()
        {}

        void IWindow::_mousePos(const math::Vector2f&)
        {}

        void IWindow::_mouseDelta(const math::Vector2f&)
        {}

        void IWindow::_mouseButton(int, int, int)
        {}

        void IWindow::_frameBufferSizeCallback(GLFWwindow* glfwWindow, int w, int h)
        {
            IWindow* window = reinterpret_cast<IWindow*>(glfwGetWindowUserPointer(glfwWindow));
            window->_size.x = w;
            window->_size.y = h;
            window->_repaint = true;
            window->_resize(math::Vector2i(
                window->_size.x * window->_contentScale.x,
                window->_size.y * window->_contentScale.y));
        }

        void IWindow::_windowContentScaleCallback(GLFWwindow* glfwWindow, float w, float h)
        {
            IWindow* window = reinterpret_cast<IWindow*>(glfwGetWindowUserPointer(glfwWindow));
            window->_contentScale.x = w;
            window->_contentScale.y = h;
            window->_repaint = true;
            window->_resize(math::Vector2i(
                window->_size.x * window->_contentScale.x,
                window->_size.y * window->_contentScale.y));
        }

        void IWindow::_cursorEnterCallback(GLFWwindow* glfwWindow, int value)
        {
            IWindow* window = reinterpret_cast<IWindow*>(glfwGetWindowUserPointer(glfwWindow));
            if (GLFW_TRUE == value)
            {
                window->_mouseEnter();
            }
            else
            {
                window->_mouseLeave();
            }
        }

        void IWindow::_cursorPosCallback(GLFWwindow* glfwWindow, double x, double y)
        {
            IWindow* window = reinterpret_cast<IWindow*>(glfwGetWindowUserPointer(glfwWindow));
            window->_mousePosList.push_front(math::Vector2f(x, y));
            while (window->_mousePosList.size() > 2)
            {
                window->_mousePosList.pop_back();
            }
            window->_mousePos(window->_mousePosList.front());
            if (window->_mousePosList.size() > 1)
            {
                const auto delta = window->_mousePosList.front() - window->_mousePosList.back();
                window->_mouseDelta(delta);
            }
        }

        void IWindow::_mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
        {
            IWindow* window = reinterpret_cast<IWindow*>(glfwGetWindowUserPointer(glfwWindow));
            window->_mouseButton(button, action, mods);
        }

        void IWindow::_keyCallback(GLFWwindow* glfwWindow, int key, int scanCode, int action, int mods)
        {
            IWindow* window = reinterpret_cast<IWindow*>(glfwGetWindowUserPointer(glfwWindow));
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
                if (auto app = window->_app.lock())
                {
                    app->exit();
                }
                break;
            }
        }
    }
}