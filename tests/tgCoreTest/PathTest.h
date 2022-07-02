// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class PathTest : public tests::ITest
        {
        protected:
            PathTest();

        public:
            static std::shared_ptr<PathTest> create();

            void run() override;
        };
    }
}
