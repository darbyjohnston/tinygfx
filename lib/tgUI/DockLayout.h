// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidget.h>

namespace tg
{
    namespace ui
    {
        //! \name Layouts
        ///@{
        
        //! Base class for dock widgets.
        class IDockWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            IDockWidget();

        public:
            virtual ~IDockWidget();

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            TG_PRIVATE();
        };
        
        //! Dock layout.
        class DockLayout : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            DockLayout();

        public:
            virtual ~DockLayout();

            //! Create a new layout.
            static std::shared_ptr<DockLayout> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            TG_PRIVATE();
        };
        
        ///@}
    }
}
