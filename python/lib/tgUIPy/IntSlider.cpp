// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/IntSlider.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void intSlider(py::module_& m)
        {
            py::class_<IntSlider, IWidget, std::shared_ptr<IntSlider> >(m, "IntSlider")
                .def(
                    py::init(&IntSlider::create),
                    py::arg("context"),
                    py::arg("model") = nullptr,
                    py::arg("parent") = nullptr)
                .def_property("value", &IntSlider::getValue, &IntSlider::setValue)
                .def("setCallback", &IntSlider::setCallback)
                .def_property("range", &IntSlider::getRange, &IntSlider::setRange)
                .def_property("step", &IntSlider::getStep, &IntSlider::setStep)
                .def_property("largeStep", &IntSlider::getLargeStep, &IntSlider::setLargeStep)
                .def_property("defaultValue", &IntSlider::getDefaultValue, &IntSlider::setDefaultValue)
                .def("getModel", &IntSlider::getModel);
        }
    }
}
