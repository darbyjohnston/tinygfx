// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/MDIWidget.h>

namespace tg
{
    namespace ui
    {
        //! MDI canvas.
        //!
        //! \todo Add support for maximizing MDI widgets.
        class MDICanvas : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            MDICanvas();

        public:
            virtual ~MDICanvas();

            //! Create a new canvas.
            static std::shared_ptr<MDICanvas> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the canvas size.
            const core::Size2I& getCanvasSize() const;

            //! Set the canvas size.
            void setCanvasSize(const core::Size2I&);

            //! Add a widget to the canvas.
            std::shared_ptr<MDIWidget> addWidget(
                const std::string& title,
                const core::V2I& pos,
                const std::shared_ptr<IWidget>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void mouseMoveEvent(MouseMoveEvent&) override;
            void mousePressEvent(MouseClickEvent&) override;
            void mouseReleaseEvent(MouseClickEvent&) override;

        private:
            TG_PRIVATE();
        };
    }
}