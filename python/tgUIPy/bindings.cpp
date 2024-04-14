// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Init.h>

#include <tgCore/Context.h>

#include <pybind11/pybind11.h>

using namespace tg::ui;
namespace py = pybind11;

void pyIButton(py::module_&);
void pyIWidget(py::module_&);
void pyIWindow(py::module_&);
void pyPushButton(py::module_&);
void pyRowLayout(py::module_&);
void pyStyle(py::module_&);
void pyWidgetOptions(py::module_&);

void tgUIPy(py::module_& m)
{
    auto sm = m.def_submodule("tgUI");
    sm.doc() = "User interface";
    sm.def("init", &init, "Initialize the library.");
    pyStyle(sm);
    pyWidgetOptions(sm);
    pyIWidget(sm);
    pyIButton(sm);
    pyIWindow(sm);
    pyPushButton(sm);
    pyRowLayout(sm);
}
