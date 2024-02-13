// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidget.h>

namespace tg
{
    namespace ui
    {
        //! \name Color Widgets
        ///@{

        //! Color widget.
        //!
        //! \todo Additional color modes like grayscale, hsv, etc.
        //! \todo Add a palette for saving colors.
        //! \todo Add support for displaying pixel types like U8, U16, etc.?
        class ColorWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            ColorWidget();

        public:
            virtual ~ColorWidget();

            //! Create a new widget.
            static std::shared_ptr<ColorWidget> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the color.
            const core::Color4F& getColor() const;

            //! Set the color.
            void setColor(const core::Color4F&);

            //! Set the color callback.
            void setCallback(const std::function<void(const core::Color4F&)>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            void _colorUpdate();

            TG_PRIVATE();
        };

        ///@}
    }
}
