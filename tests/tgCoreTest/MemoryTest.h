// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class MemoryTest : public tests::ITest
        {
        protected:
            MemoryTest();

        public:
            static std::shared_ptr<MemoryTest> create();

            void run() override;

        private:
            void _enums();
            void _endian();
        };
    }
}
