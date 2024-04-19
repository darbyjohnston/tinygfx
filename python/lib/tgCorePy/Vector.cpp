// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Bindings.h>

#include <tgCore/Vector.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <sstream>

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
                .def("__setitem__",
                    [](V2I& self, unsigned index, int v) { self.e.at(index) = v; })
                .def("__getitem__",
                    [](V2I& self, unsigned index) { return self.e.at(index); })
                .def("x", [](V2I& self) { return self.x; })
                .def("y", [](V2I& self) { return self.y; })
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self)
                .def("__repr__", [](const Size2I& v)
                    {
                        std::stringstream ss;
                        ss << v;
                        return ss.str();
                    });

            py::class_<V2F>(m, "V2F")
                .def(py::init<>())
                .def(py::init<float, float>())
                .def("__setitem__",
                    [](V2F& self, unsigned index, float v) { self.e.at(index) = v; })
                .def("__getitem__",
                    [](V2F& self, unsigned index) { return self.e.at(index); })
                .def("x", [](V2F& self) { return self.x; })
                .def("y", [](V2F& self) { return self.y; })
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self)
                .def("__repr__", [](const Size2I& v)
                    {
                        std::stringstream ss;
                        ss << v;
                        return ss.str();
                    });

            py::class_<V3F>(m, "V3F")
                .def(py::init<>())
                .def(py::init<float, float, float>())
                .def("__setitem__",
                    [](V3F& self, unsigned index, float v) { self.e.at(index) = v; })
                .def("__getitem__",
                    [](V3F& self, unsigned index) { return self.e.at(index); })
                .def("x", [](V3F& self) { return self.x; })
                .def("y", [](V3F& self) { return self.y; })
                .def("y", [](V3F& self) { return self.z; })
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self)
                .def("__repr__", [](const Size2I& v)
                    {
                        std::stringstream ss;
                        ss << v;
                        return ss.str();
                    });

            py::class_<V4F>(m, "V4F")
                .def(py::init<>())
                .def(py::init<float, float, float, float>())
                .def("__setitem__",
                    [](V4F& self, unsigned index, float v) { self.e.at(index) = v; })
                .def("__getitem__",
                    [](V4F& self, unsigned index) { return self.e.at(index); })
                .def("x", [](V4F& self) { return self.x; })
                .def("y", [](V4F& self) { return self.y; })
                .def("y", [](V4F& self) { return self.z; })
                .def("w", [](V4F& self) { return self.w; })
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self)
                .def("__repr__", [](const Size2I& v)
                    {
                        std::stringstream ss;
                        ss << v;
                        return ss.str();
                    });
        }
    }
}
