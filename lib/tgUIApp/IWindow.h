// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Size.h>
#include <tgCore/Util.h>
#include <tgCore/Vector.h>

#include <memory>

namespace tg
{
    namespace core
    {
        class Context;
    }
    
    namespace render
    {
        class IRender;
    }

    namespace ui
    {
        //! Base window class.
        class IWindow : public std::enable_shared_from_this<IWindow>
        {
            TG_NON_COPYABLE(IWindow);

        protected:
            IWindow(
                const std::shared_ptr<core::Context>&,
                const std::string& name,
                const core::Size2I&);

        public:
            virtual ~IWindow() = 0;

            //! Show the window.
            virtual void show();

            //! Hide the window.
            virtual void hide();
            
            //! Tick the window.
            virtual void tick();
            
            //! Get the window size.
            const core::Size2I& getSize() const;

            //! Get the window width.
            int getWidth() const;

            //! Get the window height.
            int getHeight() const;
            
            //! Get the window frame buffer size.
            const core::Size2I& getFrameBufferSize() const;

            //! Redraw the window.
            void redraw();

            //! Get whether the window should be redrawn.
            bool shouldRedraw() const;
            
            //! Draw the window.
            void draw();

            //! Get whether the window should close.
            bool shouldClose() const;
        
        protected:
            virtual void _draw(
                const core::V2F& contentScale,
                const std::shared_ptr<render::IRender>&) = 0;

        private:
            TG_PRIVATE();
        };
    }
}

