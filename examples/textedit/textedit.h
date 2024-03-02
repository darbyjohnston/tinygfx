// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUIApp/App.h>
#include <tgUIApp/Window.h>

#include <tgUI/Label.h>
#include <tgUI/MenuBar.h>

#include <tgCore/ObservableValue.h>

namespace tg
{
    namespace examples
    {
        namespace textedit
        {
            class App;

            class Window : public ui::Window
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    const std::shared_ptr<App>&,
                    const std::string& name,
                    const core::Size2I&);

                Window() = default;

            public:
                virtual ~Window();

                static std::shared_ptr<Window> create(
                    const std::shared_ptr<core::Context>&,
                    const std::shared_ptr<App>&,
                    const std::string& name,
                    const core::Size2I&);

                void keyPressEvent(ui::KeyEvent&) override;
                void keyReleaseEvent(ui::KeyEvent&) override;

            private:
                std::shared_ptr<ui::MenuBar> _menuBar;
                std::shared_ptr<ui::Label> _textWidget;
                std::shared_ptr<core::ValueObserver<std::string> > _textObserver;
            };

            class App : public ui::App
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    std::vector<std::string>& argv);

                App();

            public:
                virtual ~App();

                static std::shared_ptr<App> create(
                    const std::shared_ptr<core::Context>&,
                    std::vector<std::string>& argv);

                void open(const std::string&);

                std::shared_ptr<core::IObservableValue<std::string> > observeText() const;

            private:
                std::string _fileName;
                std::shared_ptr<core::ObservableValue<std::string> > _text;
                std::shared_ptr<Window> _window;
            };
        }
    }
}
