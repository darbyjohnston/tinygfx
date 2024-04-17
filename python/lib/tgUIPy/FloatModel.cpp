// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/FloatModel.h>

#include <tgCore/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void floatModel(py::module_& m)
        {
            py::class_<FloatModel, std::shared_ptr<FloatModel> >(m, "FloatModel")
                .def(py::init(&FloatModel::create),
                    py::arg("context"));
        }
    }
}
