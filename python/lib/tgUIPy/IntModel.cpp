// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/IntModel.h>

#include <tgCore/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void intModel(py::module_& m)
        {
            py::class_<IntModel, std::shared_ptr<IntModel> >(m, "IntModel")
                .def(py::init(&IntModel::create),
                    py::arg("context"));
        }
    }
}
