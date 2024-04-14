// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/Context.h>
#include <tgCore/Init.h>

#include <pybind11/pybind11.h>

using namespace tg::core;
namespace py = pybind11;

void bindContext(py::module_&);
void bindOS(py::module_&);
void bindSize(py::module_&);

PYBIND11_MODULE(tgCorePy, m)
{
    m.doc() = "Core functionality";
    m.def("init", &init, "Initialize the library.");
    bindContext(m);
    bindOS(m);
    bindSize(m);
}
