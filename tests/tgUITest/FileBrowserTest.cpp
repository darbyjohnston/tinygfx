// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/FileBrowserTest.h>

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
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("DoubleSliderTest");
                _app = App::create(
                    context,
                    argv,
                    "DoubleSliderTest",
                    "Double slider test.");
                _window = Window::create(context, _app, "DoubleSliderTest");
                _app->addWindow(_window);
                _window->show();
                _app->tick();
                _widget(context);
                _dialog(context);
            }
        }

        void FileBrowserTest::_enums()
        {
            TINYGFX_TEST_ENUM(FileBrowserSort);
        }

        void FileBrowserTest::_widget(const std::shared_ptr<Context>& context)
        {
            std::filesystem::path path = std::filesystem::current_path();
            auto fileBrowserWidget = FileBrowserWidget::create(context, path, _window);
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

            fileBrowserWidget->setParent(nullptr);
        }

        void FileBrowserTest::_dialog(const std::shared_ptr<Context>& context)
        {
            std::filesystem::path path = std::filesystem::current_path();
            auto fileBrowser = FileBrowser::create(context, path);
            TG_ASSERT(path == fileBrowser->getPath());
            fileBrowser->setCallback(
                [&path](const std::filesystem::path& value)
                {
                    path = value;
                });
            bool close = false;
            fileBrowser->setCloseCallback(
                [&close]
                {
                    close = true;
                });
            FileBrowserOptions options;
            options.reverseSort = true;
            fileBrowser->setOptions(options);
            TG_ASSERT(fileBrowser->getOptions() == options);
            auto recentFilesModel = RecentFilesModel::create(context);
            fileBrowser->setRecentFilesModel(recentFilesModel);
            TG_ASSERT(recentFilesModel == fileBrowser->getRecentFilesModel());

            fileBrowser->open(_window);
            _app->tick();
            TG_ASSERT(fileBrowser->isOpen());
            fileBrowser->close();
            _app->tick();
            TG_ASSERT(!fileBrowser->isOpen());

            fileBrowser->open(_window);
            _app->tick();
            TG_ASSERT(fileBrowser->isOpen());
            _window->setKey(Key::Escape);
            _window->setKey(Key::Escape);
            TG_ASSERT(!fileBrowser->isOpen());

            fileBrowser->open(_window);
            _app->tick();
            TG_ASSERT(fileBrowser->isOpen());
            _window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
            _window->setKey(Key::Enter);
            TG_ASSERT(!fileBrowser->isOpen());

            fileBrowser->open(_window);
            _app->tick();
            _window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
            _window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
            _window->setKey(Key::Enter);
        }
    }
}

