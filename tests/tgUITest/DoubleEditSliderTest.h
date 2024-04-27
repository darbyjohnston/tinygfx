// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class DoubleEditSliderTest : public test::ITest
        {
        protected:
            DoubleEditSliderTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~DoubleEditSliderTest();

            static std::shared_ptr<DoubleEditSliderTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

