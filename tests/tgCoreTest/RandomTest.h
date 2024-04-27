// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_test
    {
        class RandomTest : public test::ITest
        {
        protected:
            RandomTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~RandomTest();

            static std::shared_ptr<RandomTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

