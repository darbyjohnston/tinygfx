// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/IButton.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void iButton(py::module_& m)
        {
            py::class_<IButton, IWidget, std::shared_ptr<IButton> >(m, "IButton");
        }
    }
}
