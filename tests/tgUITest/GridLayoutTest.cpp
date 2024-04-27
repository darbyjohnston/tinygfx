// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/GridLayoutTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/Divider.h>
#include <tgUI/GridLayout.h>
#include <tgUI/Spacer.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        GridLayoutTest::GridLayoutTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::GridLayoutTest")
        {}

        GridLayoutTest::~GridLayoutTest()
        {}

        std::shared_ptr<GridLayoutTest> GridLayoutTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<GridLayoutTest>(new GridLayoutTest(context));
        }

        void GridLayoutTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("GridLayoutTest");
                auto app = App::create(
                    context,
                    argv,
                    "GridLayoutTest",
                    "Grid layout test.");
                auto window = Window::create(context, app, "GridLayoutTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto layout = GridLayout::create(context, window);
                layout->setSpacingRole(SizeRole::None);
                layout->setSpacingRole(SizeRole::None);
                layout->setSpacingRole(SizeRole::Spacing);
                TG_ASSERT(SizeRole::Spacing == layout->getSpacingRole());
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::None);
                TG_ASSERT(SizeRole::None == layout->getMarginRole());

                auto spacer0 = Spacer::create(context, Orientation::Horizontal, layout);
                auto spacer1 = Spacer::create(context, Orientation::Horizontal, layout);
                auto spacer2 = Spacer::create(context, Orientation::Horizontal, layout);
                spacer2->setStretch(Stretch::Expanding);
                layout->setGridPos(spacer0, 0, 0);
                layout->setGridPos(spacer1, 0, 1);
                layout->setGridPos(spacer2, 1, 1);
                app->tick();

                spacer2->setParent(nullptr);
                app->tick();
            }
        }
    }
}

