// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class StringFormatTest : public tests::ITest
        {
        protected:
            StringFormatTest();

        public:
            static std::shared_ptr<StringFormatTest> create();

            void run() override;
        };
    }
}
