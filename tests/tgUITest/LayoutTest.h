// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgTestLib/ITest.h>

#include <tgUI/RowLayout.h>

namespace tg
{
    namespace ui_test
    {
        class LayoutTest : public test::ITest
        {
        protected:
            LayoutTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~LayoutTest();

            static std::shared_ptr<LayoutTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<ui::IWidget>&);

            std::shared_ptr<App> _app;
            std::shared_ptr<Window> _window;
        };
    }
}

