// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "App.h"

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = tg::core::Context::create();
        auto args = tg::app::convert(argc, argv);
        auto app = tg::examples::textedit::App::create(context, args);
        r = app->getExit();
        if (0 == r)
        {
            app->run();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}
