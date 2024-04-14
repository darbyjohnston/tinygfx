// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <pybind11/pybind11.h>

namespace py = pybind11;

void pyCmdline(py::module_&);
void pyIApp(py::module_&);

void tgBaseAppPy(py::module_& m)
{
    auto sm = m.def_submodule("tgBaseApp");
    sm.doc() = "Applications";
    pyCmdline(sm);
    pyIApp(sm);
}
