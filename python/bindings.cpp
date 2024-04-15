// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Bindings.h>
#include <tgBaseAppPy/Bindings.h>
#include <tgUIPy/bindings.h>
#include <tgUIAppPy/bindings.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(tinygfx, m)
{
    m.doc() = "Small experiments with graphics programming";
    tg::core::bind(m);
    tg::app::bind(m);
    tg::ui::bind(m);
    tg::ui_app::bind(m);
}
