// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "App.h"

#include "Sol000.h"
#include "Sol001.h"

#include <tgApp/IWindow.h>

#include <tgCore/Math.h>

namespace tg
{
    namespace
    {
        const float duration = 3.F;
        const float transition = 3.F;
    }

    void App::_init(int& argc, char** argv)
    {
        app::App::_init(argc, argv);

        _solList.push_back(Sol000::create());
        _solList.push_back(Sol000::create());

        _nextSol = 1;

        _startTimer = std::chrono::steady_clock::now();
        _prevTimer = _startTimer;
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

    const SolData& App::getSolData() const
    {
        return _solData;
    }

    void App::_tick()
    {
        const auto now = std::chrono::steady_clock::now();
        const std::chrono::duration<float> delta = now - _prevTimer;
        const float deltaCount = delta.count();
        _prevTimer = now;
        const std::chrono::duration<float> time = now - _startTimer;
        const float timeCount = time.count();

        if (_currentSol < _solList.size())
        {
            _solList[_currentSol]->tick(deltaCount);
        }
        if (timeCount > duration)
        {
            _solList[_nextSol]->tick(deltaCount);
        }

        _solData.a = _currentSol < _solList.size() ? _solList[_currentSol] : nullptr;
        _solData.b = _nextSol < _solList.size() ? _solList[_nextSol] : nullptr;
        _solData.transition = 0.F;
        if (timeCount > duration)
        {
            _solData.transition = math::lerp((timeCount - duration) / transition, 0.F, 1.F);
        }
        if (timeCount > duration + transition)
        {
            _startTimer = now;
            _currentSol = _nextSol;
            ++_nextSol;
            if (_nextSol >= _solList.size())
            {
                _nextSol = 0;
            }
        }

        for (const auto& window : getWindows())
        {
            window->repaint();
        }
    }
}
