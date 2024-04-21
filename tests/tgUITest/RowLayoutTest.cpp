// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/RowLayoutTest.h>

#include <tgUI/Divider.h>
#include <tgUI/RowLayout.h>
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
                _app = App::create(context, argv, "RowLayoutTest", "Row layout test.");                _window = Window::create(context, "ButtonTest", Size2I(1280, 960));
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
            }
        }

        void RowLayoutTest::_test(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& layout,
            ui::Orientation orientation)
        {
            TG_ASSERT(layout->getParent().lock());
            TG_ASSERT(layout->getParentT<Window>());
            TG_ASSERT(layout->getWindow());

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
                TG_ASSERT(VAlign::Center == spacer->getVAlign());
                break;
            default: break;
            }
            _app->run();

            spacer->hide();
            spacer->hide();
            _app->run();
            TG_ASSERT(!spacer->isVisible());
            TG_ASSERT(!spacer->isVisible(false));
            TG_ASSERT(spacer->isClipped());
            spacer->show();
            _app->run();

            spacer->setParent(nullptr);
            _app->run();
            children = layout->getChildren();
            TG_ASSERT(1 == children.size());
            TG_ASSERT(divider == children.front());
            spacer->setParent(layout);
            _app->run();
            children = layout->getChildren();
            TG_ASSERT(2 == children.size());
            TG_ASSERT(divider == children.front());
            TG_ASSERT(spacer == children.back());
            spacer->setParent(nullptr);
            _app->run();

            divider->setParent(nullptr);
            _app->run();
            children = layout->getChildren();
            TG_ASSERT(children.empty());
        }
    }
}

