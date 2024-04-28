// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/ScrollWidget.h>

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class ScrollWidgetTest : public test::ITest
        {
        protected:
            ScrollWidgetTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ScrollWidgetTest();

            static std::shared_ptr<ScrollWidgetTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                ui::ScrollType);
        };
    }
}

