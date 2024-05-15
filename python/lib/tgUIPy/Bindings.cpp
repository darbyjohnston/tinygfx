// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Bindings.h>

#include <tgUIPy/Bellows.h>
#include <tgUIPy/ButtonGroup.h>
#include <tgUIPy/CheckBox.h>
#include <tgUIPy/ColorPopup.h>
#include <tgUIPy/ColorSwatch.h>
#include <tgUIPy/ColorWidget.h>
#include <tgUIPy/DoubleEdit.h>
#include <tgUIPy/DoubleEditSlider.h>
#include <tgUIPy/DoubleModel.h>
#include <tgUIPy/DoubleSlider.h>
#include <tgUIPy/Event.h>
#include <tgUIPy/FileBrowser.h>
#include <tgUIPy/FileEdit.h>
#include <tgUIPy/FloatEdit.h>
#include <tgUIPy/FloatEditSlider.h>
#include <tgUIPy/FloatModel.h>
#include <tgUIPy/FloatSlider.h>
#include <tgUIPy/GroupBox.h>
#include <tgUIPy/IButton.h>
#include <tgUIPy/IntEdit.h>
#include <tgUIPy/IntEditSlider.h>
#include <tgUIPy/IntModel.h>
#include <tgUIPy/IntSlider.h>
#include <tgUIPy/IPopup.h>
#include <tgUIPy/IWidget.h>
#include <tgUIPy/IWidgetPopup.h>
#include <tgUIPy/IWindow.h>
#include <tgUIPy/MDICanvas.h>
#include <tgUIPy/MDIWidget.h>
#include <tgUIPy/PushButton.h>
#include <tgUIPy/RecentFilesModel.h>
#include <tgUIPy/RowLayout.h>
#include <tgUIPy/ScrollArea.h>
#include <tgUIPy/ScrollWidget.h>
#include <tgUIPy/Style.h>
#include <tgUIPy/TabBar.h>
#include <tgUIPy/TabWidget.h>
#include <tgUIPy/ToolButton.h>
#include <tgUIPy/WidgetOptions.h>

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

            bellows(sm);
            buttonGroup(sm);
            checkBox(sm);
            colorPopup(sm);
            colorSwatch(sm);
            colorWidget(sm);
            doubleEdit(sm);
            doubleEditSlider(sm);
            doubleModel(sm);
            doubleSlider(sm);
            fileBrowser(sm);
            fileEdit(sm);
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
            recentFilesModel(sm);
            rowLayout(sm);
            scrollArea(sm);
            scrollWidget(sm);
            tabBar(sm);
            tabWidget(sm);
            toolButton(sm);
        }
    }
}
