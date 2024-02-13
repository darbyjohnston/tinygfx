// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidget.h>

namespace tg
{
    namespace ui
    {
        //! \name MDI Widgets
        ///@{

        //! MDI resize directions.
        enum class MDIResize
        {
            None,
            North,
            NorthEast,
            East,
            SouthEast,
            South,
            SouthWest,
            West,
            NorthWest,

            Count,
            First = North
        };
        TG_ENUM(MDIResize);

        //! MDI widget.
        class MDIWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& title,
                const std::shared_ptr<IWidget>& parent);

            MDIWidget();

        public:
            virtual ~MDIWidget();

            //! Create a new widget.
            static std::shared_ptr<MDIWidget> create(
                const std::shared_ptr<core::Context>&,
                const std::string& title,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the title.
            void setTitle(const std::string&);

            //! Set the widget.
            void setWidget(const std::shared_ptr<IWidget>&);

            //! Set the press callback.
            void setPressCallback(const std::function<void(bool)>&);

            //! Set the move callback.
            void setMoveCallback(const std::function<void(const core::V2I&)>&);

            //! Set the resize callback.
            void setResizeCallback(const std::function<void(MDIResize, const core::V2I&)>&);

            //! Add the margins.
            core::Box2I addMargins(const core::Box2I&) const;

            //! Remove the margins.
            core::Box2I removeMargins(const core::Box2I&) const;

            //! Remove the margins.
            core::Size2I removeMargins(const core::Size2I&) const;

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void mouseLeaveEvent() override;
            void mouseMoveEvent(MouseMoveEvent&) override;
            void mousePressEvent(MouseClickEvent&) override;
            void mouseReleaseEvent(MouseClickEvent&) override;

        private:
            TG_PRIVATE();
        };

        ///@}
    }
}
