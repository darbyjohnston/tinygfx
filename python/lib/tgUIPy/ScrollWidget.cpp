// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/ScrollWidget.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void scrollWidget(py::module_& m)
        {
            py::class_<ScrollWidget, IWidget, std::shared_ptr<ScrollWidget> >(m, "ScrollWidget")
                .def(
                    py::init(&ScrollWidget::create),
                    py::arg("context"),
                    py::arg("type"),
                    py::arg("parent") = nullptr)
                .def(
                    "setWidget",
                    &ScrollWidget::setWidget,
                    py::arg("widget"));
        }
    }
}
