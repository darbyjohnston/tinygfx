// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class FloatModelTest : public test::ITest
        {
        protected:
            FloatModelTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~FloatModelTest();

            static std::shared_ptr<FloatModelTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

