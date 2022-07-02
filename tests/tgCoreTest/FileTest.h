// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class FileTest : public tests::ITest
        {
        protected:
            FileTest();

        public:
            static std::shared_ptr<FileTest> create();

            void run() override;
        };
    }
}
