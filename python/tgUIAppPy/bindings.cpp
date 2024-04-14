// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <pybind11/pybind11.h>

namespace py = pybind11;

void bindApp(py::module_&);
void bindWindow(py::module_&);

PYBIND11_MODULE(tgUIAppPy, m)
{
    m.doc() = "User interface applications";
    bindApp(m);
    bindWindow(m);
}
