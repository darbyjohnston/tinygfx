// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class DrawUtilTest : public test::ITest
        {
        protected:
            DrawUtilTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~DrawUtilTest();

            static std::shared_ptr<DrawUtilTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

