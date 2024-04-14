// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IWidget.h>

#include <pybind11/pybind11.h>

using namespace tg::core;
using namespace tg::ui;
namespace py = pybind11;

void bindWidgetOptions(py::module_& m)
{
    py::enum_<Orientation>(m, "Orientation")
        .value("Horizontal", Orientation::Horizontal)
        .value("Vertical", Orientation::Vertical)
        .export_values();

    py::enum_<Stretch>(m, "Stretch")
        .value("Fixed", Stretch::Fixed)
        .value("Expanding", Stretch::Expanding)
        .export_values();

    py::enum_<HAlign>(m, "HAlign")
        .value("Left", HAlign::Left)
        .value("Center", HAlign::Center)
        .value("Right", HAlign::Right)
        .export_values();

    py::enum_<VAlign>(m, "VAlign")
        .value("Top", VAlign::Top)
        .value("Center", VAlign::Center)
        .value("Bottom", VAlign::Bottom)
        .export_values();
}
