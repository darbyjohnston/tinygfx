// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace tg::core;
namespace py = pybind11;

void pyContext(py::module_& m)
{
    py::class_<Context, std::shared_ptr<Context> >(m, "Context")
        .def("create", &Context::create)
        .def("tick", &Context::tick);
}
