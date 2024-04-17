// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/FloatEditSlider.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void floatEditSlider(py::module_& m)
        {
            py::class_<FloatEditSlider, IWidget, std::shared_ptr<FloatEditSlider> >(m, "FloatEditSlider")
                .def(
                    py::init(&FloatEditSlider::create),
                    py::arg("context"),
                    py::arg("model") = nullptr,
                    py::arg("parent") = nullptr)
                .def_property("value", &FloatEditSlider::getValue, &FloatEditSlider::setValue)
                .def("setCallback", &FloatEditSlider::setCallback)
                .def_property("range", &FloatEditSlider::getRange, &FloatEditSlider::setRange)
                .def_property("step", &FloatEditSlider::getStep, &FloatEditSlider::setStep)
                .def_property("largeStep", &FloatEditSlider::getLargeStep, &FloatEditSlider::setLargeStep)
                .def_property("defaultValue", &FloatEditSlider::getDefaultValue, &FloatEditSlider::setDefaultValue)
                .def("getModel", &FloatEditSlider::getModel)
                .def("setFontRole", &FloatEditSlider::setFontRole);
        }
    }
}
