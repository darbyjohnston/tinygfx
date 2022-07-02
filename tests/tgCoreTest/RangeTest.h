// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class RangeTest : public tests::ITest
        {
        protected:
            RangeTest();

        public:
            static std::shared_ptr<RangeTest> create();

            void run() override;
        };
    }
}
