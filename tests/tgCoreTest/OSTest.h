// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_test
    {
        class OSTest : public test::ITest
        {
        protected:
            OSTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~OSTest();

            static std::shared_ptr<OSTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _env();
        };
    }
}

