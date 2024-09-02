// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "noise.h"

#include <dtk/ui/App.h>

#include <dtk/core/Noise.h>

namespace tg
{
    namespace examples
    {
        namespace noise
        {
            void Window::_init(
                const std::shared_ptr<dtk::Context>& context,
                const std::string& name,
                const dtk::Size2I& size)
            {
                dtk::Window::_init(context, name, size);

                _timer = dtk::Timer::create(context);
                _timer->setRepeating(true);
                _timer->start(
                    std::chrono::milliseconds(1000 / 24),
                    [this]
                    {
                        _tick();
                    });
            }

            Window::~Window()
            {}

            std::shared_ptr<Window> Window::create(
                const std::shared_ptr<dtk::Context>& context,
                const std::string& name,
                const dtk::Size2I& size)
            {
                auto out = std::shared_ptr<Window>(new Window);
                out->_init(context, name, size);
                return out;
            }

            void Window::setGeometry(const dtk::Box2I& value)
            {
                dtk::Window::setGeometry(value);
                const dtk::Box2I& g = getGeometry();
                _image = dtk::Image::create(g.w() / 2, g.h() / 2, dtk::ImageType::L_U8);
                _render();
            }

            void Window::drawEvent(const dtk::Box2I& drawRect, const dtk::DrawEvent& event)
            {
                dtk::Window::drawEvent(drawRect, event);
                if (_image)
                {
                    const dtk::Box2I& g = getGeometry();
                    dtk::ImageOptions options;
                    options.cache = false;
                    event.render->drawImage(
                        _image,
                        dtk::Box2F(0.F, 0.F, g.w(), g.h()),
                        dtk::Color4F(1.F, 1.F, 1.F),
                        options);
                }
            }

            void Window::_render()
            {
                if (_image)
                {
                    const dtk::Size2I& size = _image->getSize();
                    uint8_t* data = _image->getData();
                    dtk::Noise noise;
                    for (int y = 0; y < size.h; ++y)
                    {
                        for (int x = 0; x < size.w; ++x)
                        {
                            const double n = noise.get(x / 100.0, y / 100.0, _noiseZ / 100.0);
                            data[y * size.w + x] = dtk::clamp(n, 0.0, 1.0) * 255;
                        }
                    }
                }
            }

            void Window::_tick()
            {
                _render();
                _setDrawUpdate();
                _noiseZ += 1.0;
            }
        }
    }
}

DTK_MAIN()
{
    try
    {
        auto context = dtk::Context::create();
        auto args = dtk::convert(argc, argv);
        auto app = dtk::App::create(context, args, "noise", "Noise example");
        if (app->getExit() != 0)
            return app->getExit();

        auto window = tg::examples::noise::Window::create(
            context,
            "noise",
            dtk::Size2I(1280, 960));
        app->addWindow(window);
        window->show();
        app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

