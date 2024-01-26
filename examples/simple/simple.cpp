// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "simple.h"

#include <tgUIApp/App.h>

using namespace tg::core;
using namespace tg::ui;

MainWindow::~MainWindow()
{}

std::shared_ptr<MainWindow> MainWindow::create(
    const std::shared_ptr<Context>& context,
    const std::string& name,
    const Size2I& size)
{
    auto out = std::shared_ptr<MainWindow>(new MainWindow);
    out->_init(context, name, size);
    return out;
}

void MainWindow::drawEvent(const Box2I& drawRect, const DrawEvent& event)
{
    Window::drawEvent(drawRect, event);

    const Box2F box(0, 0, _geometry.w(), _geometry.h());

    const std::string text = "Hello world";
    FontInfo fontInfo;
    fontInfo.size = _geometry.h() / 6.F * event.displayScale;
    const Size2I textSize = event.fontSystem->getSize(text, fontInfo);
    const auto textGlyphs = event.fontSystem->getGlyphs(text, fontInfo);
    const FontMetrics fontMetrics = event.fontSystem->getMetrics(fontInfo);
    event.render->drawText(
        textGlyphs,
        center(box) - V2F(textSize.w, textSize.h) / 2.F + V2F(0.F, fontMetrics.ascender),
        Color4F(1.F, 1.F, 1.F));
}

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = app::convert(argc, argv);
        auto app = App::create(context, args, "simple", "Simple example");
        if (0 == app->getExit())
        {
            auto window = MainWindow::create(context, "simple", Size2I(1280, 720));
            app->addWindow(window);
            window->show();
        }
        r = app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

