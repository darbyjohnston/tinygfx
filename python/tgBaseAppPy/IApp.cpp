// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgBaseApp/Cmdline.h>
#include <tgBaseApp/IApp.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace tg::core;
using namespace tg::app;
namespace py = pybind11;

void pyIApp(py::module_& m)
{
    py::class_<IApp, std::shared_ptr<IApp> >(m, "IApp")
        .def("getExit", &IApp::getExit)
        .def("run", &IApp::run);
}
