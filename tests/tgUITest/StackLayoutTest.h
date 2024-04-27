// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class StackLayoutTest : public test::ITest
        {
        protected:
            StackLayoutTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~StackLayoutTest();

            static std::shared_ptr<StackLayoutTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

