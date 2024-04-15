// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIAppPy/Bindings.h>

#include <tgUIApp/App.h>
#include <tgUIApp/Window.h>

#include <tgBaseApp/CmdLine.h>

#include <tgCore/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace pybind11::literals;
namespace py = pybind11;

namespace tg
{
    namespace ui_app
    {
        void app(py::module_& m)
        {
            py::class_<ui::App, app::IApp, std::shared_ptr<ui::App> >(m, "App")
                .def_static("create",
                    &ui::App::create,
                    py::arg("context"),
                    py::arg("argv"),
                    py::arg("name"),
                    py::arg("summary"),
                    py::arg("cmdLineArgs") = std::vector<std::shared_ptr<app::ICmdLineArg> >(),
                    py::arg("cmdLineOptions") = std::vector<std::shared_ptr<app::ICmdLineOption> >())
                .def("addWindow", &ui::App::addWindow, py::arg("window"))
                .def("removeWindow", &ui::App::removeWindow, py::arg("window"))
                .def("exit", &ui::App::exit);
        }
    }
}
