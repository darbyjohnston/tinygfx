// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/IWidget.h>
#include <tgUI/IWindow.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void iWidget(py::module_& m)
        {
            py::class_<IWidget, std::shared_ptr<IWidget> >(m, "IWidget")
                .def_property("objectName", &IWidget::getObjectName, &IWidget::setObjectName)
                .def("getObjectPath", &IWidget::getObjectPath)
                .def("setBackgroundColor", &IWidget::setBackgroundRole)
                .def("getUpdates", &IWidget::getUpdates)

                .def("getParent", &IWidget::getParent)
                .def("setParent", &IWidget::setParent)
                .def("getChildren", &IWidget::getChildren)
                .def("moveToFront", &IWidget::moveToFront)
                .def("moveToBack", &IWidget::moveToBack)
                .def("getWindow", &IWidget::getWindow)

                .def("getSizeHint", &IWidget::getSizeHint)
                .def_property("hStretch", &IWidget::getHStretch, &IWidget::setHStretch)
                .def_property("vStretch", &IWidget::getVStretch, &IWidget::setHStretch)
                .def(
                    "setStretch",
                    py::overload_cast<Stretch, Stretch>(&IWidget::setStretch),
                    py::arg("horizontal"),
                    py::arg("vertical"))
                .def(
                    "setStretch",
                    py::overload_cast<Stretch>(&IWidget::setStretch))
                .def_property("hAlign", &IWidget::getHAlign, &IWidget::setHAlign)
                .def_property("vAlign", &IWidget::getVAlign, &IWidget::setHAlign)
                .def(
                    "setAlign",
                    &IWidget::setAlign,
                    py::arg("horizontal"),
                    py::arg("vertical"))
                .def_property("geometry", &IWidget::getGeometry, &IWidget::setGeometry)
                .def("setPos", &IWidget::setPos)
                .def("setSize", &IWidget::setSize)
                .def(
                    "isVisible",
                    &IWidget::isVisible,
                    py::arg("andParentsVisible") = true)
                .def("show", &IWidget::show)
                .def("hide", &IWidget::hide)
                .def("isClipped", &IWidget::isClipped)
                .def("getChildrenClipRect", &IWidget::getChildrenClipRect)
                
                .def_property("enabled", &IWidget::isEnabled, &IWidget::setEnabled)
                
                .def("hasMouseHover", &IWidget::hasMouseHover)
                
                .def_property("acceptsKeyFocus", &IWidget::acceptsKeyFocus, &IWidget::setAcceptsKeyFocus)
                .def("hasKeyFocus", &IWidget::hasKeyFocus)
                .def("takeKeyFocus", &IWidget::takeKeyFocus)
                .def("releaseKeyFocus", &IWidget::releaseKeyFocus)

                .def_property("tooltip", &IWidget::getTooltip, &IWidget::setTooltip);
        }
    }
}
