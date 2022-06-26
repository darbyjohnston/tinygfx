// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "App.h"

#include "Sol.h"

#include <tgApp/IWindow.h>

#include <tgCore/Math.h>

namespace tg
{
    namespace
    {
        const float duration = 10.F;
        const float transition = 3.F;
    }

    void App::_init(int& argc, char** argv)
    {
        app::App::_init(argc, argv);

        _sols.push_back(Sol::create(duration));

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

        for (auto& i : _sols)
        {
            i->tick(deltaCount);
        }

        if (timeCount > duration && 1 == _sols.size())
        {
            _sols.push_back(Sol::create(duration));
        }
        if (timeCount > duration + transition)
        {
            _startTimer = now;
            _sols.erase(_sols.begin());
        }

        _solData.a = _sols.size() > 0 ? _sols[0] : nullptr;
        _solData.b = _sols.size() > 1 ? _sols[1] : nullptr;
        _solData.transition = transition > 0.F ?
            math::clamp(math::lerp((timeCount - duration) / transition, 0.F, 1.F), 0.F, 1.F) :
            0.F;

        for (const auto& window : getWindows())
        {
            window->repaint();
        }
    }
}
