// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/ISystem.h>

#include <tgCore/Context.h>
#include <tgCore/ISystem.h>

#include <pybind11/pybind11.h>
#include <pybind11/chrono.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace core
    {
        void iSystem(py::module_& m)
        {
            py::class_<ISystem, std::shared_ptr<ISystem> >(m, "ISystem")
                .def_property_readonly(
                    "context",
                    [](std::shared_ptr<ISystem>& self)
                    {
                        return self->getContext().lock();
                    })
                .def_property_readonly("name", &ISystem::getName)
                .def("tick", &ISystem::tick)
                .def_property_readonly("tickTime", &ISystem::getTickTime);
        }
    }
}