// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Bindings.h>

#include <tgCore/Vector.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace tg
{
    namespace core
    {
        void vector(py::module_& m)
        {
            py::class_<V2I>(m, "V2I")
                .def(py::init<>())
                .def(py::init<int, int>())
                .def_readwrite("e", &V2I::e);
        }
    }
}
