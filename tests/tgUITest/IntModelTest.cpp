// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/IntModelTest.h>

#include <tgUI/IntModel.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        IntModelTest::IntModelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::IntModelTest")
        {}

        IntModelTest::~IntModelTest()
        {}

        std::shared_ptr<IntModelTest> IntModelTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IntModelTest>(new IntModelTest(context));
        }
                
        void IntModelTest::run()
        {
            if (auto context = _context.lock())
            {
                auto model = IntModel::create(context);

                int value = 0;
                RangeI range;
                bool hasDefaultValue = false;
                auto valueObserver = ValueObserver<int>::create(
                    model->observeValue(),
                    [&value](int v)
                    {
                        value = v;
                    });
                auto rangeObserver = ValueObserver<RangeI>::create(
                    model->observeRange(),
                    [&range](const RangeI& r)
                    {
                        range = r;
                    });
                auto defaultValueObserver = ValueObserver<bool>::create(
                    model->observeHasDefaultValue(),
                    [&hasDefaultValue](bool value)
                    {
                        hasDefaultValue = value;
                    });

                model->setValue(11);
                TG_ASSERT(11 == model->getValue());
                TG_ASSERT(11 == value);

                model->setRange(RangeI(0, 10));
                TG_ASSERT(RangeI(0, 10) == model->getRange());
                TG_ASSERT(RangeI(0, 10) == range);
                TG_ASSERT(10 == value);

                model->setStep(2);
                TG_ASSERT(2 == model->getStep());
                model->decrementStep();
                TG_ASSERT(8 == value);
                model->incrementStep();
                TG_ASSERT(10 == value);

                model->setLargeStep(5);
                TG_ASSERT(5 == model->getLargeStep());
                model->decrementLargeStep();
                TG_ASSERT(5 == value);
                model->incrementLargeStep();
                TG_ASSERT(10 == value);

                model->setDefaultValue(0);
                TG_ASSERT(0 == model->getDefaultValue());
                TG_ASSERT(hasDefaultValue);
                model->setDefaultValue();
                TG_ASSERT(0 == value);
                model->clearDefaultValue();
                TG_ASSERT(!hasDefaultValue);
            }
        }
    }
}

