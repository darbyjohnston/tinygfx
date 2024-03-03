// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "App.h"

#include "Window.h"

#include <tgUI/FileBrowser.h>
#include <tgUI/MessageDialog.h>

#include <tgBaseApp/CmdLine.h>

#include <tgCore/FileIO.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace examples
    {
        namespace textedit
        {
            void App::_init(
                const std::shared_ptr<Context>& context,
                std::vector<std::string>& argv)
            {
                ui::App::_init(
                    context,
                    argv,
                    "textedit",
                    "Text edit example",
                    {
                        app::CmdLineValueArg<std::string>::create(
                            _fileName,
                            "input",
                            "Input file name.",
                            true)
                    });

                _font = ObservableValue<FontRole>::create(FontRole::Mono);
                _text = ObservableValue<std::string>::create();

                context->getSystem<FileBrowserSystem>()->setNativeFileDialog(false);

                _window = Window::create(
                    context,
                    std::dynamic_pointer_cast<App>(shared_from_this()),
                    "textedit",
                    Size2I(1280, 720));
                addWindow(_window);

                if (!_fileName.empty())
                {
                    open(_fileName);
                }

                _window->show();
            }

            std::shared_ptr<App> App::create(
                const std::shared_ptr<Context>& context,
                std::vector<std::string>& argv)
            {
                auto out = std::shared_ptr<App>(new App);
                out->_init(context, argv);
                return out;
            }

            std::shared_ptr<core::IObservableValue<FontRole> > App::observeFont() const
            {
                return _font;
            }

            void App::setFont(FontRole value)
            {
                _font->setIfChanged(value);
            }

            std::shared_ptr<core::IObservableValue<std::string> > App::observeText() const
            {
                return _text;
            }

            void App::open(const std::string& fileName)
            {
                try
                {
                    auto fileIO = FileIO::create(fileName, FileMode::Read);
                    const std::string text = read(fileIO);
                    _text->setIfChanged(text);
                }
                catch (const std::exception& e)
                {
                    _context->getSystem<MessageDialogSystem>()->message("ERROR", e.what(), _window);
                }
            }
        }
    }
}
