// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <pybind11/pybind11.h>

namespace tg
{
    namespace app
    {
        void bind(pybind11::module_&);
        void cmdLine(pybind11::module_&);
        void iApp(pybind11::module_&);
    }
}
