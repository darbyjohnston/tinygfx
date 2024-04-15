// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUI/Init.h>

#include <tgCore/Context.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void bind(py::module_& m)
        {
            auto sm = m.def_submodule("tgUI");
            sm.doc() = "User interface";

            sm.def("init", &init, "Initialize the library.");

            style(sm);
            widgetOptions(sm);
            iWidget(sm);
            iButton(sm);
            iWindow(sm);

            buttonGroup(sm);
            checkBox(sm);
            groupBox(sm);
            pushButton(sm);
            rowLayout(sm);
            scrollArea(sm);
            scrollWidget(sm);
            toolButton(sm);
        }
    }
}
