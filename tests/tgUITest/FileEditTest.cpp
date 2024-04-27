// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/FileEditTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/FileBrowser.h>
#include <tgUI/FileEdit.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        FileEditTest::FileEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::FileEditTest")
        {}

        FileEditTest::~FileEditTest()
        {}

        std::shared_ptr<FileEditTest> FileEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileEditTest>(new FileEditTest(context));
        }

        void FileEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FileEditTest");
                auto app = App::create(
                    context,
                    argv,
                    "FileEditTest",
                    "File edit test.");
                auto window = Window::create(context, app, "FileEditTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto edit = FileEdit::create(context, layout);
                std::filesystem::path path = std::filesystem::current_path();
                edit->setPath(path);
                edit->setPath(path);
                TG_ASSERT(path == edit->getPath());
                edit->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });

                auto system = context->getSystem<FileBrowserSystem>();
                system->setNativeFileDialog(false);
                TG_ASSERT(!system->isNativeFileDialog());
                system->setPath(path);
                TG_ASSERT(path == system->getPath());
                FileBrowserOptions options;
                options.reverseSort = true;
                system->setOptions(options);
                TG_ASSERT(options == system->getOptions());
                TG_ASSERT(system->getRecentFilesModel());

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);

                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);

                window->setKey(Key::Tab);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
            }
        }
    }
}

