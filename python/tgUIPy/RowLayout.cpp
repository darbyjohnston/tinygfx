// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/RowLayout.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void rowLayout(py::module_& m)
        {
            py::class_<RowLayout, IWidget, std::shared_ptr<RowLayout> >(m, "RowLayout")
                .def_static(
                    "create",
                    &RowLayout::create,
                    py::arg("context"),
                    py::arg("orientation"),
                    py::arg("parent") = nullptr)
                .def("setMarginRole", &RowLayout::setMarginRole)
                .def("setSpacingRole", &RowLayout::setSpacingRole);

            py::class_<VerticalLayout, RowLayout, std::shared_ptr<VerticalLayout> >(m, "VerticalLayout")
                .def_static(
                    "create",
                    &VerticalLayout::create,
                    py::arg("context"),
                    py::arg("parent") = nullptr);

            py::class_<HorizontalLayout, RowLayout, std::shared_ptr<HorizontalLayout> >(m, "HorizontalLayout")
                .def_static(
                    "create",
                    &HorizontalLayout::create,
                    py::arg("context"),
                    py::arg("parent") = nullptr);
        }
    }
}
