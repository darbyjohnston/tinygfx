// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class MatrixTest : public tests::ITest
        {
        protected:
            MatrixTest();

        public:
            static std::shared_ptr<MatrixTest> create();

            void run() override;

        private:
            void _ctors();
            void _transforms();
            void _operators();
        };
    }
}
