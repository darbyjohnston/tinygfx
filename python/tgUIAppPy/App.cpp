// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIApp/App.h>
#include <tgUIApp/Window.h>

#include <tgBaseApp/Cmdline.h>

#include <tgCore/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace tg::core;
using namespace tg::app;
using namespace tg::ui;
using namespace pybind11::literals;
namespace py = pybind11;

void pyApp(py::module_& m)
{
    py::class_<App, IApp, std::shared_ptr<App> >(m, "App")
        .def_static("create",
            &App::create,
            py::arg("context"),
            py::arg("argv"),
            py::arg("name"),
            py::arg("summary"),
            py::arg("cmdLineArgs") = std::vector<std::shared_ptr<ICmdLineArg> >(),
            py::arg("cmdLineOptions") = std::vector<std::shared_ptr<ICmdLineOption> >())
        .def("addWindow", &App::addWindow, py::arg("window"))
        .def("removeWindow", &App::removeWindow, py::arg("window"))
        .def("exit", &App::exit);
}
