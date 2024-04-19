// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Bindings.h>

#include <tgCore/Size.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <sstream>

namespace py = pybind11;

namespace tg
{
    namespace core
    {
        void size(py::module_& m)
        {
            py::class_<Size2I>(m, "Size2I")
                .def(py::init<>())
                .def(py::init<int, int>())
                .def("__setitem__",
                    [](Size2I& self, unsigned index, int v) { self.e.at(index) = v; })
                .def("__getitem__",
                    [](Size2I& self, unsigned index) { return self.e.at(index); })
                .def("w", [](Size2I& self) { return self.w; })
                .def("h", [](Size2I& self) { return self.h; })
                .def("isValid", &Size2I::isValid)
                .def(pybind11::self + int())
                .def(pybind11::self - int())
                .def(pybind11::self * int())
                .def(pybind11::self / int())
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self)
                .def("__repr__", [](const Size2I& v)
                    {
                        std::stringstream ss;
                        ss << v;
                        return ss.str();
                    });

            py::class_<Size2F>(m, "Size2F")
                .def(py::init<>())
                .def(py::init<float, float>())
                .def("__setitem__",
                    [](Size2F& self, unsigned index, float v) { self.e.at(index) = v; })
                .def("__getitem__",
                    [](Size2F& self, unsigned index) { return self.e.at(index); })
                .def("w", [](Size2F& self) { return self.w; })
                .def("h", [](Size2F& self) { return self.h; })
                .def("isValid", &Size2F::isValid)
                .def(pybind11::self + float())
                .def(pybind11::self - float())
                .def(pybind11::self * float())
                .def(pybind11::self / float())
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self)
                .def("__repr__", [](const Size2I& v)
                    {
                        std::stringstream ss;
                        ss << v;
                        return ss.str();
                    });

            py::class_<Size3F>(m, "Size3F")
                .def(py::init<>())
                .def(py::init<float, float, float>())
                .def("__setitem__",
                    [](Size3F& self, unsigned index, float v) { self.e.at(index) = v; })
                .def("__getitem__",
                    [](Size3F& self, unsigned index) { return self.e.at(index); })
                .def("w", [](Size3F& self) { return self.w; })
                .def("h", [](Size3F& self) { return self.h; })
                .def("d", [](Size3F& self) { return self.d; })
                .def("isValid", &Size3F::isValid)
                .def(pybind11::self + float())
                .def(pybind11::self - float())
                .def(pybind11::self * float())
                .def(pybind11::self / float())
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self)
                .def("__repr__", [](const Size2I& v)
                    {
                        std::stringstream ss;
                        ss << v;
                        return ss.str();
                    });

            m.def("aspectRatio", [](const Size2I& v) { return aspectRatio(v); });
            m.def("aspectRatio", [](const Size2F& v) { return aspectRatio(v); });

            m.def("area", [](const Size2I& v) { return area(v); });
            m.def("area", [](const Size2F& v) { return area(v); });

            m.def("volume", [](const Size3F& v) { return volume(v); });
        }
    }
}
