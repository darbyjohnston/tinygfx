// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Box.h>

#include <tgCore/Box.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

namespace tg
{
    namespace core
    {
        void box(py::module_& m)
        {
            py::class_<Box2I>(m, "Box2I")
                .def(py::init<>())
                .def(py::init<V2I, V2I>())
                .def(py::init<V2I, Size2I>())
                .def(py::init<int, int, int, int>())
                .def_readwrite("min", &Box2I::min)
                .def_readwrite("max", &Box2I::max)
                .def_property_readonly("x", &Box2I::x)
                .def_property_readonly("y", &Box2I::y)
                .def_property_readonly("size", &Box2I::size)
                .def_property_readonly("w", &Box2I::w)
                .def_property_readonly("h", &Box2I::h)
                .def(py::self == py::self)
                .def(py::self != py::self);

            py::class_<Box2F>(m, "Box2F")
                .def(py::init<>())
                .def(py::init<V2F, V2F>())
                .def(py::init<V2F, Size2F>())
                .def(py::init<float, float, float, float>())
                .def_readwrite("min", &Box2F::min)
                .def_readwrite("max", &Box2F::max)
                .def_property_readonly("x", &Box2F::x)
                .def_property_readonly("y", &Box2F::y)
                .def_property_readonly("size", &Box2F::size)
                .def_property_readonly("w", &Box2F::w)
                .def_property_readonly("h", &Box2F::h)
                .def(py::self == py::self)
                .def(py::self != py::self);

            py::class_<Box3F>(m, "Box3F")
                .def(py::init<>())
                .def(py::init<V3F, V3F>())
                .def(py::init<V3F, Size3F>())
                .def(py::init<float, float, float, float, float, float>())
                .def_readwrite("min", &Box3F::min)
                .def_readwrite("max", &Box3F::max)
                .def_property_readonly("x", &Box3F::x)
                .def_property_readonly("y", &Box3F::y)
                .def_property_readonly("z", &Box3F::z)
                .def_property_readonly("size", &Box3F::size)
                .def_property_readonly("w", &Box3F::w)
                .def_property_readonly("h", &Box3F::h)
                .def_property_readonly("d", &Box3F::d)
                .def(py::self == py::self)
                .def(py::self != py::self);

            m.def("center", [](const Box2I& v) { return center(v); });
            m.def("center", [](const Box2F& v) { return center(v); });
            m.def("center", [](const Box3F& v) { return center(v); });

            m.def("area", [](const Box2I& v) { return area(v); });
            m.def("area", [](const Box2F& v) { return area(v); });

            m.def("volume", [](const Box3F& v) { return volume(v); });

            m.def("move", [](const Box2I& v, const V2I& m) { return move(v, m); });
            m.def("move", [](const Box2F& v, const V2F& m) { return move(v, m); });
            m.def("move", [](const Box3F& v, const V3F& m) { return move(v, m); });

            m.def("contains",
                [](const Box2I& a, const Box2I& b) { return contains(a, b); });
            m.def("contains",
                [](const Box2F& a, const Box2F& b) { return contains(a, b); });
            m.def("contains",
                [](const Box2I& a, const V2I& b) { return contains(a, b); });
            m.def("contains",
                [](const Box2F& a, const V2F& b) { return contains(a, b); });

            m.def("intersects",
                [](const Box2I& a, const Box2I& b) { return intersects(a, b); });
            m.def("intersects",
                [](const Box2F& a, const Box2F& b) { return intersects(a, b); });

            m.def("intersect",
                [](const Box2I& a, const Box2I& b) { return intersect(a, b); });
            m.def("intersect",
                [](const Box2F& a, const Box2F& b) { return intersect(a, b); });

            m.def("expand",
                [](const Box2I& a, const Box2I& b) { return expand(a, b); });
            m.def("expand",
                [](const Box2F& a, const Box2F& b) { return expand(a, b); });
            m.def("expand",
                [](const Box2I& a, const V2I& b) { return expand(a, b); });
            m.def("expand",
                [](const Box2F& a, const V2F& b) { return expand(a, b); });

            m.def("margin",
                [](const Box2I& v, const V2I& m) { return margin(v, m); });
            m.def("margin",
                [](const Box2F& v, const V2F& m) { return margin(v, m); });
            m.def("margin",
                [](const Box2I& v, int m) { return margin(v, m); });
            m.def("margin",
                [](const Box2F& v, float m) { return margin(v, m); });
            m.def("margin",
                [](const Box2I& v, int x0, int y0, int x1, int y1) { return margin(v, x0, y0, x1, y1); });
            m.def("margin",
                [](const Box2F& v, float x0, float y0, float x1, float y1) { return margin(v, x0, y0, x1, y1); });
        }
    }
}
