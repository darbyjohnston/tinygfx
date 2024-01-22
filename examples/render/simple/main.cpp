// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "App.h"

#include <tgCore/Context.h>

#include <iostream>

using namespace tg;
using namespace tg::core;
using namespace tg::examples::simple;

int main(int argc, char** argv)
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = base_app::convert(argc, argv);
        auto app = App::create(context, "simple", args);
        r = app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}
