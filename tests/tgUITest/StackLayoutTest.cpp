// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/StackLayoutTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/Divider.h>
#include <tgUI/StackLayout.h>
#include <tgUI/Spacer.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        StackLayoutTest::StackLayoutTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::StackLayoutTest")
        {}

        StackLayoutTest::~StackLayoutTest()
        {}

        std::shared_ptr<StackLayoutTest> StackLayoutTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<StackLayoutTest>(new StackLayoutTest(context));
        }

        void StackLayoutTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("StackLayoutTest");
                auto app = App::create(
                    context,
                    argv,
                    "StackLayoutTest",
                    "Stack layout test.");
                auto window = Window::create(context, app, "StackLayoutTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto layout = StackLayout::create(context, window);
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::None);
                TG_ASSERT(SizeRole::None == layout->getMarginRole());

                auto spacer0 = Spacer::create(context, Orientation::Horizontal, layout);
                auto spacer1 = Spacer::create(context, Orientation::Horizontal, layout);
                auto spacer2 = Spacer::create(context, Orientation::Horizontal, layout);
                app->tick();
                TG_ASSERT(0 == layout->getCurrentIndex());
                TG_ASSERT(spacer0->isVisible());
                TG_ASSERT(!spacer1->isVisible());
                TG_ASSERT(!spacer2->isVisible());

                layout->setCurrentIndex(1);
                app->tick();
                TG_ASSERT(!spacer0->isVisible());
                TG_ASSERT(spacer1->isVisible());
                TG_ASSERT(!spacer2->isVisible());

                layout->setCurrentWidget(spacer2);
                app->tick();
                TG_ASSERT(2 == layout->getCurrentIndex());
                TG_ASSERT(!spacer0->isVisible());
                TG_ASSERT(!spacer1->isVisible());
                TG_ASSERT(spacer2->isVisible());

                spacer2->setParent(nullptr);
                app->tick();
                TG_ASSERT(1 == layout->getCurrentIndex());
                TG_ASSERT(!spacer0->isVisible());
                TG_ASSERT(spacer1->isVisible());
            }
        }
    }
}

