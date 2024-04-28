// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/IconTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/Icon.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>
#include <tgCore/Time.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        IconTest::IconTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::IconTest")
        {}

        IconTest::~IconTest()
        {}

        std::shared_ptr<IconTest> IconTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IconTest>(new IconTest(context));
        }
                
        void IconTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("IconTest");
                auto app = App::create(
                    context,
                    argv,
                    "IconTest",
                    "Icon test.");
                auto window = Window::create(context, app, "IconTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget = Icon::create(context, "PlaybackForward", layout);
                widget->setIcon("PlaybackStop");
                widget->setIcon("PlaybackStop");
                TG_ASSERT("PlaybackStop" == widget->getIcon());
                app->tick(1000);
                widget->setIcon("PlaybackForward");
                widget->setIcon("PlaybackForward");
                app->tick(1000);
                widget->setMarginRole(SizeRole::Margin);
                widget->setMarginRole(SizeRole::Margin);
                TG_ASSERT(SizeRole::Margin == widget->getMarginRole());
                widget->setMarginRole(SizeRole::None);

                widget->setEnabled(false);
                app->tick();
                widget->setEnabled(true);
                app->tick();

                widget->hide();
                app->tick();
                widget->show();
                app->tick();

                app->setDisplayScale(2.F);
                app->tick(1000);
                app->setDisplayScale(1.F);
                app->tick(1000);
            }
        }
    }
}

