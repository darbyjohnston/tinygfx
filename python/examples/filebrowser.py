# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

from tinygfx import *

import sys
        
context = tgCore.Context()
app = tgUIApp.App(context, sys.argv, "buttons", "Buttons example")
if app.getExit() != 0:
    sys.exit(1)
for system in context.systems:
    print(system.name, system)

# Create the window.
size = tgCore.Size2I(1280, 960)
window = tgUIApp.Window(context, "buttons", size)
app.addWindow(window)

# Create the layout.
layout = tgUI.VerticalLayout(context)
layout.marginRole = tgUI.SizeRole.Margin
scrollWidget = tgUI.ScrollWidget(context, tgUI.ScrollType.Both, window)
scrollWidget.setWidget(layout);
        
# Create the file widgets.
for i in range(0, 10):
    tgUI.FileEdit(context, layout)

window.show()
app.run()
# \bug Need to manually reset the window.
window = None
