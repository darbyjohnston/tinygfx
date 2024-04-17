// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Bindings.h>

#include <tgCore/Vector.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace core
    {
        void vector(py::module_& m)
        {
            py::class_<V2I>(m, "V2I")
                .def(py::init<>())
                .def(py::init<int, int>())
                .def(
                    "__setitem__",
                    [](V2I& self, unsigned index, int v)
                    {
                        self.e.at(index) = v;
                    })
                .def(
                    "__getitem__",
                    [](V2I& self, unsigned index)
                    {
                        return self.e.at(index);
                    })
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self);

            py::class_<V2F>(m, "V2F")
                .def(py::init<>())
                .def(py::init<float, float>())
                .def(
                    "__setitem__",
                    [](V2F& self, unsigned index, float v)
                    {
                        self.e.at(index) = v;
                    })
                .def(
                    "__getitem__",
                    [](V2F& self, unsigned index)
                    {
                        return self.e.at(index);
                    })
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self);

            py::class_<V3F>(m, "V3F")
                .def(py::init<>())
                .def(py::init<float, float, float>())
                .def(
                    "__setitem__",
                    [](V3F& self, unsigned index, float v)
                    {
                        self.e.at(index) = v;
                    })
                .def(
                    "__getitem__",
                    [](V3F& self, unsigned index)
                    {
                        return self.e.at(index);
                    })
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self);

            py::class_<V4F>(m, "V4F")
                .def(py::init<>())
                .def(py::init<float, float, float, float>())
                .def(
                    "__setitem__",
                    [](V4F& self, unsigned index, float v)
                    {
                        self.e.at(index) = v;
                    })
                .def(
                    "__getitem__",
                    [](V4F& self, unsigned index)
                    {
                        return self.e.at(index);
                    })
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self);
        }
    }
}
