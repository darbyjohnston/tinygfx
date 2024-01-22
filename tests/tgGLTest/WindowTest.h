// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace gl_test
    {
        class WindowTest : public test::ITest
        {
        protected:
            WindowTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~WindowTest();

            static std::shared_ptr<WindowTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _enums();
            void _members();
            void _functions();
        };
    }
}

