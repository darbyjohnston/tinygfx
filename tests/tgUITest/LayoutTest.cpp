// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/LayoutTest.h>

#include <tgUI/Divider.h>
#include <tgUI/RowLayout.h>
#include <tgUI/Spacer.h>
#include <tgUI/StackLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        LayoutTest::LayoutTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::LayoutTest")
        {}

        LayoutTest::~LayoutTest()
        {}

        std::shared_ptr<LayoutTest> LayoutTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<LayoutTest>(new LayoutTest(context));
        }

        void LayoutTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("LayoutTest");
                _app = App::create(context, argv, "LayoutTest", "Layout test.");                _window = Window::create(context, "ButtonTest", Size2I(1280, 960));
                _app->addWindow(_window);
                _window->show();
                _app->run();

                std::shared_ptr<IWidget> layout = VerticalLayout::create(context, _window);
                _test(context, layout, Orientation::Horizontal);
                layout->setParent(nullptr);
                layout.reset();

                layout = HorizontalLayout::create(context, _window);
                _test(context, layout, Orientation::Vertical);
                layout->setParent(nullptr);
                layout.reset();

                layout = StackLayout::create(context, _window);
                _test(context, layout, Orientation::Horizontal);
                layout->setParent(nullptr);
                layout.reset();
            }
        }

        void LayoutTest::_test(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& layout,
            ui::Orientation orientation)
        {
            TG_ASSERT(layout->getParent().lock());
            TG_ASSERT(layout->getParentT<Window>());
            TG_ASSERT(layout->getWindow());

            auto spacer = Spacer::create(context, orientation, layout);
            auto divider = Divider::create(context, orientation, layout);
            auto children = layout->getChildren();
            TG_ASSERT(2 == children.size());
            TG_ASSERT(spacer == children.front());
            TG_ASSERT(divider == children.back());
            _app->run();

            layout->moveToFront(spacer);
            _app->run();
            children = layout->getChildren();
            TG_ASSERT(divider == children.front());
            TG_ASSERT(spacer == children.back());

            layout->moveToBack(spacer);
            _app->run();
            children = layout->getChildren();
            TG_ASSERT(spacer == children.front());
            TG_ASSERT(divider == children.back());

            switch (orientation)
            {
            case Orientation::Horizontal:
                spacer->setHStretch(Stretch::Expanding);
                TG_ASSERT(Stretch::Expanding == spacer->getHStretch());
                break;
            case Orientation::Vertical:
                spacer->setVStretch(Stretch::Expanding);
                TG_ASSERT(Stretch::Expanding == spacer->getVStretch());
                break;
            default: break;
            }
            _app->run();

            spacer->setParent(nullptr);
            _app->run();
            children = layout->getChildren();
            TG_ASSERT(1 == children.size());
            TG_ASSERT(std::find(
                children.begin(),
                children.end(),
                spacer) == children.end());

            divider->setParent(nullptr);
            _app->run();
            children = layout->getChildren();
            TG_ASSERT(children.empty());
            TG_ASSERT(std::find(
                children.begin(),
                children.end(),
                divider) == children.end());
        }
    }
}

