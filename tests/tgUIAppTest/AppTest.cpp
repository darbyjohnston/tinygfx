// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIAppTest/AppTest.h>

#include <tgUIApp/App.h>
#include <tgUIApp/Window.h>

#include <tgUI/PushButton.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        AppTest::AppTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::AppTest")
        {}

        AppTest::~AppTest()
        {}

        std::shared_ptr<AppTest> AppTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<AppTest>(new AppTest(context));
        }
                
        void AppTest::run()
        {
            int r = 0;
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv = { "app", "-exit" };
                try
                {
                    auto app = ui::App::create(
                        context,
                        argv,
                        "tg::ui_test::App",
                        "Test UI application");
                    r = app->getExit();
                    if (0 == r)
                    {
                        auto window = Window::create(
                            context,
                            "tg::ui_test::App",
                            Size2I(1280, 960));
                        auto layout = VerticalLayout::create(context, window);
                        auto button = PushButton::create(context, "Button", layout);
                        app->addWindow(window);
                        TG_ASSERT(app->getWindows().front() == window );
                        window->show();
                        window->setSize(Size2I(1920, 1080));
                        TG_ASSERT(Size2I(1920, 1080) == window->getSize());

                        _print(Format("Frame buffer size: {0}").
                            arg(window->getFrameBufferSize()));
                        _print(Format("Display scale: {0}").
                            arg(window->getDisplayScale()));

                        app->run();
                        app->exit();
                        window->hide();
                        app->removeWindow(window);
                    }
                }
                catch (const std::exception&)
                {}
            }
            TG_ASSERT(0 == r);
        }
    }
}
