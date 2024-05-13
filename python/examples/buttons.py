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
        
        # Create push buttons
        groupBox = tgUI.GroupBox(context, "Push Buttons", self.layout);
        hLayout = tgUI.HorizontalLayout(context, groupBox)
        pushButton = tgUI.PushButton(context, "Click", hLayout)
        pushButton.setClickedCallback(lambda: print("Click"))
        pushButton = tgUI.PushButton(context, "Text", hLayout)
        pushButton.icon = "Settings"
        pushButton = tgUI.PushButton(context, "Disabled", hLayout)
        pushButton.enabled = False
        
        # Create tool buttons
        groupBox = tgUI.GroupBox(context, "Tool Buttons", self.layout)
        hLayout = tgUI.HorizontalLayout(context, groupBox)
        self.toolButtonGroup = tgUI.ButtonGroup(context, tgUI.ButtonGroupType.Radio)
        self.toolButtonGroup.setCheckedCallback(lambda index, checked: print("Tool:", index))
        hLayout = tgUI.HorizontalLayout(context, groupBox)
        toolIcons = [
            "PlaybackReverse",
            "PlaybackStop",
            "PlaybackForward"
        ]
        hLayout2 = tgUI.HorizontalLayout(context, hLayout)
        hLayout2.spacingRole = tgUI.SizeRole.SizeRoleNone
        for i in range(0, 3):
            toolButton = tgUI.ToolButton(context, hLayout2)
            toolButton.checkable = True
            toolButton.checked = 0 == i
            toolButton.icon = toolIcons[i]
            self.toolButtonGroup.addButton(toolButton)
        toolButton = tgUI.ToolButton(context, "Text", hLayout)
        toolButton = tgUI.ToolButton(context, "Text", hLayout)
        toolButton.icon = "Settings"
        toolButton = tgUI.ToolButton(context, "Disabled", hLayout)
        toolButton.enabled = False
        self.toolButtonGroup.addButton(toolButton)
        
        # Create check boxes
        groupBox = tgUI.GroupBox(context, "Check Boxes", self.layout);
        vLayout = tgUI.VerticalLayout(context, groupBox)
        checkBox = tgUI.CheckBox(context, "Checkable", vLayout)
        checkBox.setCheckedCallback(lambda checked: print("Checked:", checked))
        checkBox = tgUI.CheckBox(context, "Disabled", vLayout)
        checkBox.enabled = False

context = tgCore.Context()
app = tgUIApp.App(context, sys.argv, "buttons", "Buttons example")
if 0 == app.getExit():
    window = Window(context, "buttons", tgCore.Size2I(1280, 960))
    app.addWindow(window)
    window.show()
    app.run()
    window = None
