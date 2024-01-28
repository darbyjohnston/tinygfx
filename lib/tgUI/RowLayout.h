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
        
        //! Row layout.
        class RowLayout : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                Orientation,
                const std::string& objectName,
                const std::shared_ptr<IWidget>& parent);

            RowLayout();

        public:
            virtual ~RowLayout();

            //! Create a new layout.
            static std::shared_ptr<RowLayout> create(
                const std::shared_ptr<core::Context>&,
                Orientation,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the margin role.
            void setMarginRole(SizeRole);

            //! Set the spacing role.
            void setSpacingRole(SizeRole);

            void setGeometry(const core::Box2I&) override;
            core::Box2I getChildrenClipRect() const override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void childAddedEvent(const ChildEvent&) override;
            void childRemovedEvent(const ChildEvent&) override;

        private:
            TG_PRIVATE();
        };

        //! Horizontal layout.
        class HorizontalLayout : public RowLayout
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            HorizontalLayout();

        public:
            virtual ~HorizontalLayout();

            //! Create a new layout.
            static std::shared_ptr<HorizontalLayout> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);
        };

        //! Vertical layout.
        class VerticalLayout : public RowLayout
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            VerticalLayout();

        public:
            virtual ~VerticalLayout();

            //! Create a new layout.
            static std::shared_ptr<VerticalLayout> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);
        };
        
        ///@}
    }
}
