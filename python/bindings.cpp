// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/bindings.h>
#include <tgBaseAppPy/bindings.h>
#include <tgUIPy/bindings.h>
#include <tgUIAppPy/bindings.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(tinygfx, m)
{
    m.doc() = "Small experiments with graphics programming";
    tgCorePy(m);
    tgBaseAppPy(m);
    tgUIPy(m);
    tgUIAppPy(m);
}
