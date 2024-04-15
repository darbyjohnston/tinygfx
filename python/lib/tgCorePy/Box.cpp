// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Bindings.h>

#include <tgCore/Box.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace tg
{
    namespace core
    {
        void box(py::module_& m)
        {
            py::class_<Box2I>(m, "Box2I")
                .def(py::init<>())
                .def(py::init<V2I, V2I>())
                .def(py::init<int, int, int, int>())
                .def_readwrite("min", &Box2I::min)
                .def_readwrite("max", &Box2I::max);
        }
    }
}
