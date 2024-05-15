// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bellows.h>

#include <tgUI/Bellows.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void bellows(py::module_& m)
        {
            py::class_<Bellows, IWidget, std::shared_ptr<Bellows> >(m, "Bellows")
                .def(
                    py::init(py::overload_cast<
                        const std::shared_ptr<core::Context>&,
                        const std::shared_ptr<IWidget>&>(&Bellows::create)),
                    py::arg("context"),
                    py::arg("parent") = nullptr)
                .def(
                    py::init(py::overload_cast<
                        const std::shared_ptr<core::Context>&,
                        const std::string&,
                        const std::shared_ptr<IWidget>&>(&Bellows::create)),
                    py::arg("context"),
                    py::arg("text"),
                    py::arg("parent") = nullptr)
            .def_property("text", &Bellows::getText, &Bellows::setText)
            .def("setWidget", &Bellows::setWidget)
            .def_property("open", &Bellows::isOpen, &Bellows::setOpen);
        }
    }
}
