// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class SearchBoxTest : public test::ITest
        {
        protected:
            SearchBoxTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~SearchBoxTest();

            static std::shared_ptr<SearchBoxTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

