// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_test
    {
        class ErrorTest : public test::ITest
        {
        protected:
            ErrorTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ErrorTest();

            static std::shared_ptr<ErrorTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

