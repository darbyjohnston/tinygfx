// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUIApp/Window.h>

#include <tgUI/RowLayout.h>

using namespace tg;

class Window : public ui::Window
{
protected:
    void _init(
        const std::shared_ptr<core::Context>&,
        const std::string& name,
        const core::Size2I&);

    Window();

public:
    virtual ~Window();
    
    static std::shared_ptr<Window> create(
        const std::shared_ptr<core::Context>&,
        const std::string& name,
        const core::Size2I&);

    void setGeometry(const core::Box2I&) override;
    void sizeHintEvent(const ui::SizeHintEvent&) override;

private:
    std::shared_ptr<ui::VerticalLayout> _layout;
};

