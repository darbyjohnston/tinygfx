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
            event(sm);
            widgetOptions(sm);
            iWidget(sm);
            iWindow(sm);
            iPopup(sm);
            iWidgetPopup(sm);
            iButton(sm);

            buttonGroup(sm);
            checkBox(sm);
            colorPopup(sm);
            colorSwatch(sm);
            colorWidget(sm);
            doubleEdit(sm);
            doubleEditSlider(sm);
            doubleModel(sm);
            doubleSlider(sm);
            floatEdit(sm);
            floatEditSlider(sm);
            floatModel(sm);
            floatSlider(sm);
            groupBox(sm);
            intEdit(sm);
            intEditSlider(sm);
            intModel(sm);
            intSlider(sm);
            mdiCanvas(sm);
            mdiWidget(sm);
            pushButton(sm);
            rowLayout(sm);
            scrollArea(sm);
            scrollWidget(sm);
            toolButton(sm);
        }
    }
}
