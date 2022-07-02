// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class ValueObserverTest : public tests::ITest
        {
        protected:
            ValueObserverTest();

        public:
            static std::shared_ptr<ValueObserverTest> create();

            void run() override;
        };
    }
}
