// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/Context.h>
#include <tgCore/Init.h>

#include <pybind11/pybind11.h>

using namespace tg::core;
namespace py = pybind11;

void pySize(py::module_&);
void pyContext(py::module_&);
void pyOS(py::module_&);

void tgCorePy(py::module_& m)
{
    auto sm = m.def_submodule("tgCore");
    sm.doc() = "Core functionality";
    sm.def("init", &init, "Initialize the library.");
    pySize(sm);
    pyContext(sm);
    pyOS(sm);
}
