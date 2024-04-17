// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Bindings.h>

#include <tgCore/Context.h>
#include <tgCore/Init.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace tg
{
    namespace core
    {
        void bind(py::module_& m)
        {
            auto sm = m.def_submodule("tgCore");
            sm.doc() = "Core functionality";

            sm.def("init", &init, "Initialize the library.");

            context(sm);
            os(sm);
            range(sm);
            size(sm);
            vector(sm);
            box(sm);
        }
    }
}
