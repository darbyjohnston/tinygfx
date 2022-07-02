// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgApp/App.h>

#include <tgCore/ValueObserver.h>

#include <string>

namespace tg
{
    class Mesh;
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

        void open(const std::string&);

        std::shared_ptr<observer::IValue<std::shared_ptr<Mesh> > > observeMesh() const;

    private:
        std::shared_ptr<observer::Value<std::shared_ptr<Mesh> > > _mesh;
        std::shared_ptr<Window> _window;
    };
}
