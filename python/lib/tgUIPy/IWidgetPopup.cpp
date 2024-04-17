// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/IWidgetPopup.h>
#include <tgUI/IWindow.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void iWidgetPopup(py::module_& m)
        {
            py::class_<IWidgetPopup, IPopup, std::shared_ptr<IWidgetPopup> >(m, "IWidgetPopup")
                .def("open", &IWidgetPopup::open)
                .def("isOpen", &IWidgetPopup::isOpen)
                .def("setCloseCallback", &IWidgetPopup::setCloseCallback)
                .def("setWidget", &IWidgetPopup::setWidget)
                .def_property("popupRole", &IWidgetPopup::getPopupRole, &IWidgetPopup::setPopupRole);
        }
    }
}
