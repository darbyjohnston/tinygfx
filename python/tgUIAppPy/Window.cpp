// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIApp/Window.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace tg::core;
using namespace tg::ui;
namespace py = pybind11;

void bindWindow(py::module_& m)
{
    py::class_<Window, IWindow, std::shared_ptr<Window> >(m, "Window")
        .def_static(
            "create",
            &Window::create,
            py::arg("context"),
            py::arg("name"),
            py::arg("size"))
        .def("show", &Window::show);
}
