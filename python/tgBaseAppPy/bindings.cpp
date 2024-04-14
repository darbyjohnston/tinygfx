// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <pybind11/pybind11.h>

namespace py = pybind11;

void bindCmdline(py::module_&);
void bindIApp(py::module_&);

PYBIND11_MODULE(tgBaseAppPy, m)
{
    m.doc() = "Applications";
    bindCmdline(m);
    bindIApp(m);
}
