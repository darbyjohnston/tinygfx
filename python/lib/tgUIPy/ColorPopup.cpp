// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/ColorPopup.h>

#include <tgUI/ColorPopup.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void colorPopup(py::module_& m)
        {
            py::class_<ColorPopup, IWidgetPopup, std::shared_ptr<ColorPopup> >(m, "ColorPopup")
                .def(
                    py::init(&ColorPopup::create),
                    py::arg("context"),
                    py::arg("color"),
                    py::arg("parent") = nullptr)
                .def("setCallback", &ColorPopup::setCallback);
        }
    }
}
