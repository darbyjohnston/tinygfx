// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace gl_test
    {
        class RenderTest : public test::ITest
        {
        protected:
            RenderTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~RenderTest();

            static std::shared_ptr<RenderTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

