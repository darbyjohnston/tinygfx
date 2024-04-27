// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWindow.h>

namespace tg
{
    namespace ui
    {
        //! Base window class.
        class Window : public IWindow
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& name,
                const core::Size2I&);

            Window();

        public:
            virtual ~Window();
            
            //! Create a new window.
            static std::shared_ptr<Window> create(
                const std::shared_ptr<core::Context>&,
                const std::string& name,
                const core::Size2I&);

            //! Get the window size.
            const core::Size2I& getSize() const;

            //! Set the window size.
            void setSize(const core::Size2I&);
            
            //! Get the window frame buffer size.
            const core::Size2I& getFrameBufferSize() const;
            
            //! Get the display scale.
            float getDisplayScale() const;

            //! Get whether the window should close.
            bool shouldClose() const;
        
            void setGeometry(const core::Box2I&) override;
            void setVisible(bool) override;
            void tickEvent(
                bool parentsVisible,
                bool parentsEnabled,
                const TickEvent&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            TG_PRIVATE();
        };
    }
}

