// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class AppTest : public test::ITest
        {
        protected:
            AppTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~AppTest();

            static std::shared_ptr<AppTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

