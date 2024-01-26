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
            Window(
                const std::shared_ptr<core::Context>&,
                const std::string& name,
                const core::Size2I&);

        public:
            virtual ~Window();
            
            //! Get the window frame buffer size.
            const core::Size2I& getFrameBufferSize() const;
            
            //! Get the display scale.
            float getDisplayScale() const;

            //! Get whether the window should refresh.
            bool shouldRefresh() const;

            //! Get whether the window should close.
            bool shouldClose() const;
        
            void setGeometry(const core::Box2I&) override;
            void setVisible(bool) override;
            void tickEvent(
                bool parentsVisible,
                bool parentsEnabled,
                const TickEvent&) override;

        private:
            bool _hasSizeUpdate(const std::shared_ptr<IWidget>&) const;
            void _sizeHintEventRecursive(
                const std::shared_ptr<IWidget>&,
                const SizeHintEvent&);

            bool _hasDrawUpdate(const std::shared_ptr<IWidget>&) const;
            void _drawEventRecursive(
                const std::shared_ptr<IWidget>&,
                const core::Box2I&,
                const DrawEvent&);

            TG_PRIVATE();
        };
    }
}

