// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class VectorTest : public tests::ITest
        {
        protected:
            VectorTest();

        public:
            static std::shared_ptr<VectorTest> create();

            void run() override;

        private:
            void _ctors();
            void _operators();
        };
    }
}
