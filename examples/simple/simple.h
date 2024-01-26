// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUIApp/Window.h>

using namespace tg;

class MainWindow : public ui::Window
{
public:
    virtual ~MainWindow();
    
    static std::shared_ptr<MainWindow> create(
        const std::shared_ptr<core::Context>&,
        const std::string& name,
        const core::Size2I&);

    void drawEvent(const core::Box2I&, const ui::DrawEvent&) override;
};

