// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "textedit.h"

#include <tgUI/FileBrowser.h>
#include <tgUI/Menu.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ScrollWidget.h>

#include <tgBaseApp/CmdLine.h>

#include <tgCore/Format.h>
#include <tgCore/FileIO.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace examples
    {
        namespace textedit
        {
            void Window::_init(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<App>& app,
                const std::string& name,
                const Size2I& size)
            {
                ui::Window::_init(context, name, size);

                auto layout = VerticalLayout::create(context, shared_from_this());
                layout->setSpacingRole(SizeRole::None);
                    
                auto fileMenu = Menu::create(context);
                auto appWeak = std::weak_ptr<App>(app);
                fileMenu->addItem(std::make_shared<Action>(
                    "Open",
                    "FileOpen",
                    Key::O,
                    static_cast<int>(KeyModifier::Control),
                    [this, appWeak]
                    {
                        if (auto context = _getContext().lock())
                        {
                            if (auto fileBrowserSystem = context->getSystem<FileBrowserSystem>())
                            {
                                fileBrowserSystem->open(
                                    getWindow(),
                                    [appWeak](const std::string& value)
                                    {
                                        if (auto app = appWeak.lock())
                                        {
                                            app->open(value);
                                        }
                                    });
                            }
                        }
                    }));
                fileMenu->addItem(std::make_shared<Action>(
                    "Close",
                    "FileClose",
                    Key::E,
                    static_cast<int>(KeyModifier::Control),
                    [this]
                    {
                        _textWidget->setText(std::string());
                    }));
                fileMenu->addDivider();
                fileMenu->addItem(std::make_shared<Action>(
                    "Exit",
                    Key::Q,
                    static_cast<int>(KeyModifier::Control),
                    [appWeak]
                    {
                        if (auto app = appWeak.lock())
                        {
                            app->exit();
                        }
                    }));

                _menuBar = MenuBar::create(context, layout);
                _menuBar->addMenu("File", fileMenu);

                _textWidget = Label::create(context);
                _textWidget->setMarginRole(SizeRole::Margin);
                auto scrollWidget = ScrollWidget::create(context, ScrollType::Both, layout);
                scrollWidget->setStretch(Stretch::Expanding);
                scrollWidget->setWidget(_textWidget);

                _textObserver = ValueObserver<std::string>::create(
                    app->observeText(),
                    [this](const std::string& value)
                    {
                        _textWidget->setText(value);
                    });
            }

            Window::~Window()
            {}

            std::shared_ptr<Window> Window::create(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<App>& app,
                const std::string& name,
                const Size2I& size)
            {
                auto out = std::shared_ptr<Window>(new Window);
                out->_init(context, app, name, size);
                return out;
            }

            void Window::keyPressEvent(ui::KeyEvent& event)
            {
                event.accept = _menuBar->shortcut(event.key, event.modifiers);
            }

            void Window::keyReleaseEvent(ui::KeyEvent& event)
            {
                event.accept = true;
            }

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

                _text = ObservableValue<std::string>::create();

                if (!_fileName.empty())
                {
                    open(_fileName);
                }

                context->getSystem<tg::ui::FileBrowserSystem>()->setNativeFileDialog(false);

                _window = Window::create(
                    context,
                    std::dynamic_pointer_cast<App>(shared_from_this()),
                    "textedit",
                    Size2I(1280, 720));
                addWindow(_window);

                _window->show();
            }

            App::App()
            {}

            App::~App()
            {}

            std::shared_ptr<App> App::create(
                const std::shared_ptr<Context>& context,
                std::vector<std::string>& argv)
            {
                auto out = std::shared_ptr<App>(new App);
                out->_init(context, argv);
                return out;
            }

            void App::open(const std::string& fileName)
            {
                try
                {
                    auto fileIO = FileIO::create(fileName, FileMode::Read);
                    const std::string text = read(fileIO);
                    _text->setIfChanged(text);
                }
                catch (const std::exception&)
                {}
            }

            std::shared_ptr<core::IObservableValue<std::string> > App::observeText() const
            {
                return _text;
            }
        }
    }
}

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = tg::app::convert(argc, argv);
        auto app = tg::examples::textedit::App::create(context, args);
        r = app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

