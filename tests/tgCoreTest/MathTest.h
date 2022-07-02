// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class MathTest : public tests::ITest
        {
        protected:
            MathTest();

        public:
            static std::shared_ptr<MathTest> create();

            void run() override;
        };
    }
}
