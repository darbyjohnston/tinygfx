// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgApp/App.h>

#include <chrono>
#include <memory>
#include <vector>

namespace tg
{
    class ISol;

    //! Sol data.
    struct SolData
    {
        std::shared_ptr<ISol> a;
        std::shared_ptr<ISol> b;
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
        std::vector<std::shared_ptr<ISol> > _solList;
        size_t _currentSol = 0;
        size_t _nextSol = 0;
        SolData _solData;
        std::chrono::steady_clock::time_point _startTimer;
        std::chrono::steady_clock::time_point _prevTimer;
    };
}
