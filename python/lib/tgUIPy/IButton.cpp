// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/IButton.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void iButton(py::module_& m)
        {
            py::class_<IButton, IWidget, std::shared_ptr<IButton> >(m, "IButton")
                .def_property("checkable", &IButton::isCheckable, &IButton::setCheckable)
                .def_property("checked", &IButton::isChecked, &IButton::setChecked)
                .def("setText", &IButton::setText)
                .def("setFontRole", &IButton::setFontRole)
                .def("setIcon", &IButton::setIcon)
                .def("setCheckedIcon", &IButton::setCheckedIcon)
                .def("setButtonRole", &IButton::setButtonRole)
                .def("setCheckedRole", &IButton::setCheckedRole)
                .def("setHoveredCallback", &IButton::setHoveredCallback)
                .def("setPressedCallback", &IButton::setPressedCallback)
                .def("setRepeatClick", &IButton::setRepeatClick)
                .def("setClickedCallback", &IButton::setClickedCallback)
                .def("setCheckedCallback", &IButton::setCheckedCallback);
        }
    }
}
