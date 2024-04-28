// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class ScrollBarTest : public test::ITest
        {
        protected:
            ScrollBarTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ScrollBarTest();

            static std::shared_ptr<ScrollBarTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                ui::Orientation);
        };
    }
}

