// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class ErrorTest : public tests::ITest
        {
        protected:
            ErrorTest();

        public:
            static std::shared_ptr<ErrorTest> create();

            void run() override;
        };
    }
}
