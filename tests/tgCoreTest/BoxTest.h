// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_test
    {
        class BoxTest : public test::ITest
        {
        protected:
            BoxTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~BoxTest();

            static std::shared_ptr<BoxTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _members();
            void _functions();
            void _operators();
            void _serialize();
        };
    }
}

