// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "popups.h"

#include <tgUIApp/App.h>

#include <tgUI/ComboBox.h>
#include <tgUI/ColorSwatch.h>
#include <tgUI/GroupBox.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ScrollWidget.h>

#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace examples
    {
        namespace popups
        {
            void Window::_init(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                const Size2I& size)
            {
                ui::Window::_init(context, name, size);

                // Create the layout and scroll widget.
                auto layout = VerticalLayout::create(context);
                layout->setMarginRole(SizeRole::Margin);
                auto scrollWidget = ScrollWidget::create(
                    context,
                    ScrollType::Both,
                    shared_from_this());
                scrollWidget->setWidget(layout);

                // Create combo boxes.
                auto groupBox = GroupBox::create(context, "Combo Boxes", layout);
                auto vLayout = VerticalLayout::create(context, groupBox);
                auto comboBox = ComboBox::create(context, getEndianLabels(), vLayout);
                comboBox->setToolTip("Endian types");
                comboBox = ComboBox::create(context, getImageTypeLabels(), vLayout);
                comboBox->setToolTip("Image types");

                // Create color swatches.
                groupBox = GroupBox::create(context, "Color Popups", layout);
                auto hLayout = HorizontalLayout::create(context, groupBox);
                const std::vector<Color4F> colors =
                {
                    Color4F(1.F, .5F, .5F),
                    Color4F(.5F, 1.F, .5F),
                    Color4F(.5F, .5F, 1.F),
                    Color4F(1.F, 1.F, .5F),
                    Color4F(.5F, 1.F, 1.F),
                    Color4F(1.F, .5F, 1.F)
                };
                for (const auto& color : colors)
                {
                    auto colorSwatch = ColorSwatch::create(context, hLayout);
                    colorSwatch->setColor(color);
                    colorSwatch->setEditable(true);
                }
            }

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
        }
    }
}

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = tg::app::convert(argc, argv);
        auto app = App::create(context, args, "popups", "Popups example");
        if (0 == app->getExit())
        {
            auto window = tg::examples::popups::Window::create(
                context,
                "popups",
                Size2I(1280, 720));
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

