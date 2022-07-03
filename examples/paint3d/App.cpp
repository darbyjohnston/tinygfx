// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "App.h"

#include "Obj.h"
#include "Window.h"

namespace tg
{
    void App::_init(int& argc, char** argv)
    {
        app::App::_init(argc, argv);

        _mesh = observer::Value<std::shared_ptr<geom::Mesh3D> >::create();
        if (argc > 1)
        {
            open(argv[1]);
        }
        else
        {
            const math::BBox3f bbox(
                math::Vector3f(-1.F, -1.F, -1.F),
                math::Vector3f( 1.F,  1.F,  1.F));
            _mesh->setIfChanged(std::shared_ptr<geom::Mesh3D>(new geom::Mesh3D(geom::bbox(bbox))));
        }

        _window = tg::Window::create(std::dynamic_pointer_cast<App>(shared_from_this()));
        _window->show();
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

    void App::open(const std::string& fileName)
    {
        _mesh->setIfChanged(readObj(fileName));
    }

    std::shared_ptr<observer::IValue<std::shared_ptr<geom::Mesh3D> > > App::observeMesh() const
    {
        return _mesh;
    }
}
