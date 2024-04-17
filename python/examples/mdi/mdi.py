# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

from tinygfx import *
import sys

class Window(tgUIApp.Window):
    def __init__(self, context, name, size):
        tgUIApp.Window.__init__(self, context, name, size)
        
        # Create the scroll widget.
        self.scrollWidget = tgUI.ScrollWidget(context, tgUI.ScrollType.Both, self)
        
        # Create the MDI canvas.
        self.canvas = tgUI.MDICanvas(context)
        self.scrollWidget.setWidget(self.canvas)
        
        # Create the MDI widgets.
        random = tgCore.Random()
        for i in range(0, 10):
            colorWidget = tgUI.ColorWidget(context)
            colorWidget.color = tgCore.Color4F(
                random.getF(),
                random.getF(),
                random.getF())
            self.canvas.addWidget(
                "Color {0}".format(i),
                tgCore.V2I(random.getI(0, size[0]), random.getI(0, size[1])),
                colorWidget)
        
context = tgCore.Context()
app = tgUIApp.App(context, sys.argv, "buttons", "Buttons example")
if 0 == app.getExit():
    window = Window(context, "buttons", tgCore.Size2I(1280, 960))
    app.addWindow(window)
    window.show()
    app.run()
    window = None
