// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIAppPy/Bindings.h>

#include <tgUIApp/Window.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui_app
    {
        void window(py::module_& m)
        {
            py::class_<ui::Window, ui::IWindow, std::shared_ptr<ui::Window> >(m, "Window")
                .def(
                    py::init(&ui::Window::create),
                    py::arg("context"),
                    py::arg("name"),
                    py::arg("size"))
                .def("show", &ui::Window::show);
        }
    }
}
