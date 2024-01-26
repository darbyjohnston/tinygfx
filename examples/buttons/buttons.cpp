// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "buttons.h"

#include <tgUIApp/App.h>

#include <tgUI/PushButton.h>

#include <tgCore/Format.h>

using namespace tg::core;

void Window::_init(
    const std::shared_ptr<Context>& context,
    const std::string& name,
    const Size2I& size)
{
    ui::Window::_init(context, name, size);
        
    _layout = ui::VerticalLayout::create(context, shared_from_this());
    
    for (size_t i = 0; i < 10; ++i)
    {
        auto pushButton = ui::PushButton::create(
            context,
            Format("Push Button {0}").arg(i),
            _layout);
    }
}

Window::Window()
{}

Window::~Window()
{}

std::shared_ptr<Window> Window::create(
    const std::shared_ptr<Context>& context,
    const std::string& name,
    const Size2I& size)
{
    auto out = std::shared_ptr<Window>(new Window);
    out->_init(context, name, size);
    return out;
}

void Window::setGeometry(const Box2I& value)
{
    ui::Window::setGeometry(value);
    _layout->setGeometry(value);
}

void Window::sizeHintEvent(const ui::SizeHintEvent& event)
{
    ui::Window::sizeHintEvent(event);
    _sizeHint = _layout->getSizeHint();
}

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = app::convert(argc, argv);
        auto app = ui::App::create(context, args, "simple", "Simple example");
        if (0 == app->getExit())
        {
            auto window = Window::create(context, "simple", Size2I(1280, 720));
            app->addWindow(window);
            window->show();
        }
        r = app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

