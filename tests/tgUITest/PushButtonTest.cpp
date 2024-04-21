// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/PushButtonTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/PushButton.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        PushButtonTest::PushButtonTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::PushButtonTest")
        {}

        PushButtonTest::~PushButtonTest()
        {}

        std::shared_ptr<PushButtonTest> PushButtonTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<PushButtonTest>(new PushButtonTest(context));
        }
                
        void PushButtonTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("PushButtonTest");
                auto app = App::create(context, argv, "PushButtonTest", "Push button test.");
                auto window = Window::create(context, "PushButtonTest", Size2I(1280, 960));
                auto pushButton = PushButton::create(context, window);
                pushButton->setText("Push Button");
                app->addWindow(window);
                window->show();
                app->run();
            }
        }
    }
}

