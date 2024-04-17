// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidget.h>
#include <tgUI/IntModel.h>

namespace tg
{
    namespace ui
    {
        //! \name Numeric Widgets
        ///@{
        
        //! Integer value editor and slider.
        class IntEditSlider : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IntModel>&,
                const std::shared_ptr<IWidget>& parent);

            IntEditSlider();

        public:
            virtual ~IntEditSlider();

            //! Create a new widget.
            static std::shared_ptr<IntEditSlider> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IntModel>& = nullptr,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the value.
            int getValue() const;

            //! Set the value.
            void setValue(int);

            //! Set the callback.
            void setCallback(const std::function<void(int)>&);

            //! Get the range.
            const core::RangeI& getRange() const;

            //! Set the range.
            void setRange(const core::RangeI&);

            //! Get the step.
            int getStep() const;

            //! Set the step.
            void setStep(int);

            //! Get the large step.
            int getLargeStep() const;

            //! Set the large step.
            void setLargeStep(int);

            //! Get the default value.
            int getDefaultValue() const;

            //! Set the default value.
            void setDefaultValue(int);

            //! Get the model.
            const std::shared_ptr<IntModel>& getModel() const;

            //! Set the font role.
            void setFontRole(FontRole);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            TG_PRIVATE();
        };
        
        ///@}
    }
}
