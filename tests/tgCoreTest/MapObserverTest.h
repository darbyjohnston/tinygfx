// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class MapObserverTest : public tests::ITest
        {
        protected:
            MapObserverTest();

        public:
            static std::shared_ptr<MapObserverTest> create();

            void run() override;
        };
    }
}
