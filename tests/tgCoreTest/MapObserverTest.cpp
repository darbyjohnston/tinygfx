// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/MapObserverTest.h>

#include <tgCore/Assert.h>
#include <tgCore/MapObserver.h>

namespace tg
{
    namespace core_tests
    {
        MapObserverTest::MapObserverTest() :
            ITest("core_tests::MapObserverTest")
        {}

        std::shared_ptr<MapObserverTest> MapObserverTest::create()
        {
            return std::shared_ptr<MapObserverTest>(new MapObserverTest);
        }

        void MapObserverTest::run()
        {
            std::map<int, int> map = {};
            auto value = observer::Map<int, int>::create(map);
            TINYGFX_ASSERT(map == value->get());

            std::map<int, int> result;
            auto observer = observer::MapObserver<int, int>::create(
                value,
                [&result](const std::map<int, int>& value)
                {
                    result = value;
                });
            map[0] = 1;
            bool changed = value->setIfChanged(map);
            TINYGFX_ASSERT(changed);
            changed = value->setIfChanged(map);
            TINYGFX_ASSERT(!changed);
            TINYGFX_ASSERT(map == result);
            TINYGFX_ASSERT(1 == value->getSize());
            TINYGFX_ASSERT(!value->isEmpty());
            TINYGFX_ASSERT(value->hasKey(0));
            TINYGFX_ASSERT(1 == value->getItem(0));

            {
                std::map<int, int> result2;
                auto observer2 = observer::MapObserver<int, int>::create(
                    value,
                    [&result2](const std::map<int, int>& value)
                    {
                        result2 = value;
                    });
                map[1] = 2;
                value->setIfChanged(map);
                TINYGFX_ASSERT(map == result);
                TINYGFX_ASSERT(map == result2);
                TINYGFX_ASSERT(2 == value->getSize());
                TINYGFX_ASSERT(!value->isEmpty());
                TINYGFX_ASSERT(value->hasKey(1));
                TINYGFX_ASSERT(2 == value->getItem(1));
                TINYGFX_ASSERT(2 == value->getObserversCount());
            }

            TINYGFX_ASSERT(1 == value->getObserversCount());
        }
    }
}
