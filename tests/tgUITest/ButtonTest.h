// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgTestLib/ITest.h>

#include <tgUI/IButton.h>
#include <tgUI/RowLayout.h>

namespace tg
{
    namespace ui_test
    {
        class ButtonTest : public test::ITest
        {
        protected:
            ButtonTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ButtonTest();

            static std::shared_ptr<ButtonTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                const std::shared_ptr<ui::VerticalLayout>&,
                const std::shared_ptr<ui::IButton>&);
        };
    }
}

