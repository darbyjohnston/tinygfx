// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgApp/App.h>

#include <memory>

namespace tg
{
    class GOL;
    class Window;

    //! Applicaton.
    class App : public app::App
    {
    protected:
        void _init(int& argc, char** argv);

        App();

    public:
        ~App() override;

        static std::shared_ptr<App> create(int& argc, char** argv);

        const std::shared_ptr<GOL>& getGOL() const;

    protected:
        void _tick() override;

    private:
        std::shared_ptr<GOL> _gol;
        std::shared_ptr<Window> _window;
    };
}
