// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class MessageDialogTest : public test::ITest
        {
        protected:
            MessageDialogTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~MessageDialogTest();

            static std::shared_ptr<MessageDialogTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

