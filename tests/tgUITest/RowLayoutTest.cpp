// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/RowLayoutTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/Label.h>
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
            auto label0 = Label::create(context, "Label 0", layout);
            auto spacer = Spacer::create(context, orientation, layout);
            spacer->setSpacingRole(SizeRole::SpacingLarge);
            spacer->setSpacingRole(SizeRole::SpacingLarge);
            TG_ASSERT(SizeRole::SpacingLarge == spacer->getSpacingRole());
            auto label1 = Label::create(context, "Label 1", layout);
            auto children = layout->getChildren();
            TG_ASSERT(3 == children.size());
            TG_ASSERT(label0 == children.front());
            TG_ASSERT(label1 == children.back());
            app->tick();

            layout->moveToFront(label0);
            app->tick();
            children = layout->getChildren();
            TG_ASSERT(spacer == children.front());
            TG_ASSERT(label0 == children.back());

            layout->moveToBack(label0);
            app->tick();
            children = layout->getChildren();
            TG_ASSERT(label0 == children.front());
            TG_ASSERT(label1 == children.back());

            switch (orientation)
            {
            case Orientation::Horizontal:
                label0->setHStretch(Stretch::Expanding);
                label0->setHStretch(Stretch::Expanding);
                label0->setStretch(Stretch::Fixed, Stretch::Fixed);
                label0->setStretch(Stretch::Fixed, Stretch::Fixed);
                label0->setStretch(Stretch::Expanding);
                TG_ASSERT(Stretch::Expanding == label0->getHStretch());
                app->tick();
                label0->setHAlign(HAlign::Right);
                label0->setHAlign(HAlign::Right);
                label0->setAlign(HAlign::Center, VAlign::Center);
                label0->setAlign(HAlign::Center, VAlign::Center);
                TG_ASSERT(HAlign::Center == label0->getHAlign());
                app->tick();
                label0->setHAlign(HAlign::Left);
                label1->setHAlign(HAlign::Right);
                break;
            case Orientation::Vertical:
                label0->setVStretch(Stretch::Expanding);
                label0->setVStretch(Stretch::Expanding);
                label0->setStretch(Stretch::Fixed, Stretch::Fixed);
                label0->setStretch(Stretch::Fixed, Stretch::Fixed);
                label0->setStretch(Stretch::Expanding);
                TG_ASSERT(Stretch::Expanding == label0->getVStretch());
                app->tick();
                label0->setVAlign(VAlign::Bottom);
                label0->setVAlign(VAlign::Bottom);
                label0->setAlign(HAlign::Center, VAlign::Center);
                label0->setAlign(HAlign::Center, VAlign::Center);
                TG_ASSERT(VAlign::Center == label0->getVAlign());
                app->tick();
                label0->setVAlign(VAlign::Top);
                label1->setVAlign(VAlign::Bottom);
                break;
            default: break;
            }
            app->tick();

            label0->hide();
            label0->hide();
            app->tick();
            TG_ASSERT(!label0->isVisible());
            TG_ASSERT(!label0->isVisible(false));
            TG_ASSERT(label0->isClipped());
            label0->show();
            app->tick();

            label0->setParent(nullptr);
            app->tick();
            children = layout->getChildren();
            TG_ASSERT(2 == children.size());
            TG_ASSERT(spacer == children.front());
            label0->setParent(layout);
            app->tick();
            children = layout->getChildren();
            TG_ASSERT(3 == children.size());
            TG_ASSERT(spacer == children.front());
            TG_ASSERT(label0 == children.back());
            label0->setParent(nullptr);
            app->tick();

            label1->setParent(nullptr);
            spacer->setParent(nullptr);
            app->tick();
            children = layout->getChildren();
            TG_ASSERT(children.empty());
        }
    }
}

