// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/FloatEdit.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void floatEdit(py::module_& m)
        {
            py::class_<FloatEdit, IWidget, std::shared_ptr<FloatEdit> >(m, "FloatEdit")
                .def(
                    py::init(&FloatEdit::create),
                    py::arg("context"),
                    py::arg("model") = nullptr,
                    py::arg("parent") = nullptr)
                .def_property("value", &FloatEdit::getValue, &FloatEdit::setValue)
                .def("setCallback", &FloatEdit::setCallback)
                .def_property("range", &FloatEdit::getRange, &FloatEdit::setRange)
                .def_property("step", &FloatEdit::getStep, &FloatEdit::setStep)
                .def_property("largeStep", &FloatEdit::getLargeStep, &FloatEdit::setLargeStep)
                .def("getModel", &FloatEdit::getModel)
                .def("setFontRole", &FloatEdit::setFontRole);
        }
    }
}
