// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Bindings.h>

#include <tgCore/Range.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace tg
{
    namespace core
    {
        void range(py::module_& m)
        {
            py::class_<RangeI>(m, "RangeI")
                .def(py::init<>())
                .def(py::init<int, int>())
                .def("min", &RangeI::min)
                .def("max", &RangeI::max);

            py::class_<RangeF>(m, "RangeF")
                .def(py::init<>())
                .def(py::init<float, float>())
                .def("min", &RangeF::min)
                .def("max", &RangeF::max);

            py::class_<RangeD>(m, "RangeD")
                .def(py::init<>())
                .def(py::init<double, double>())
                .def("min", &RangeD::min)
                .def("max", &RangeD::max);
        }
    }
}
