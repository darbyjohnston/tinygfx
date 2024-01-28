// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Util.h>
#include <tgCore/Vector.h>

#include <memory>
#include <functional>

struct GLFWwindow;

namespace tg
{
    namespace core
    {
        class Context;
    }

    namespace gl
    {
        //! \name Windows
        ///@{
        
        //! OpenGL window options.
        enum class WindowOptions
        {
            None         = 0,
            Visible      = 1,
            DoubleBuffer = 2,
            MakeCurrent  = 4
        };

        //! OpenGL window.
        class Window : public std::enable_shared_from_this<Window>
        {
            TG_NON_COPYABLE(Window);

        protected:
            Window(
                const std::shared_ptr<core::Context>&,
                const std::string& name,
                const core::Size2I&,
                int options,
                const std::shared_ptr<Window>& share);

        public:
            virtual ~Window();

            //! Create a new window.
            static std::shared_ptr<Window> create(
                const std::shared_ptr<core::Context>&,
                const std::string& name,
                const core::Size2I&,
                int options =
                    static_cast<int>(WindowOptions::Visible) |
                    static_cast<int>(WindowOptions::DoubleBuffer) |
                    static_cast<int>(WindowOptions::MakeCurrent),
                const std::shared_ptr<Window>& share = nullptr);
        
            //! Get the GLFW window pointer.
            GLFWwindow* getGLFW() const;

            //! Get the window size.
            const core::Size2I& getSize() const;

            //! Set the window size.
            void setSize(const core::Size2I&);

            //! Get the frame buffer size.
            const core::Size2I& getFrameBufferSize() const;

            //! Get the window content scale.
            const core::V2F& getContentScale() const;

            //! Show the window.
            void show();

            //! Hide the window.
            void hide();

            //! Make the OpenGL context current.
            void makeCurrent();

            //! Release the OpenGL context.
            void doneCurrent();

            //! Get whether the window should close.
            bool shouldClose() const;

            //! Get which screen the window is on.
            int getScreen() const;

            //! Get whether the window is in full screen mode.
            bool isFullScreen() const;

            //! Set whether the window is in full screen mode.
            void setFullScreen(bool, int screen = -1);

            //! Get whether the window is floating on top.
            bool isFloatOnTop() const;

            //! Set whether the window is floating on top.
            void setFloatOnTop(bool);

            //! Swap the buffers.
            void swap();

            //! Set the window size callback.
            void setSizeCallback(
                const std::function<void(const core::Size2I&)>&);

            //! Set the frame buffer size callback.
            void setFrameBufferSizeCallback(
                const std::function<void(const core::Size2I&)>&);

            //! Set the content scale callback.
            void setContentScaleCallback(
                const std::function<void(const core::V2F&)>&);

            //! Set the window refresh callback.
            void setRefreshCallback(const std::function<void(void)>&);

            //! Set the cursor enter callback.
            void setCursorEnterCallback(const std::function<void(bool)>&);

            //! Set the cursor position callback.
            void setCursorPosCallback(const std::function<void(const core::V2F&)>&);

            //! Set the mouse button callback.
            void setButtonCallback(const std::function<void(int, int, int)>&);

            //! Set the scroll callback.
            void setScrollCallback(const std::function<void(const core::V2F&)>&);

            //! Set the key callback.
            void setKeyCallback(const std::function<void(int, int, int, int)>&);

            //! Set the character callback.
            void setCharCallback(const std::function<void(unsigned int)>&);

            //! Set the drop callback.
            void setDropCallback(const std::function<void(int, const char**)>&);

        private:
            static void _sizeCallback(GLFWwindow*, int, int);
            static void _frameBufferSizeCallback(GLFWwindow*, int, int);
            static void _windowContentScaleCallback(GLFWwindow*, float, float);
            static void _windowRefreshCallback(GLFWwindow*);
            static void _cursorEnterCallback(GLFWwindow*, int);
            static void _cursorPosCallback(GLFWwindow*, double, double);
            static void _mouseButtonCallback(GLFWwindow*, int, int, int);
            static void _scrollCallback(GLFWwindow*, double, double);
            static void _keyCallback(GLFWwindow*, int, int, int, int);
            static void _charCallback(GLFWwindow*, unsigned int);
            static void _dropCallback(GLFWwindow*, int, const char**);

            TG_PRIVATE();
        };
        
        ///@}
    }
}

