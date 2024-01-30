// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "mdi.h"

#include <tgUIApp/App.h>

#include <tgUI/ColorWidget.h>
#include <tgUI/MDICanvas.h>
#include <tgUI/MDIWidget.h>

#include <tgCore/Format.h>
#include <tgCore/Random.h>

using namespace tg::core;
using namespace tg::ui;

void MainWindow::_init(
    const std::shared_ptr<Context>& context,
    const std::string& name,
    const Size2I& size)
{
    Window::_init(context, name, size);
    
    // Create the scroll widget.
    _scrollWidget = ScrollWidget::create(
        context,
        ScrollType::Both,
        shared_from_this());
    
    // Create the MDI canvas.
    auto canvas = MDICanvas::create(context);
    _scrollWidget->setWidget(canvas);

    // Create the MDI widgets.
    Random random;
    for (size_t i = 0; i < 10; ++i)
    {
        auto colorWidget = ColorWidget::create(context);
        colorWidget->setColor(Color4F(random.get(), random.get(), random.get()));
        canvas->addWidget(
            Format("Color {0}").arg(i),
            V2I(random.get(0, size.w), random.get(0, size.h)),
            colorWidget);
    }
}

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

void MainWindow::setGeometry(const Box2I& value)
{
    Window::setGeometry(value);
    _scrollWidget->setGeometry(value);
}

void MainWindow::sizeHintEvent(const SizeHintEvent& event)
{
    Window::sizeHintEvent(event);
    _sizeHint = _scrollWidget->getSizeHint();
}

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = app::convert(argc, argv);
        auto app = App::create(context, args, "mdi", "MDI example");
        if (0 == app->getExit())
        {
            auto window = MainWindow::create(context, "mdi", Size2I(1280, 720));
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

