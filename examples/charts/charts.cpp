// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "charts.h"

#include <tgUIApp/App.h>

#include <tgUI/GridLayout.h>
#include <tgUI/PieChart.h>
#include <tgUI/ScrollWidget.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace examples
    {
        namespace charts
        {
            void Window::_init(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                const Size2I& size)
            {
                ui::Window::_init(context, name, size);

                // Create the scroll widget.
                auto scrollWidget = ScrollWidget::create(
                    context,
                    ScrollType::Both,
                    shared_from_this());
                auto scrollLayout = GridLayout::create(context);
                scrollLayout->setMarginRole(SizeRole::Margin);
                scrollWidget->setWidget(scrollLayout);

                // Create pie charts.
                auto pieChart = PieChart::create(context, scrollLayout);
                pieChart->setData(
                    {
                        PieChartData("Red", 100.F / 3.F, Color4F(1.F, 0.F, 0.F)),
                        PieChartData("Green", 100.F / 3.F, Color4F(0.F, 1.F, 0.F)),
                        PieChartData("Blue", 100.F / 3.F, Color4F(0.F, 0.F, 1.F))
                    });
                scrollLayout->setGridPos(pieChart, 0, 0);
                pieChart = PieChart::create(context, scrollLayout);
                pieChart->setData(
                    {
                        PieChartData("Cyan", 25.F, Color4F(0.F, 1.F, 1.F)),
                        PieChartData("Magenta", 25.F, Color4F(1.F, 0.F, 1.F)),
                        PieChartData("Yellow", 25.F, Color4F(1.F, 1.F, 0.F)),
                        PieChartData("Key", 25.F, Color4F(0.F, 0.F, 0.F))
                    });
                scrollLayout->setGridPos(pieChart, 0, 1);
                pieChart = PieChart::create(context, scrollLayout);
                pieChart->setData(
                    {
                        PieChartData("Kiwis", 40.F, Color4F(.1F, .6F, .3F)),
                        PieChartData("Apples", 30.F, Color4F(.7F, .2F, 0.F)),
                        PieChartData("Grapes", 15.F, Color4F(.6F, .1F, .5F)),
                        PieChartData("Bananas", 10.F, Color4F(.8F, .7F, .1F)),
                        PieChartData("Pears", 5.F, Color4F(.5F, .8F, .6F))
                    });
                scrollLayout->setGridPos(pieChart, 0, 2);
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
        auto app = App::create(context, args, "charts", "Charts example");
        if (0 == app->getExit())
        {
            auto window = tg::examples::charts::Window::create(
                context,
                "charts",
                Size2I(1280, 720));
            app->addWindow(window);
            window->show();
            r = app->run();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

