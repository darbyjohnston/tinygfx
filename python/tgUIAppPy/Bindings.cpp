// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIAppPy/Bindings.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace tg
{
    namespace ui_app
    {
        void bind(py::module_& m)
        {
            auto sm = m.def_submodule("tgUIApp");
            sm.doc() = "User interface applications";

            app(sm);
            window(sm);
        }
    }
}
