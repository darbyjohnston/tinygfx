// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Init.h>

#include <tgCore/Context.h>

#include <pybind11/pybind11.h>

using namespace tg::ui;
namespace py = pybind11;

void bindIButton(py::module_&);
void bindIWidget(py::module_&);
void bindIWindow(py::module_&);
void bindPushButton(py::module_&);
void bindRowLayout(py::module_&);
void bindStyle(py::module_&);
void bindWidgetOptions(py::module_&);

PYBIND11_MODULE(tgUIPy, m)
{
    m.doc() = "User interface";
    m.def("init", &init, "Initialize the library.");
    bindStyle(m);
    bindWidgetOptions(m);
    bindIWidget(m);
    bindIButton(m);
    bindIWindow(m);
    bindPushButton(m);
    bindRowLayout(m);
}
