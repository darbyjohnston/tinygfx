// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/ValueObserverTest.h>

#include <tgCore/Assert.h>
#include <tgCore/ValueObserver.h>

namespace tg
{
    namespace core_tests
    {
        ValueObserverTest::ValueObserverTest() :
            ITest("core_tests::ValueObserverTest")
        {}

        std::shared_ptr<ValueObserverTest> ValueObserverTest::create()
        {
            return std::shared_ptr<ValueObserverTest>(new ValueObserverTest);
        }

        void ValueObserverTest::run()
        {
            auto value = observer::Value<int>::create(0);
            TINYGFX_ASSERT(0 == value->get());

            int result = 0;
            auto observer = observer::ValueObserver<int>::create(
                value,
                [&result](int value)
                {
                    result = value;
                });
            bool changed = value->setIfChanged(1);
            TINYGFX_ASSERT(changed);
            TINYGFX_ASSERT(1 == result);

            {
                int result2 = 0;
                auto observer2 = observer::ValueObserver<int>::create(
                    value,
                    [&result2](int value)
                    {
                        result2 = value;
                    });
                value->setIfChanged(2);
                TINYGFX_ASSERT(2 == result);
                TINYGFX_ASSERT(2 == result2);

                TINYGFX_ASSERT(2 == value->getObserversCount());
            }

            TINYGFX_ASSERT(1 == value->getObserversCount());
        }
    }
}
