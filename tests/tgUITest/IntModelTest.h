// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class IntModelTest : public test::ITest
        {
        protected:
            IntModelTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~IntModelTest();

            static std::shared_ptr<IntModelTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

