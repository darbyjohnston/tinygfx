// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "App.h"

#include "Obj.h"
#include "Window.h"

namespace tg
{
    void App::_init(int& argc, char** argv)
    {
        app::App::_init(argc, argv);

        if (argc != 2)
        {
            std::cout << "usage: paint3d (file.obj)" << std::endl;
            exit();
            return;
        }

        auto obj = readObj(argv[1]);

        _window = tg::Window::create(shared_from_this(), obj);
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
