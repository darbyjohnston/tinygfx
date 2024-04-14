// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/Size.h>

#include <pybind11/pybind11.h>

using namespace tg::core;
namespace py = pybind11;

void bindSize(py::module_& m)
{
    py::class_<Size2I>(m, "Size2I")
        .def(py::init<>())
        .def(py::init<int, int>())
        .def_readwrite("e", &Size2I::e);
}
