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
        class LineEditTest : public test::ITest
        {
        protected:
            LineEditTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~LineEditTest();

            static std::shared_ptr<LineEditTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            std::shared_ptr<App> _app;
            std::shared_ptr<Window> _window;
            std::shared_ptr<ui::VerticalLayout> _layout;
        };
    }
}

