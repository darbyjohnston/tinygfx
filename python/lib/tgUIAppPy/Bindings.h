// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <pybind11/pybind11.h>

namespace tg
{
    namespace ui_app
    {
        void bind(pybind11::module_&);

        void app(pybind11::module_&);
        void window(pybind11::module_&);
    }
}
