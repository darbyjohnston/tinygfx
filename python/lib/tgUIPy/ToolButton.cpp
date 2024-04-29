// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/ToolButton.h>

#include <tgUI/ToolButton.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void toolButton(py::module_& m)
        {
            py::class_<ToolButton, IButton, std::shared_ptr<ToolButton> >(m, "ToolButton")
                .def(
                    py::init(py::overload_cast<
                        const std::shared_ptr<core::Context>&,
                        const std::shared_ptr<IWidget>&>(&ToolButton::create)),
                    py::arg("context"),
                    py::arg("parent") = nullptr);
        }
    }
}
