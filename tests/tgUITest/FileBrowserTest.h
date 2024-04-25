// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class FileBrowserTest : public test::ITest
        {
        protected:
            FileBrowserTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~FileBrowserTest();

            static std::shared_ptr<FileBrowserTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _enums();
            void _widget();
        };
    }
}

