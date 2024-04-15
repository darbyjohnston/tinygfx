// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Bindings.h>

#include <tgCore/OS.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace tg
{
    namespace core
    {
        void os(py::module_& m)
        {
            py::class_<SystemInfo>(m, "SystemInfo")
                .def_readwrite("name", &SystemInfo::name)
                .def_readwrite("cores", &SystemInfo::cores)
                .def_readwrite("ram", &SystemInfo::ram)
                .def_readwrite("ramGB", &SystemInfo::ramGB);

            m.def("getSystemInfo", &getSystemInfo, "Get operating system information.");
        }
    }
}
