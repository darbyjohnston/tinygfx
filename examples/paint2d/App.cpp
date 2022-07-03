// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "App.h"

#include "Window.h"

namespace tg
{
    void App::_init(int& argc, char** argv)
    {
        app::App::_init(argc, argv);

        _window = tg::Window::create(std::dynamic_pointer_cast<App>(shared_from_this()));
        _window->show();
    }

    App::App()
    {}

    App::~App()
    {}

    std::shared_ptr<App> App::create(int& argc, char** argv)
    {
        auto out = std::shared_ptr<App>(new App);
        out->_init(argc, argv);
        return out;
    }
}
