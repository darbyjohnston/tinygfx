// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/FloatModel.h>

#include <tgCore/Math.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct FloatModel::Private
        {
            std::shared_ptr<ObservableValue<float> > value;
            std::shared_ptr<ObservableValue<RangeF> > range;
            float step = .1F;
            float largeStep = 1.F;
            std::shared_ptr<ObservableValue<bool> > hasDefaultValue;
            float defaultValue = 0.F;
        };

        void FloatModel::_init(const std::shared_ptr<Context>&)
        {
            TG_P();
            p.value = ObservableValue<float>::create(0.F);
            p.range = ObservableValue<RangeF>::create(RangeF(0.F, 1.F));
            p.hasDefaultValue = ObservableValue<bool>::create(false);
        }

        FloatModel::FloatModel() :
            _p(new Private)
        {}

        FloatModel::~FloatModel()
        {}

        std::shared_ptr<FloatModel> FloatModel::create(
            const std::shared_ptr<Context>& context)
        {
            auto out = std::shared_ptr<FloatModel>(new FloatModel);
            out->_init(context);
            return out;
        }

        float FloatModel::getValue() const
        {
            return _p->value->get();
        }

        void FloatModel::setValue(float value)
        {
            TG_P();
            const RangeF& range = p.range->get();
            const float tmp = clamp(value, range.min(), range.max());
            _p->value->setIfChanged(tmp);
        }

        std::shared_ptr<IObservableValue<float> > FloatModel::observeValue() const
        {
            return _p->value;
        }

        const RangeF& FloatModel::getRange() const
        {
            return _p->range->get();
        }

        void FloatModel::setRange(const RangeF& range)
        {
            TG_P();
            if (p.range->setIfChanged(range))
            {
                setValue(p.value->get());
            }
        }

        std::shared_ptr<IObservableValue<RangeF> > FloatModel::observeRange() const
        {
            return _p->range;
        }

        float FloatModel::getStep() const
        {
            return _p->step;
        }

        void FloatModel::setStep(float value)
        {
            _p->step = value;
        }

        void FloatModel::incrementStep()
        {
            TG_P();
            setValue(p.value->get() + p.step);
        }

        void FloatModel::decrementStep()
        {
            TG_P();
            setValue(p.value->get() - p.step);
        }

        float FloatModel::getLargeStep() const
        {
            return _p->largeStep;
        }

        void FloatModel::setLargeStep(float value)
        {
            _p->largeStep = value;
        }

        void FloatModel::incrementLargeStep()
        {
            TG_P();
            setValue(p.value->get() + p.largeStep);
        }

        void FloatModel::decrementLargeStep()
        {
            TG_P();
            setValue(p.value->get() - p.largeStep);
        }

        bool FloatModel::hasDefaultValue() const
        {
            return _p->hasDefaultValue->get();
        }

        std::shared_ptr<IObservableValue<bool> > FloatModel::observeHasDefaultValue() const
        {
            return _p->hasDefaultValue;
        }

        float FloatModel::getDefaultValue() const
        {
            return _p->defaultValue;
        }

        void FloatModel::setDefaultValue(float value)
        {
            _p->hasDefaultValue->setIfChanged(true);
            _p->defaultValue = value;
        }

        void FloatModel::setDefaultValue()
        {
            setValue(_p->defaultValue);
        }

        void FloatModel::clearDefaultValue()
        {
            _p->hasDefaultValue->setIfChanged(false);
        }
    }
}
