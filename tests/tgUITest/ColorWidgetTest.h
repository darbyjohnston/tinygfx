// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class ColorWidgetTest : public test::ITest
        {
        protected:
            ColorWidgetTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ColorWidgetTest();

            static std::shared_ptr<ColorWidgetTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

