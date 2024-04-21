// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class PushButtonTest : public test::ITest
        {
        protected:
            PushButtonTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~PushButtonTest();

            static std::shared_ptr<PushButtonTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

