// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/DoubleModel.h>

#include <tgCore/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void doubleModel(py::module_& m)
        {
            py::class_<DoubleModel, std::shared_ptr<DoubleModel> >(m, "DoubleModel")
                .def(py::init(&DoubleModel::create),
                    py::arg("context"));
        }
    }
}
