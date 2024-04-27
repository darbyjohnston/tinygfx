// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class MenuBarTest : public test::ITest
        {
        protected:
            MenuBarTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~MenuBarTest();

            static std::shared_ptr<MenuBarTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

