// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/BellowsTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/Bellows.h>
#include <tgUI/Label.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        BellowsTest::BellowsTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::BellowsTest")
        {}

        BellowsTest::~BellowsTest()
        {}

        std::shared_ptr<BellowsTest> BellowsTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<BellowsTest>(new BellowsTest(context));
        }
                
        void BellowsTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("BellowsTest");
                auto app = App::create(
                    context,
                    argv,
                    "BellowsTest",
                    "Bellows test.");
                auto window = Window::create(context, app, "BellowsTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto bellows = Bellows::create(context, "Bellows", layout);
                bellows->setText("Test");
                TG_ASSERT("Test" == bellows->getText());
                auto label = Label::create(context, "Label");
                bellows->setWidget(label);
                bellows->setWidget(label);
                TG_ASSERT(label == bellows->getWidget());
                bellows->setOpen(true);
                bellows->setOpen(true);
                TG_ASSERT(bellows->isOpen());
                bellows->setOpen(false);

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                TG_ASSERT(bellows->isOpen());
                window->setKey(Key::Enter);
                TG_ASSERT(!bellows->isOpen());
                window->setKey(Key::Escape);
                window->setCursorPos(center(bellows->getGeometry()));
                window->setButton(0);
                TG_ASSERT(bellows->isOpen());
                window->setButton(0);
                TG_ASSERT(!bellows->isOpen());

                bellows->hide();
                app->tick();
                bellows->show();
                app->tick();
            }
        }
    }
}

