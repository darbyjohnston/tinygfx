// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/ButtonGroup.h>

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace ui_test
    {
        class ListWidgetTest : public test::ITest
        {
        protected:
            ListWidgetTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ListWidgetTest();

            static std::shared_ptr<ListWidgetTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                ui::ButtonGroupType);
        };
    }
}

