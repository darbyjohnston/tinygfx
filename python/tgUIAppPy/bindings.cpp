// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <pybind11/pybind11.h>

namespace py = pybind11;

void pyApp(py::module_&);
void pyWindow(py::module_&);

void tgUIAppPy(py::module_& m)
{
    auto sm = m.def_submodule("tgUIApp");
    sm.doc() = "User interface applications";
    pyApp(sm);
    pyWindow(sm);
}
