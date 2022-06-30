// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "App.h"

#include "GOL.h"
#include "Window.h"

#include <tgApp/IWindow.h>

namespace tg
{
    void App::_init(int& argc, char** argv)
    {
        app::App::_init(argc, argv);

        _gol = GOL::create();

        _window = tg::Window::create(shared_from_this());
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

    const std::shared_ptr<GOL>& App::getGOL() const
    {
        return _gol;
    }

    void App::_tick()
    {
        _gol->tick();

        _window->repaint();
    }
}
