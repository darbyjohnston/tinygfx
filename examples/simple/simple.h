// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUIApp/Window.h>

using namespace tg;

class Window : public ui::Window
{
    TG_NON_COPYABLE(Window);

protected:
    Window(
        const std::shared_ptr<core::Context>&,
        const std::string& name,
        const core::Size2I&);

public:
    virtual ~Window();
    
    static std::shared_ptr<Window> create(
        const std::shared_ptr<core::Context>&,
        const std::string& name,
        const core::Size2I&);

    void drawEvent(const core::Box2I&, const ui::DrawEvent&) override;
};

