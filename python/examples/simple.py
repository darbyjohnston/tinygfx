# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

from tinygfx import *

import sys

class Window(tgUIApp.Window):
    def __init__(self, context, name, size):
        tgUIApp.Window.__init__(self, context, name, size)
    
    def drawEvent(self, drawRect, event):
        tgUIApp.Window.drawEvent(self, drawRect, event)
        
        text = "Hello world"
        fontInfo = tgCore.FontInfo()
        fontInfo.size = 0
        textSize = tgCore.Size2I()
        g = tgCore.margin(self.geometry, -100)
        while textSize.w < g.w and textSize.h < g.h:
            fontInfo.size += 10
            textSize = event.fontSystem.getSize(text, fontInfo)
        #glyphs = event.fontSystem.getGlyphs(text, fontInfo)
        fontMetrics = event.fontSystem.getMetrics(fontInfo)
        print(event.render)
        event.render.drawRect(
            tgCore.Box2F(10, 10, 100, 100),
            tgCore.Color4F(1, 1, 1))
        #event.render.drawText(
        #    glyphs,
        #    fontMetrics,
        #    tgCore.V2F(0, 0),
        #    tgCore.Color4F(1, 1, 1, 1))
        #    #tgCore.center(tgCore.Box2F(g.x, g.y, g.w, g.h)) -
        #    #tgCore.V2F(textSize.w, textSize.h) / 2,
        #    #tgCore.Color4F(1, 1, 1))
    
context = tgCore.Context()
app = tgUIApp.App(context, sys.argv, "simple", "Simple example")
if 0 == app.getExit():
    window = Window(context, "simple", tgCore.Size2I(1280, 960))
    app.addWindow(window)
    window.show()
    app.run()
    window = None
