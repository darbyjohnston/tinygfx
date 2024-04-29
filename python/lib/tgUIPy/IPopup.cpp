// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/IPopup.h>

#include <tgUI/IPopup.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void iPopup(py::module_& m)
        {
            py::class_<IPopup, IWidget, std::shared_ptr<IPopup> >(m, "IPopup")
                .def("close", &IPopup::close);
        }
    }
}
