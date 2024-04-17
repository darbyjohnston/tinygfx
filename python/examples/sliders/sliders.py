# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

from tinygfx import *
import sys

class Window(tgUIApp.Window):
    def __init__(self, context, name, size):
        tgUIApp.Window.__init__(self, context, name, size)
        
        # Create the layout.
        self.layout = tgUI.VerticalLayout(context)
        self.layout.marginRole = tgUI.SizeRole.Margin
        self.scrollWidget = tgUI.ScrollWidget(context, tgUI.ScrollType.Both, self)
        self.scrollWidget.setWidget(self.layout);
        
        # Create integer sliders.
        groupBox = tgUI.GroupBox(context, self.layout);
        groupBox.text = "Integer sliders"
        vLayout = tgUI.VerticalLayout(context, groupBox)
        intEditSlider = tgUI.IntEditSlider(context, None, vLayout)
        intEditSlider.setCallback(lambda value: print("Int:", value))
        intEditSlider = tgUI.IntEditSlider(context, None, vLayout)
        intEditSlider.range = tgCore.RangeI(100, 200)
        intEditSlider.setCallback(lambda value: print("Int:", value))
        intEditSlider = tgUI.IntEditSlider(context, None, vLayout)
        intEditSlider.range = tgCore.RangeI(-100, 100)
        intEditSlider.setCallback(lambda value: print("Int:", value))
        
        # Create float sliders.
        groupBox = tgUI.GroupBox(context, self.layout);
        groupBox.text = "Float sliders"
        vLayout = tgUI.VerticalLayout(context, groupBox)
        floatEditSlider = tgUI.FloatEditSlider(context, None, vLayout)
        floatEditSlider.setCallback(lambda value: print("Float:", value))
        floatEditSlider = tgUI.FloatEditSlider(context, None, vLayout)
        floatEditSlider.range = tgCore.RangeF(100, 200)
        floatEditSlider.setCallback(lambda value: print("Float:", value))
        floatEditSlider = tgUI.FloatEditSlider(context, None, vLayout)
        floatEditSlider.range = tgCore.RangeF(-100, 100)
        floatEditSlider.setCallback(lambda value: print("Float:", value))
        
        # Create double sliders.
        groupBox = tgUI.GroupBox(context, self.layout);
        groupBox.text = "Double sliders"
        vLayout = tgUI.VerticalLayout(context, groupBox)
        doubleEditSlider = tgUI.DoubleEditSlider(context, None, vLayout)
        doubleEditSlider.setCallback(lambda value: print("Double:", value))
        doubleEditSlider = tgUI.DoubleEditSlider(context, None, vLayout)
        doubleEditSlider.range = tgCore.RangeD(100, 200)
        doubleEditSlider.setCallback(lambda value: print("Double:", value))
        doubleEditSlider = tgUI.DoubleEditSlider(context, None, vLayout)
        doubleEditSlider.range = tgCore.RangeD(-100, 100)
        doubleEditSlider.setCallback(lambda value: print("Double:", value))
        
context = tgCore.Context()
app = tgUIApp.App(context, sys.argv, "buttons", "Buttons example")
if 0 == app.getExit():
    window = Window(context, "buttons", tgCore.Size2I(1280, 960))
    app.addWindow(window)
    window.show()
    app.run()
    window = None
