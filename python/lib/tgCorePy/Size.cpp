// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Bindings.h>

#include <tgCore/Size.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

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
                .def(
                    "__setitem__",
                    [](Size2I& self, unsigned index, int v)
                    {
                        self.e.at(index) = v;
                    })
                .def(
                    "__getitem__",
                    [](Size2I& self, unsigned index)
                    {
                        return self.e.at(index);
                    })
                .def("isValid", &Size2I::isValid)
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self);

            py::class_<Size2F>(m, "Size2F")
                .def(py::init<>())
                .def(py::init<float, float>())
                .def(
                    "__setitem__",
                    [](Size2F& self, unsigned index, float v)
                    {
                        self.e.at(index) = v;
                    })
                .def(
                    "__getitem__",
                    [](Size2F& self, unsigned index)
                    {
                        return self.e.at(index);
                    })
                .def("isValid", &Size2F::isValid)
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self);

            py::class_<Size3F>(m, "Size3F")
                .def(py::init<>())
                .def(py::init<float, float, float>())
                .def(
                    "__setitem__",
                    [](Size3F& self, unsigned index, float v)
                    {
                        self.e.at(index) = v;
                    })
                .def(
                    "__getitem__",
                    [](Size3F& self, unsigned index)
                    {
                        return self.e.at(index);
                    })
                .def("isValid", &Size3F::isValid)
                .def(pybind11::self == pybind11::self)
                .def(pybind11::self != pybind11::self);
                    
            //! \todo These cause linker errors?
            /*m.def("aspectRatio", &aspectRatio<Size2I>);
            m.def("aspectRatio", &aspectRatio<Size2F>);
            m.def("area", &area<Size2I>);
            m.def("area", &area<Size2F>);
            m.def("volume", &area<Size3F>);*/
        }
    }
}
