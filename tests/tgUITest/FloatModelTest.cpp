// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/FloatModelTest.h>

#include <tgUI/FloatModel.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>
#include <tgCore/Math.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        FloatModelTest::FloatModelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::FloatModelTest")
        {}

        FloatModelTest::~FloatModelTest()
        {}

        std::shared_ptr<FloatModelTest> FloatModelTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FloatModelTest>(new FloatModelTest(context));
        }
                
        void FloatModelTest::run()
        {
            if (auto context = _context.lock())
            {
                auto model = FloatModel::create(context);

                float value = 0.F;
                RangeF range;
                bool hasDefaultValue = false;
                auto valueObserver = ValueObserver<float>::create(
                    model->observeValue(),
                    [&value](float v)
                    {
                        value = v;
                    });
                auto rangeObserver = ValueObserver<RangeF>::create(
                    model->observeRange(),
                    [&range](const RangeF& r)
                    {
                        range = r;
                    });
                auto defaultValueObserver = ValueObserver<bool>::create(
                    model->observeHasDefaultValue(),
                    [&hasDefaultValue](bool value)
                    {
                        hasDefaultValue = value;
                    });

                model->setValue(.9F);
                TG_ASSERT(.9F == model->getValue());
                TG_ASSERT(.9F == value);

                model->setRange(RangeF(0.F, .5F));
                TG_ASSERT(RangeF(0.F, .5F) == model->getRange());
                TG_ASSERT(RangeF(0.F, .5F) == range);
                TG_ASSERT(.5F == value);

                model->setStep(.2F);
                TG_ASSERT(.2F == model->getStep());
                model->decrementStep();
                TG_ASSERT(fuzzyCompare(.3F, value));
                model->incrementStep();
                TG_ASSERT(fuzzyCompare(.5F, value));

                model->setLargeStep(.3F);
                TG_ASSERT(.3F == model->getLargeStep());
                model->decrementLargeStep();
                TG_ASSERT(fuzzyCompare(.2F, value));
                model->incrementLargeStep();
                TG_ASSERT(fuzzyCompare(.5F, value));

                model->setDefaultValue(0.F);
                TG_ASSERT(0.F == model->getDefaultValue());
                TG_ASSERT(hasDefaultValue);
                model->setDefaultValue();
                TG_ASSERT(0.F == value);
                model->clearDefaultValue();
                TG_ASSERT(!hasDefaultValue);
            }
        }
    }
}
