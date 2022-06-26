// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "App.h"
#include "Window.h"

#include <iostream>

int main(int argc, char* argv[])
{
    int r = 0;
    try
    {
        auto app = tg::App::create(argc, argv);
        auto window = tg::Window::create(app);
        window->show();
        r = app->run();
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    return r;
}
