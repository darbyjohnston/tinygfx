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
        class DragAndDropTest : public test::ITest
        {
        protected:
            DragAndDropTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~DragAndDropTest();

            static std::shared_ptr<DragAndDropTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:

            std::shared_ptr<App> _app;
            std::shared_ptr<Window> _window;
            std::shared_ptr<ui::HorizontalLayout> _layout;
        };
    }
}

