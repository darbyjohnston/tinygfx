// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/FloatModel.h>
#include <tgUI/IWidget.h>

namespace tg
{
    namespace ui
    {
        //! \name Numeric Widgets
        ///@{

        //! Floating point value slider.
        class FloatSlider : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<FloatModel>&,
                const std::shared_ptr<IWidget>& parent);

            FloatSlider();

        public:
            virtual ~FloatSlider();

            //! Create a new widget.
            static std::shared_ptr<FloatSlider> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<FloatModel>& = nullptr,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the value.
            float getValue() const;

            //! Set the value.
            void setValue(float);

            //! Set the callback.
            void setCallback(const std::function<void(float)>&);

            //! Get the range.
            const core::RangeF& getRange() const;

            //! Set the range.
            void setRange(const core::RangeF&);

            //! Get the step.
            float getStep() const;

            //! Set the step.
            void setStep(float);

            //! Get the large step.
            float getLargeStep() const;

            //! Set the large step.
            void setLargeStep(float);

            //! Get the default value.
            float getDefaultValue() const;

            //! Set the default value.
            void setDefaultValue(float);

            //! Get the model.
            const std::shared_ptr<FloatModel>& getModel() const;

            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void mouseEnterEvent() override;
            void mouseLeaveEvent() override;
            void mouseMoveEvent(MouseMoveEvent&) override;
            void mousePressEvent(MouseClickEvent&) override;
            void mouseReleaseEvent(MouseClickEvent&) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            core::Box2I _getSliderGeometry() const;

            float _posToValue(int) const;
            int _valueToPos(float) const;

            TG_PRIVATE();
        };
        
        ///@}
    }
}
