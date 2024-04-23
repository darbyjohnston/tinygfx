// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/DoubleModelTest.h>

#include <tgUI/DoubleModel.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>
#include <tgCore/Math.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        DoubleModelTest::DoubleModelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::DoubleModelTest")
        {}

        DoubleModelTest::~DoubleModelTest()
        {}

        std::shared_ptr<DoubleModelTest> DoubleModelTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<DoubleModelTest>(new DoubleModelTest(context));
        }
                
        void DoubleModelTest::run()
        {
            if (auto context = _context.lock())
            {
                auto model = DoubleModel::create(context);

                double value = 0.0;
                RangeD range;
                bool hasDefaultValue = false;
                auto valueObserver = ValueObserver<double>::create(
                    model->observeValue(),
                    [&value](double v)
                    {
                        value = v;
                    });
                auto rangeObserver = ValueObserver<RangeD>::create(
                    model->observeRange(),
                    [&range](const RangeD& r)
                    {
                        range = r;
                    });
                auto defaultValueObserver = ValueObserver<bool>::create(
                    model->observeHasDefaultValue(),
                    [&hasDefaultValue](bool value)
                    {
                        hasDefaultValue = value;
                    });

                model->setValue(0.9);
                TG_ASSERT(0.9 == model->getValue());
                TG_ASSERT(0.9 == value);

                model->setRange(RangeD(0.0, 0.5));
                TG_ASSERT(RangeD(0.0, 0.5) == model->getRange());
                TG_ASSERT(RangeD(0.0, 0.5) == range);
                TG_ASSERT(0.5 == value);

                model->setStep(0.2);
                TG_ASSERT(0.2 == model->getStep());
                model->decrementStep();
                TG_ASSERT(fuzzyCompare(0.3, value));
                model->incrementStep();
                TG_ASSERT(fuzzyCompare(0.5, value));

                model->setLargeStep(0.3);
                TG_ASSERT(0.3 == model->getLargeStep());
                model->decrementLargeStep();
                TG_ASSERT(fuzzyCompare(0.2, value));
                model->incrementLargeStep();
                TG_ASSERT(fuzzyCompare(0.5, value));

                model->setDefaultValue(0.0);
                TG_ASSERT(0.0 == model->getDefaultValue());
                TG_ASSERT(hasDefaultValue);
                model->setDefaultValue();
                TG_ASSERT(0.0 == value);
                model->clearDefaultValue();
                TG_ASSERT(!hasDefaultValue);
            }
        }
    }
}

