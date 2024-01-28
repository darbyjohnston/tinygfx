// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/ObservableValue.h>
#include <tgCore/Range.h>

namespace tg
{
    namespace core
    {
        class Context;
    }
    
    namespace ui
    {
        //! Double precision floating point value model.
        class DoubleModel : public std::enable_shared_from_this<DoubleModel>
        {
            TG_NON_COPYABLE(DoubleModel);

            void _init(const std::shared_ptr<core::Context>&);

        protected:
            DoubleModel();

        public:
            ~DoubleModel();

            //! Create a new model.
            static std::shared_ptr<DoubleModel> create(
                const std::shared_ptr<core::Context>&);

            //! \name Value
            ///@{

            //! Get the value.
            double getValue() const;

            //! Set the value.
            void setValue(double);

            //! Observe the value.
            std::shared_ptr<core::IObservableValue<double> > observeValue() const;

            ///@}

            //! \name Range
            ///@{

            //! Get the range.
            const core::RangeD& getRange() const;

            //! Set the range.
            void setRange(const core::RangeD&);

            //! Observe the range.
            std::shared_ptr<core::IObservableValue<core::RangeD> > observeRange() const;

            ///@}

            //! \name Increment
            ///@{

            //! Get the increment step.
            double getStep() const;

            //! Set the increment step.
            void setStep(double);

            //! Increment the value by a step.
            void incrementStep();

            //! Decrement the value by a step.
            void decrementStep();

            //! Get the increment large step.
            double getLargeStep() const;

            //! Set the increment large step.
            void setLargeStep(double);

            //! Increment the value by a large step.
            void incrementLargeStep();

            //! Decrement the value by a large step.
            void decrementLargeStep();

            ///@}

            //! \name Default Value
            ///@{

            //! Get whether there is a default value.
            bool hasDefaultValue() const;

            //! Observe the default value.
            std::shared_ptr<core::IObservableValue<bool> > observeHasDefaultValue() const;

            //! Get the default value.
            double getDefaultValue() const;

            //! Set the default value.
            void setDefaultValue(double);

            //! Set the value to the default value.
            void setDefaultValue();

            //! Clear the default value.
            void clearDefaultValue();

            ///@}

        private:
            TG_PRIVATE();
        };
    }
}
