// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/FileBrowserTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/FileBrowser.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        FileBrowserTest::FileBrowserTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::FileBrowserTest")
        {}

        FileBrowserTest::~FileBrowserTest()
        {}

        std::shared_ptr<FileBrowserTest> FileBrowserTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileBrowserTest>(new FileBrowserTest(context));
        }
                
        void FileBrowserTest::run()
        {
            _enums();
            _widget();
        }

        void FileBrowserTest::_enums()
        {
            TINYGFX_TEST_ENUM(FileBrowserSort);
        }

        void FileBrowserTest::_widget()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("DoubleSliderTest");
                auto app = App::create(context, argv, "DoubleSliderTest", "Double slider test.");
                auto window = Window::create(context, "DoubleSliderTest", Size2I(1280, 960));
                app->addWindow(window);
                window->show();
                app->run();

                auto fileBrowserWidget = FileBrowserWidget::create(
                    context,
                    std::filesystem::current_path(),
                    window);
                app->run();
            }
        }
    }
}

