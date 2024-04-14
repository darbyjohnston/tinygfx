// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/PushButton.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace tg::core;
using namespace tg::ui;
namespace py = pybind11;

void bindPushButton(py::module_& m)
{
    py::class_<PushButton, IButton, std::shared_ptr<PushButton> >(m, "PushButton")
        .def_static(
            "create",
            py::overload_cast<
                const std::shared_ptr<Context>&,
                const std::string&,
                const std::shared_ptr<IWidget>&>(&PushButton::create),
            py::arg("context"),
            py::arg("text"),
            py::arg("parent") = nullptr);
}
