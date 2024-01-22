// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_test
    {
        class MemoryTest : public test::ITest
        {
        protected:
            MemoryTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~MemoryTest();

            static std::shared_ptr<MemoryTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _enums();
            void _endian();
            void _bits();
        };
    }
}

