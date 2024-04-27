// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class DoubleEditTest : public test::ITest
        {
        protected:
            DoubleEditTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~DoubleEditTest();

            static std::shared_ptr<DoubleEditTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

