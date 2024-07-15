// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/IWidget.h>

#include <tgUI/IWidget.h>
#include <tgUI/IWindow.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        class PyIWidget : public IWidget
        {
        public:
            virtual void drawEvent(const core::Box2I& drawRect, const DrawEvent& event) override
            {
                PYBIND11_OVERRIDE(
                    void,
                    IWidget,
                    drawEvent,
                    drawRect,
                    event);
            }
        };

        void iWidget(py::module_& m)
        {
            py::class_<IWidget, std::shared_ptr<IWidget>, PyIWidget>(m, "IWidget")
                .def_property("objectName", &IWidget::getObjectName, &IWidget::setObjectName)
                .def("getObjectPath", &IWidget::getObjectPath)
                .def_property("backgroundColor", &IWidget::getBackgroundRole, &IWidget::setBackgroundRole)
                .def("getUpdates", &IWidget::getUpdates)

                .def_property("parent", &IWidget::getParent, &IWidget::setParent)
                .def("getChildren", &IWidget::getChildren)
                .def("moveToFront", &IWidget::moveToFront)
                .def("moveToBack", &IWidget::moveToBack)
                .def_property_readonly("window", &IWidget::getWindow)

                .def_property_readonly("sizeHint", &IWidget::getSizeHint)
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
                .def_property_readonly("clipped", &IWidget::isClipped)
                .def_property_readonly("childrenClipRect", &IWidget::getChildrenClipRect)

                .def_property("enabled", &IWidget::isEnabled, &IWidget::setEnabled)

                .def("hasMouseHover", &IWidget::hasMouseHover)

                .def_property("acceptsKeyFocus", &IWidget::acceptsKeyFocus, &IWidget::setAcceptsKeyFocus)
                .def_property_readonly("keyFocus", &IWidget::hasKeyFocus)
                .def("takeKeyFocus", &IWidget::takeKeyFocus)
                .def("releaseKeyFocus", &IWidget::releaseKeyFocus)

                .def_property("tooltip", &IWidget::getTooltip, &IWidget::setTooltip)

                .def("childAddEvent", &IWidget::childAddEvent, py::arg("event"))
                .def("childRemoveEvent", &IWidget::childRemoveEvent, py::arg("event"))
                .def(
                    "tickEvent",
                    &IWidget::tickEvent,
                    py::arg("parentsVisible"),
                    py::arg("parentsEnabled"),
                    py::arg("event"))
                .def("sizeHintEvent", &IWidget::sizeHintEvent, py::arg("event"))
                .def(
                    "clipEvent",
                    &IWidget::clipEvent,
                    py::arg("clipRect"),
                    py::arg("clipped"))
                .def(
                    "drawEvent",
                    &IWidget::drawEvent,
                    py::arg("drawRect"),
                    py::arg("event"))
                .def(
                    "drawOverlayEvent",
                    &IWidget::drawOverlayEvent,
                    py::arg("drawRect"),
                    py::arg("event"))
                .def("mouseEnterEvent", &IWidget::mouseEnterEvent)
                .def("mouseLeaveEvent", &IWidget::mouseLeaveEvent)
                .def("mouseMoveEvent", &IWidget::mouseMoveEvent, py::arg("event"))
                .def("mousePressEvent", &IWidget::mousePressEvent, py::arg("event"))
                .def("mouseReleaseEvent", &IWidget::mouseReleaseEvent, py::arg("event"))
                .def("scrollEvent", &IWidget::scrollEvent, py::arg("event"))
                .def("keyFocusEvent", &IWidget::keyFocusEvent, py::arg("focus"))
                .def("keyPressEvent", &IWidget::keyPressEvent, py::arg("event"))
                .def("keyReleaseEvent", &IWidget::keyReleaseEvent, py::arg("event"))
                .def("textEvent", &IWidget::textEvent, py::arg("event"))
                .def("dragEnterEvent", &IWidget::dragEnterEvent, py::arg("event"))
                .def("dragLeaveEvent", &IWidget::dragLeaveEvent, py::arg("event"))
                .def("dragMoveEvent", &IWidget::dragMoveEvent, py::arg("event"))
                .def("dropEvent", &IWidget::dropEvent, py::arg("event"));
        }
    }
}
