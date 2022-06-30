// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgApp/App.h>

#include <chrono>
#include <vector>

namespace tg
{
    class Sol;
    class SolFactory;
    class Window;

    //! Sol data.
    struct SolData
    {
        std::shared_ptr<Sol> a;
        std::shared_ptr<Sol> b;
        float transition = 0.F;
    };

    //! Applicaton.
    class App : public app::App
    {
    protected:
        void _init(int& argc, char** argv);

        App();

    public:
        ~App() override;

        static std::shared_ptr<App> create(int& argc, char** argv);

        const SolData& getSolData() const;

    protected:
        void _tick() override;

    private:
        std::shared_ptr<SolFactory> _solFactory;
        std::vector<std::shared_ptr<Sol> > _sols;
        SolData _solData;
        std::chrono::steady_clock::time_point _startTimer;
        std::chrono::steady_clock::time_point _prevTimer;
        std::shared_ptr<Window> _window;
    };
}
