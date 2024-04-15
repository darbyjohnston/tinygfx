// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <pybind11/pybind11.h>

namespace tg
{
    namespace ui
    {
        void bind(pybind11::module_&);

        void buttonGroup(pybind11::module_&);
        void checkBox(pybind11::module_&);
        void groupBox(pybind11::module_&);
        void iButton(pybind11::module_&);
        void iWidget(pybind11::module_&);
        void iWindow(pybind11::module_&);
        void pushButton(pybind11::module_&);
        void rowLayout(pybind11::module_&);
        void scrollArea(pybind11::module_&);
        void scrollWidget(pybind11::module_&);
        void style(pybind11::module_&);
        void toolButton(pybind11::module_&);
        void widgetOptions(pybind11::module_&);
    }
}
