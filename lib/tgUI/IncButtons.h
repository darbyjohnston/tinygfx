// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IButton.h>

namespace tg
{
    namespace ui
    {
        class DoubleModel;
        class FloatModel;
        class IntModel;

        //! \name Buttons
        ///@{

        //! Button for incrementing a value.
        class IncButton : public IButton
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            IncButton();

        public:
            virtual ~IncButton();

            //! Create a new widget.
            static std::shared_ptr<IncButton> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;

        private:
            TG_PRIVATE();
        };

        //! Buttons for incrementing and decrementing a value.
        class IncButtons : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            IncButtons();

        public:
            virtual ~IncButtons();

            //! Create a new widget.
            static std::shared_ptr<IncButtons> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the increment callback.
            void setIncCallback(const std::function<void(void)>&);

            //! Set the decrement callback.
            void setDecCallback(const std::function<void(void)>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        protected:
            std::shared_ptr<IncButton> _incButton;
            std::shared_ptr<IncButton> _decButton;
        };
        
        ///@}
    }
}
