// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "noise.h"

#include <tgUIApp/App.h>

#include <tgCore/Noise.h>

using namespace tg::core;
using namespace tg::ui;

void MainWindow::_init(
    const std::shared_ptr<Context>& context,
    const std::string& name,
    const Size2I& size)
{
    Window::_init(context, name, size);

    _timer = Timer::create(context);
    _timer->setRepeating(true);
    _timer->start(
        std::chrono::milliseconds(1000 / 24),
        [this]
        {
            _tick();
        });
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
    _image = Image::create(_geometry.w() / 2, _geometry.h() / 2, ImageType::L_U8);
}

void MainWindow::drawEvent(const Box2I& drawRect, const DrawEvent& event)
{
    Window::drawEvent(drawRect, event);
    ImageOptions options;
    options.cache = false;
    event.render->drawImage(
        _image,
        Box2F(0.F, 0.F, _geometry.w(), _geometry.h()),
        Color4F(1.F, 1.F, 1.F),
        options);
}

void MainWindow::_tick()
{
    const Size2I& size = _image->getSize();
    uint8_t* data = _image->getData();
    Noise noise;
    for (int y = 0; y < size.h; ++y)
    {
        for (int x = 0; x < size.w; ++x)
        {
            const double n = noise.get(x / 100.0, y / 100.0, _noiseZ / 100.0);
            data[y * size.w + x] = clamp(n, 0.0, 1.0) * 255;
        }
    }
    _noiseZ += 1.0;
    _updates |= Update::Draw;
}

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = app::convert(argc, argv);
        auto app = App::create(context, args, "noise", "Noise example");
        if (0 == app->getExit())
        {
            auto window = MainWindow::create(context, "noise", Size2I(1280, 720));
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

