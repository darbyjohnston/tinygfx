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
                _test(context, layout);
                layout->setParent(nullptr);
                layout.reset();

                layout = HorizontalLayout::create(context, _window);
                _test(context, layout);
                layout->setParent(nullptr);
                layout.reset();

                layout = StackLayout::create(context, _window);
                _test(context, layout);
                layout->setParent(nullptr);
                layout.reset();
            }
        }

        void LayoutTest::_test(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& layout)
        {
            auto spacer = Spacer::create(context, Orientation::Horizontal, layout);
            auto divider = Divider::create(context, Orientation::Horizontal, layout);
            auto children = layout->getChildren();
            TG_ASSERT(2 == children.size());
            TG_ASSERT(std::find(
                children.begin(),
                children.end(),
                spacer) != children.end());
            TG_ASSERT(std::find(
                children.begin(),
                children.end(),
                divider) != children.end());
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

