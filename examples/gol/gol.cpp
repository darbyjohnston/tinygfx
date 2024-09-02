// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "gol.h"

#include <dtk/ui/App.h>

#include <dtk/core/Noise.h>

namespace tg
{
    namespace examples
    {
        namespace gol
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
                    std::chrono::milliseconds(1000 / 60),
                    [this]
                    {
                        _tick();
                    });

                _timer2 = dtk::Timer::create(context);
                _timer2->setRepeating(true);
                /*_timer2->start(
                    std::chrono::milliseconds(10 * 1000),
                    [this]
                    {
                        _randomize(_currentCells);
                    });*/
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
                const bool changed = value != getGeometry();
                dtk::Window::setGeometry(value);
                if (changed)
                {
                    const dtk::Box2I& g = getGeometry();
                    _cellsSize.w = g.w() / _cellSize;
                    _cellsSize.h = g.h() / _cellSize;
                    const size_t size = _cellsSize.w * _cellsSize.h;
                    _cells[0].resize(size);
                    _cells[1].resize(size);
                    _randomize(_currentCells);
                }
            }

            void Window::sizeHintEvent(const dtk::SizeHintEvent& event)
            {
                dtk::Window::sizeHintEvent(event);
                _cellSize = 3 * event.displayScale;
            }

            void Window::drawEvent(const dtk::Box2I& drawRect, const dtk::DrawEvent& event)
            {
                dtk::Window::drawEvent(drawRect, event);
                const dtk::Box2I& g = getGeometry();
                const dtk::Box2F box(0, 0, g.w(), g.h());
                event.render->drawRect(box, dtk::Color4F(0.F, 0.F, 0.F));
                std::vector<dtk::Box2F> rects;
                dtk::V2I pos;
                for (; pos.y < _cellsSize.h; ++pos.y)
                {
                    for (pos.x = 0; pos.x < _cellsSize.w; ++pos.x)
                    {
                        const uint8_t v = _getCell(_currentCells, pos);
                        if (v)
                        {
                            rects.push_back(dtk::Box2F(
                                pos.x * _cellSize,
                                pos.y * _cellSize,
                                _cellSize - 1,
                                _cellSize - 1));
                        }
                    }
                }
                event.render->drawRects(rects, dtk::Color4F(1.F, 1.F, 1.F));
            }

            dtk::V2I Window::_wrap(const dtk::V2I& pos) const
            {
                dtk::V2I out = pos;
                if (out.x < 0)
                {
                    out.x = _cellsSize.w - 1;
                }
                else if (out.x >= _cellsSize.w)
                {
                    out.x = 0;
                }
                if (out.y < 0)
                {
                    out.y = _cellsSize.h - 1;
                }
                else if (out.y >= _cellsSize.h)
                {
                    out.y = 0;
                }
                return out;
            }

            uint8_t Window::_getCell(size_t index, const dtk::V2I& pos) const
            {
                const dtk::V2I pos2 = _wrap(pos);
                return _cells[index][pos2.y * _cellsSize.w + pos2.x];
            }

            void Window::_setCell(size_t index, const dtk::V2I& pos, uint8_t value)
            {
                const dtk::V2I pos2 = _wrap(pos);
                _cells[index][pos2.y * _cellsSize.w + pos2.x] = value;
            }

            void Window::_randomize(size_t index)
            {
                dtk::Noise noise;
                dtk::V2I pos;
                for (; pos.y < _cellsSize.h; pos.y = ++pos.y)
                {
                    for (pos.x = 0; pos.x < _cellsSize.w; pos.x = ++pos.x)
                    {
                        const double n = noise.get(pos.x / 10.0, pos.y / 10.0, _noiseZ / 10.0);
                        if (n > 0.1)
                        {
                            _setCell(index, pos, 255);
                        }
                    }
                }
                _setDrawUpdate();
            }

            void Window::_tick()
            {
                const size_t source = _currentCells;
                const size_t dest = (_currentCells + 1) % 2;
                const std::vector<dtk::V2I> offsets =
                {
                    { -1, -1 }, { 0, -1 }, { 1, -1 },
                    { -1,  0 },            { 1,  0 },
                    { -1,  1 }, { 0,  1 }, { 1,  1 }
                };
                dtk::V2I pos;
                for (; pos.y < _cellsSize.h; ++pos.y)
                {
                    for (pos.x = 0; pos.x < _cellsSize.w; ++pos.x)
                    {
                        uint8_t cell = _getCell(source, pos);
                        size_t neighborsAlive = 0;
                        for (const auto& offset : offsets)
                        {
                            if (_getCell(source, pos + offset))
                            {
                                ++neighborsAlive;
                            }
                        }
                        if (cell)
                        {
                            if (neighborsAlive < 2)
                            {
                                cell = 0;
                            }
                            else if (neighborsAlive > 3)
                            {
                                cell = 0;
                            }
                        }
                        else
                        {
                            if (3 == neighborsAlive)
                            {
                                cell = 255;
                            }
                        }
                        _setCell(dest, pos, cell);
                    }
                }
                _currentCells = dest;
                _noiseZ += 1.0;
                _setDrawUpdate();
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
        auto app = dtk::App::create(context, args, "gol", "Game of life example");
        if (app->getExit() != 0)
            return app->getExit();

        auto window = tg::examples::gol::Window::create(
            context,
            "gol",
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

