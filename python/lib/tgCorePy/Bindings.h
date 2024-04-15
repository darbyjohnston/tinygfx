// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <pybind11/pybind11.h>

namespace tg
{
    namespace core
    {
        void bind(pybind11::module_&);

        void context(pybind11::module_&);
        void os(pybind11::module_&);
        void size(pybind11::module_&);
        void vector(pybind11::module_&);
        void box(pybind11::module_&);
    }
}
