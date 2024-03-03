// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUIApp/App.h>

#include <tgUI/Style.h>

#include <tgCore/ObservableValue.h>

namespace tg
{
    namespace examples
    {
        namespace textedit
        {
            class Window;

            class App : public ui::App
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    std::vector<std::string>& argv);

                App() = default;

            public:
                virtual ~App() = default;

                static std::shared_ptr<App> create(
                    const std::shared_ptr<core::Context>&,
                    std::vector<std::string>& argv);

                std::shared_ptr<core::IObservableValue<ui::FontRole> > observeFont() const;

                void setFont(ui::FontRole);

                std::shared_ptr<core::IObservableValue<std::string> > observeText() const;

                void open(const std::string&);

            private:
                std::string _fileName;
                std::shared_ptr<core::ObservableValue<ui::FontRole> > _font;
                std::shared_ptr<core::ObservableValue<std::string> > _text;
                std::shared_ptr<Window> _window;
            };
        }
    }
}
