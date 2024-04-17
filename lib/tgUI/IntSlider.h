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
        
        //! Integer value slider.
        class IntSlider : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IntModel>&,
                const std::shared_ptr<IWidget>& parent);

            IntSlider();

        public:
            virtual ~IntSlider();

            //! Create a new widget.
            static std::shared_ptr<IntSlider> create(
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

            int _posToValue(int) const;
            int _valueToPos(int) const;

            TG_PRIVATE();
        };
        
        ///@}
    }
}
