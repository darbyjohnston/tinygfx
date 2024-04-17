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
        self.layout.setMarginRole(tgUI.SizeRole.Margin)
        self.scrollWidget = tgUI.ScrollWidget(context, tgUI.ScrollType.Both, self)
        self.scrollWidget.setWidget(self.layout);
        
        # Create push buttons
        groupBox = tgUI.GroupBox(context, self.layout);
        groupBox.setText("Push Buttons")
        hLayout = tgUI.HorizontalLayout(context, groupBox)
        pushButton = tgUI.PushButton(context, hLayout)
        pushButton.setText("Push")
        pushButton.setClickedCallback(lambda: print("Push"))
        pushButton = tgUI.PushButton(context, hLayout)
        pushButton.setText("Disabled")
        pushButton.enabled = False
        
        # Create tool buttons
        groupBox = tgUI.GroupBox(context, self.layout);
        groupBox.setText("Tool Buttons")
        hLayout = tgUI.HorizontalLayout(context, groupBox)
        hLayout.setSpacingRole(tgUI.SizeRole.SizeRoleNone)
        self.toolButtonGroup = tgUI.ButtonGroup(context, tgUI.ButtonGroupType.Radio)
        self.toolButtonGroup.setCheckedCallback(lambda index, checked: print("Tool:", index))
        toolIcons = [
            "PlaybackReverse",
            "PlaybackStop",
            "PlaybackForward"
        ]
        for i in range(0, 3):
            toolButton = tgUI.ToolButton(context, hLayout)
            toolButton.checkable = True
            toolButton.checked = 0 == i
            toolButton.setIcon(toolIcons[i])
            self.toolButtonGroup.addButton(toolButton)
        toolButton = tgUI.ToolButton(context, hLayout)
        toolButton.setText("Disabled")
        toolButton.enabled = False
        self.toolButtonGroup.addButton(toolButton)
        
        # Create check boxes
        groupBox = tgUI.GroupBox(context, self.layout);
        groupBox.setText("Check Boxes")
        vLayout = tgUI.VerticalLayout(context, groupBox)
        checkBox = tgUI.CheckBox(context, vLayout)
        checkBox.setText("Check")
        checkBox.setCheckedCallback(lambda checked: print("Check:", checked))
        checkBox = tgUI.CheckBox(context, vLayout)
        checkBox.setText("Disabled")
        checkBox.enabled = False

context = tgCore.Context()
app = tgUIApp.App(context, sys.argv, "buttons", "Buttons example")
if 0 == app.getExit():
    window = Window(context, "buttons", tgCore.Size2I(1280, 960))
    app.addWindow(window)
    window.show()
    app.run()
    window = None
