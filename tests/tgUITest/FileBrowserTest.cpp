// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/FileBrowserTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/FileBrowser.h>
#include <tgUI/RecentFilesModel.h>

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

                std::filesystem::path path = std::filesystem::current_path();
                auto fileBrowserWidget = FileBrowserWidget::create(context, path, window);
                TG_ASSERT(path == fileBrowserWidget->getPath());
                fileBrowserWidget->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });
                bool cancel = false;
                fileBrowserWidget->setCancelCallback(
                    [&cancel]
                    {
                        cancel = true;
                    });
                FileBrowserOptions options;
                fileBrowserWidget->setOptionsCallback(
                    [&options](const FileBrowserOptions& value)
                    {
                        options = value;
                    });

                FileBrowserOptions options2;
                options2.reverseSort = true;
                fileBrowserWidget->setOptions(options2);
                fileBrowserWidget->setOptions(options2);
                TG_ASSERT(options2 == fileBrowserWidget->getOptions());

                auto recentFilesModel = RecentFilesModel::create(context);
                fileBrowserWidget->setRecentFilesModel(recentFilesModel);

                app->addWindow(window);
                window->show();
                app->run();
            }
        }
    }
}

