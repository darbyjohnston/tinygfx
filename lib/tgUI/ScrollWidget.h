// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/ScrollArea.h>

namespace tg
{
    namespace ui
    {
        //! \name Layouts
        ///@{
        
        //! Scroll widget.
        class ScrollWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                ScrollType,
                const std::shared_ptr<IWidget>& parent);

            ScrollWidget();

        public:
            virtual ~ScrollWidget();

            //! Create a new widget.
            static std::shared_ptr<ScrollWidget> create(
                const std::shared_ptr<core::Context>&,
                ScrollType = ScrollType::Both,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the widget.
            void setWidget(const std::shared_ptr<IWidget>&);

            //! Get the viewport geometry.
            core::Box2I getViewport() const;

            //! Get the scroll size.
            const core::V2I& getScrollSize() const;

            //! Get the scroll position.
            const core::V2I& getScrollPos() const;

            //! Set the scroll position.
            void setScrollPos(const core::V2I&, bool clamp = true);

            //! Set the scroll position callback.
            void setScrollPosCallback(const std::function<void(const core::V2I&)>&);

            //! Get whether the scroll bars are visible.
            bool areScrollBarsVisible() const;

            //! Set whether the scroll bars are visible.
            void setScrollBarsVisible(bool);

            //! Set whether scroll events are enabled.
            void setScrollEventsEnabled(bool);

            //! Set whether the scroll area has a border.
            void setBorder(bool);

            //! Set the margin role.
            void setMarginRole(SizeRole);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void scrollEvent(ScrollEvent&) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            int getLineStep() const;
            int getPageStep() const;

            TG_PRIVATE();
        };
        
        ///@}
    }
}
