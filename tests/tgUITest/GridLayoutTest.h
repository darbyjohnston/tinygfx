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
        class GridLayoutTest : public test::ITest
        {
        protected:
            GridLayoutTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~GridLayoutTest();

            static std::shared_ptr<GridLayoutTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            std::shared_ptr<App> _app;
            std::shared_ptr<Window> _window;
        };
    }
}

