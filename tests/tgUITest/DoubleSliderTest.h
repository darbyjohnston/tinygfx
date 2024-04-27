// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class DoubleSliderTest : public test::ITest
        {
        protected:
            DoubleSliderTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~DoubleSliderTest();

            static std::shared_ptr<DoubleSliderTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

