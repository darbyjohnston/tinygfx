// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Style.h>

#include <pybind11/pybind11.h>

using namespace tg::core;
using namespace tg::ui;
namespace py = pybind11;

void bindStyle(py::module_& m)
{
    py::enum_<SizeRole>(m, "SizeRole")
        .value("None", SizeRole::None)
        .value("Margin", SizeRole::Margin)
        .value("MarginSmall", SizeRole::MarginSmall)
        .value("MarginLarge", SizeRole::MarginLarge)
        .value("MarginInside", SizeRole::MarginInside)
        .value("MarginDialog", SizeRole::MarginDialog)
        .value("Spacing", SizeRole::Spacing)
        .value("SpacingSmall", SizeRole::SpacingSmall)
        .value("SpacingLarge", SizeRole::SpacingLarge)
        .value("SpacingTool", SizeRole::SpacingTool)
        .value("Border", SizeRole::Border)
        .value("ScrollArea", SizeRole::ScrollArea)
        .value("Slider", SizeRole::Slider)
        .value("Handle", SizeRole::Handle)
        .value("HandleSmall", SizeRole::HandleSmall)
        .value("Swatch", SizeRole::Swatch)
        .value("SwatchLarge", SizeRole::SwatchLarge)
        .value("Shadow", SizeRole::Shadow)
        .value("DragLength", SizeRole::DragLength)
        .export_values();
}
