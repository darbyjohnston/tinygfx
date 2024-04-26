// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/FileEditTest.h>

#include <tgUI/FileBrowser.h>
#include <tgUI/FileEdit.h>

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
                _app = App::create(
                    context,
                    argv,
                    "FileEditTest",
                    "File edit test.");
                _window = Window::create(context, _app, "FileEditTest");
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->tick();

                auto edit = FileEdit::create(context, _layout);
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

                _window->setCursorEnter(true);
                _window->setKey(Key::Tab);
                _window->setKey(Key::Tab);
                _window->setKey(Key::Enter);
                _window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                _window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                _window->setKey(Key::Enter);

                _window->setKey(Key::Tab);
                _window->setKey(Key::Enter);
                _window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                _window->setKey(Key::Enter);

                _window->setKey(Key::Tab);
                _window->setKey(Key::Tab);
                _window->setKey(Key::Enter);
            }
        }
    }
}

