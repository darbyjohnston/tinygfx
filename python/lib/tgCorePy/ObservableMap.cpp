// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/ObservableMap.h>

#include <tgCore/ObservableMap.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace core
    {
        void observableMap(py::module_& m)
        {
            observableMap<std::string, int>(m, "StringI");
        }
    }
}
