// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class EventTest : public test::ITest
        {
        protected:
            EventTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~EventTest();

            static std::shared_ptr<EventTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _enums();
        };
    }
}

