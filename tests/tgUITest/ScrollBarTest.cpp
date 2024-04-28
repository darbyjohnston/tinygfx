// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/ScrollBarTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/ScrollBar.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        ScrollBarTest::ScrollBarTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::ScrollBarTest")
        {}

        ScrollBarTest::~ScrollBarTest()
        {}

        std::shared_ptr<ScrollBarTest> ScrollBarTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ScrollBarTest>(new ScrollBarTest(context));
        }
                
        void ScrollBarTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ScrollBarTest");
                auto app = App::create(
                    context,
                    argv,
                    "ScrollBarTest",
                    "Scroll bar test.");
                auto window = Window::create(context, app, "ScrollBarTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();
                _test(context, app, window, layout, Orientation::Horizontal);
                _test(context, app, window, layout, Orientation::Vertical);
            }
        }

        void ScrollBarTest::_test(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Window>& window,
            const std::shared_ptr<VerticalLayout>& layout,
            Orientation orientation)
        {
            auto widget = ScrollBar::create(context, orientation, layout);
            widget->setScrollSize(10000);
            widget->setScrollSize(10000);
            TG_ASSERT(10000 == widget->getScrollSize());
            widget->setScrollPos(1000);
            widget->setScrollPos(1000);
            TG_ASSERT(1000 == widget->getScrollPos());

            window->setCursorEnter(true);
            Box2I g = widget->getGeometry();
            V2I c = center(g);
            window->setCursorPos(c);
            switch (orientation)
            {
            case Orientation::Horizontal:
                window->setButton(0, true);
                window->setCursorPos(c + V2I(100, 0));
                window->setButton(0, false);
                window->setButton(0, true);
                window->setCursorPos(c + V2I(-100, 0));
                window->setButton(0, false);
                break;
            case Orientation::Vertical:
                window->setButton(0, true);
                window->setCursorPos(c + V2I(0, 100));
                window->setButton(0, false);
                window->setButton(0, true);
                window->setCursorPos(c + V2I(0, -100));
                window->setButton(0, false);
                break;
            default: break;
            }
            window->setCursorPos(V2I(0, 0));

            widget->setParent(nullptr);
        }
    }
}

