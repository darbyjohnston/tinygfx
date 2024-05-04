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
        
        //! Scroll type.
        enum class ScrollType
        {
            Both,
            Horizontal,
            Vertical,
            Menu,

            Count,
            First = Both
        };
        TG_ENUM(ScrollType);

        //! Scroll area.
        class ScrollArea : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                ScrollType,
                const std::shared_ptr<IWidget>& parent);

            ScrollArea();

        public:
            virtual ~ScrollArea();

            //! Create a new widget.
            static std::shared_ptr<ScrollArea> create(
                const std::shared_ptr<core::Context>&,
                ScrollType = ScrollType::Both,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the scroll size.
            const core::V2I& getScrollSize() const;

            //! Set the scroll size callback.
            void setScrollSizeCallback(const std::function<void(const core::V2I&)>&);

            //! Get the scroll position.
            const core::V2I& getScrollPos() const;

            //! Set the scroll position.
            void setScrollPos(const core::V2I&, bool clamp = true);

            //! Scroll to make the given box visible.
            void scrollTo(const core::Box2I&);

            //! Set the scroll position callback.
            void setScrollPosCallback(const std::function<void(const core::V2I&)>&);

            //! Get whether the scroll area has a border.
            bool hasBorder() const;

            //! Set whether the scroll area has a border.
            void setBorder(bool);

            core::Box2I getChildrenClipRect() const override;
            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;

        private:
            TG_PRIVATE();
        };
        
        ///@}
    }
}
