// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/RowLayoutTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/Divider.h>
#include <tgUI/Spacer.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        RowLayoutTest::RowLayoutTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::RowLayoutTest")
        {}

        RowLayoutTest::~RowLayoutTest()
        {}

        std::shared_ptr<RowLayoutTest> RowLayoutTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<RowLayoutTest>(new RowLayoutTest(context));
        }

        void RowLayoutTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("RowLayoutTest");
                auto app = App::create(
                    context,
                    argv,
                    "RowLayoutTest",
                    "Row layout test.");
                auto window = Window::create(context, app, "RowLayoutTest");
                app->addWindow(window);
                window->show();
                app->tick();

                std::shared_ptr<RowLayout> layout = VerticalLayout::create(context, window);
                layout->setSpacingRole(SizeRole::None);
                layout->setSpacingRole(SizeRole::None);
                layout->setSpacingRole(SizeRole::Spacing);
                TG_ASSERT(SizeRole::Spacing == layout->getSpacingRole());
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::None);
                TG_ASSERT(SizeRole::None == layout->getMarginRole());
                _test(context, app, window, layout, Orientation::Horizontal);
                layout->setParent(nullptr);
                layout.reset();

                layout = HorizontalLayout::create(context, window);
                _test(context, app, window, layout, Orientation::Vertical);
                layout->setParent(nullptr);
                layout.reset();
            }
        }

        void RowLayoutTest::_test(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Window>& window,
            const std::shared_ptr<RowLayout>& layout,
            Orientation orientation)
        {
            auto spacer = Spacer::create(context, orientation, layout);
            spacer->setSpacingRole(SizeRole::None);
            spacer->setSpacingRole(SizeRole::None);
            TG_ASSERT(SizeRole::None == spacer->getSpacingRole());
            spacer->setSpacingRole(SizeRole::Spacing);
            auto divider = Divider::create(context, orientation, layout);
            auto children = layout->getChildren();
            TG_ASSERT(2 == children.size());
            TG_ASSERT(spacer == children.front());
            TG_ASSERT(divider == children.back());
            app->tick();

            layout->moveToFront(spacer);
            app->tick();
            children = layout->getChildren();
            TG_ASSERT(divider == children.front());
            TG_ASSERT(spacer == children.back());

            layout->moveToBack(spacer);
            app->tick();
            children = layout->getChildren();
            TG_ASSERT(spacer == children.front());
            TG_ASSERT(divider == children.back());

            switch (orientation)
            {
            case Orientation::Horizontal:
                spacer->setHStretch(Stretch::Expanding);
                spacer->setHStretch(Stretch::Expanding);
                spacer->setHStretch(Stretch::Fixed);
                spacer->setStretch(Stretch::Expanding, Stretch::Fixed);
                spacer->setStretch(Stretch::Expanding, Stretch::Fixed);
                spacer->setStretch(Stretch::Fixed, Stretch::Fixed);
                spacer->setStretch(Stretch::Expanding);
                spacer->setStretch(Stretch::Expanding);
                TG_ASSERT(Stretch::Expanding == spacer->getHStretch());
                spacer->setHAlign(HAlign::Right);
                spacer->setHAlign(HAlign::Right);
                spacer->setHAlign(HAlign::Center);
                spacer->setAlign(HAlign::Right, VAlign::Center);
                spacer->setAlign(HAlign::Right, VAlign::Center);
                spacer->setAlign(HAlign::Center, VAlign::Center);
                TG_ASSERT(HAlign::Center == spacer->getHAlign());
                break;
            case Orientation::Vertical:
                spacer->setVStretch(Stretch::Expanding);
                spacer->setVStretch(Stretch::Expanding);
                spacer->setVStretch(Stretch::Fixed);
                spacer->setStretch(Stretch::Fixed, Stretch::Expanding);
                spacer->setStretch(Stretch::Fixed, Stretch::Expanding);
                spacer->setStretch(Stretch::Fixed);
                spacer->setStretch(Stretch::Expanding);
                spacer->setStretch(Stretch::Expanding);
                TG_ASSERT(Stretch::Expanding == spacer->getVStretch());
                spacer->setVAlign(VAlign::Bottom);
                spacer->setVAlign(VAlign::Bottom);
                spacer->setVAlign(VAlign::Center);
                spacer->setAlign(HAlign::Center, VAlign::Bottom);
                spacer->setAlign(HAlign::Center, VAlign::Bottom);
                spacer->setAlign(HAlign::Center, VAlign::Center);
                TG_ASSERT(VAlign::Center == spacer->getVAlign());
                break;
            default: break;
            }
            app->tick();

            spacer->hide();
            spacer->hide();
            app->tick();
            TG_ASSERT(!spacer->isVisible());
            TG_ASSERT(!spacer->isVisible(false));
            TG_ASSERT(spacer->isClipped());
            spacer->show();
            app->tick();

            spacer->setParent(nullptr);
            app->tick();
            children = layout->getChildren();
            TG_ASSERT(1 == children.size());
            TG_ASSERT(divider == children.front());
            spacer->setParent(layout);
            app->tick();
            children = layout->getChildren();
            TG_ASSERT(2 == children.size());
            TG_ASSERT(divider == children.front());
            TG_ASSERT(spacer == children.back());
            spacer->setParent(nullptr);
            app->tick();

            divider->setParent(nullptr);
            app->tick();
            children = layout->getChildren();
            TG_ASSERT(children.empty());
        }
    }
}

