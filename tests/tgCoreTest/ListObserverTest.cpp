// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/ListObserverTest.h>

#include <tgCore/Assert.h>
#include <tgCore/ListObserver.h>

namespace tg
{
    namespace core_tests
    {
        ListObserverTest::ListObserverTest() :
            ITest("core_tests::ListObserverTest")
        {}

        std::shared_ptr<ListObserverTest> ListObserverTest::create()
        {
            return std::shared_ptr<ListObserverTest>(new ListObserverTest);
        }

        void ListObserverTest::run()
        {
            std::vector<int> list = {};
            auto value = observer::List<int>::create(list);
            TINYGFX_ASSERT(list == value->get());

            std::vector<int> result;
            auto observer = observer::ListObserver<int>::create(
                value,
                [&result](const std::vector<int>& value)
                {
                    result = value;
                });
            list.push_back(1);
            bool changed = value->setIfChanged(list);
            TINYGFX_ASSERT(changed);
            changed = value->setIfChanged(list);
            TINYGFX_ASSERT(!changed);
            TINYGFX_ASSERT(list == result);
            TINYGFX_ASSERT(1 == value->getSize());
            TINYGFX_ASSERT(!value->isEmpty());
            TINYGFX_ASSERT(1 == value->getItem(0));
            TINYGFX_ASSERT(value->contains(1));
            TINYGFX_ASSERT(0 == value->indexOf(1));

            {
                std::vector<int> result2;
                auto observer2 = observer::ListObserver<int>::create(
                    value,
                    [&result2](const std::vector<int>& value)
                    {
                        result2 = value;
                    });
                list.push_back(2);
                value->setIfChanged(list);
                TINYGFX_ASSERT(list == result);
                TINYGFX_ASSERT(list == result2);
                TINYGFX_ASSERT(2 == value->getSize());
                TINYGFX_ASSERT(2 == value->getItem(1));
                TINYGFX_ASSERT(value->contains(2));
                TINYGFX_ASSERT(1 == value->indexOf(2));
                TINYGFX_ASSERT(2 == value->getObserversCount());
            }

            TINYGFX_ASSERT(1 == value->getObserversCount());
        }
    }
}
