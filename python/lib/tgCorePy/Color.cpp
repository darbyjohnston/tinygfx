// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Bindings.h>

#include <tgCore/Color.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace core
    {
        void color(py::module_& m)
        {
            py::class_<Color1F>(m, "Color1F")
                .def(py::init<>())
                .def(py::init<float>())
                .def(
                    "__setitem__",
                    [](Color1F& self, unsigned index, float v)
                    {
                        self.e.at(index) = v;
                    })
                .def(
                    "__getitem__",
                    [](Color1F& self, unsigned index)
                    {
                        return self.e.at(index);
                    })
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self);

            py::class_<Color2F>(m, "Color2F")
                .def(py::init<>())
                .def(py::init<float>())
                .def(py::init<float, float>())
                .def(
                    "__setitem__",
                    [](Color2F& self, unsigned index, float v)
                    {
                        self.e.at(index) = v;
                    })
                .def(
                    "__getitem__",
                    [](Color2F& self, unsigned index)
                    {
                        return self.e.at(index);
                    })
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self);

            py::class_<Color3F>(m, "Color3F")
                .def(py::init<>())
                .def(py::init<float, float, float>())
                .def(
                    "__setitem__",
                    [](Color3F& self, unsigned index, float v)
                    {
                        self.e.at(index) = v;
                    })
                .def(
                    "__getitem__",
                    [](Color3F& self, unsigned index)
                    {
                        return self.e.at(index);
                    })
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self);

            py::class_<Color4F>(m, "Color4F")
                .def(py::init<>())
                .def(py::init<float, float, float>())
                .def(py::init<float, float, float, float>())
                .def(
                    "__setitem__",
                    [](Color4F& self, unsigned index, float v)
                    {
                        self.e.at(index) = v;
                    })
                .def(
                    "__getitem__",
                    [](Color4F& self, unsigned index)
                    {
                        return self.e.at(index);
                    })
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self);
        }
    }
}
