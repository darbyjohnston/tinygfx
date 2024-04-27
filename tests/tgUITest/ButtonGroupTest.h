// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class ButtonGroupTest : public test::ITest
        {
        protected:
            ButtonGroupTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ButtonGroupTest();

            static std::shared_ptr<ButtonGroupTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

