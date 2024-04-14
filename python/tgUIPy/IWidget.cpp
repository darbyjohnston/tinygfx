// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IWidget.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace tg::core;
using namespace tg::ui;
namespace py = pybind11;

void bindIWidget(py::module_& m)
{
    py::class_<IWidget, std::shared_ptr<IWidget> >(m, "IWidget");
}
