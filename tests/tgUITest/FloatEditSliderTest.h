// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class FloatEditSliderTest : public test::ITest
        {
        protected:
            FloatEditSliderTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~FloatEditSliderTest();

            static std::shared_ptr<FloatEditSliderTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

