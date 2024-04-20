// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <pybind11/pybind11.h>

namespace tg
{
    namespace ui
    {
        void bind(pybind11::module_&);

        void buttonGroup(pybind11::module_&);
        void checkBox(pybind11::module_&);
        void colorPopup(pybind11::module_&);
        void colorSwatch(pybind11::module_&);
        void colorWidget(pybind11::module_&);
        void doubleEdit(pybind11::module_&);
        void doubleEditSlider(pybind11::module_&);
        void doubleModel(pybind11::module_&);
        void doubleSlider(pybind11::module_&);
        void floatEdit(pybind11::module_&);
        void floatEditSlider(pybind11::module_&);
        void floatModel(pybind11::module_&);
        void floatSlider(pybind11::module_&);
        void groupBox(pybind11::module_&);
        void iButton(pybind11::module_&);
        void iPopup(pybind11::module_&);
        void iWidget(pybind11::module_&);
        void iWidgetPopup(pybind11::module_&);
        void iWindow(pybind11::module_&);
        void intEdit(pybind11::module_&);
        void intEditSlider(pybind11::module_&);
        void intModel(pybind11::module_&);
        void intSlider(pybind11::module_&);
        void mdiCanvas(pybind11::module_&);
        void mdiWidget(pybind11::module_&);
        void pushButton(pybind11::module_&);
        void rowLayout(pybind11::module_&);
        void scrollArea(pybind11::module_&);
        void scrollWidget(pybind11::module_&);
        void style(pybind11::module_&);
        void toolButton(pybind11::module_&);
        void widgetOptions(pybind11::module_&);
    }
}
