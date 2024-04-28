// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/PieChartTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/PieChart.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        PieChartTest::PieChartTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::PieChartTest")
        {}

        PieChartTest::~PieChartTest()
        {}

        std::shared_ptr<PieChartTest> PieChartTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<PieChartTest>(new PieChartTest(context));
        }
                
        void PieChartTest::run()
        {
            {
                PieChartData a;
                PieChartData b;
                b.text = "Pie";
                TG_ASSERT(a == a);
                TG_ASSERT(a != b);
            }
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("PieChartTest");
                auto app = App::create(
                    context,
                    argv,
                    "PieChartTest",
                    "Pie chart test.");
                auto window = Window::create(context, app, "PieChartTest");
                auto layout = HorizontalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget = PieChart::create(context, layout);
                std::vector<PieChartData> data;
                data.push_back(PieChartData("Apples", .6F, Color4F(1.F, 0.F, 0.F)));
                data.push_back(PieChartData("Oranges", .3F, Color4F(1.F, .8F, 0.F)));
                data.push_back(PieChartData("Pears", .1F, Color4F(.8F, 1.F, 0.F)));
                widget->setData(data);
                widget->setData(data);
                TG_ASSERT(data == widget->getData());
                app->tick();
                widget->setFontRole(FontRole::Mono);
                widget->setFontRole(FontRole::Mono);
                TG_ASSERT(FontRole::Mono == widget->getFontRole());
                app->tick();
                widget->setSizeMult(2);
                widget->setSizeMult(2);
                TG_ASSERT(2 == widget->getSizeMult());
                app->tick();
            }
        }
    }
}

