// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/ComboBoxTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/ComboBox.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        ComboBoxTest::ComboBoxTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::ComboBoxTest")
        {}

        ComboBoxTest::~ComboBoxTest()
        {}

        std::shared_ptr<ComboBoxTest> ComboBoxTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ComboBoxTest>(new ComboBoxTest(context));
        }
                
        void ComboBoxTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ComboBoxTest");
                auto app = App::create(
                    context,
                    argv,
                    "ComboBoxTest",
                    "Combo box test.");
                auto window = Window::create(context, app, "ComboBoxTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget = ComboBox::create(context, {}, layout);
                std::vector<ComboBoxItem> items =
                {
                    ComboBoxItem("Stop", "PlaybackStop"),
                    ComboBoxItem("Forward", "PlaybackForward"),
                    ComboBoxItem("Reverse", "PlaybackReverse")
                };
                TG_ASSERT(items[0] != ComboBoxItem());
                widget->setItems(items);
                widget->setItems(items);
                TG_ASSERT(items == widget->getItems());
                TG_ASSERT(0 == widget->getCurrentIndex());
                widget->setCurrentIndex(1);
                widget->setCurrentIndex(1);
                TG_ASSERT(1 == widget->getCurrentIndex());
                int index = -1;
                widget->setIndexCallback(
                    [&index](int value)
                    {
                        index = value;
                    });
                ComboBoxItem item;
                widget->setItemCallback(
                    [&item](const ComboBoxItem& value)
                    {
                        item = value;
                    });
                widget->setFontRole(FontRole::Mono);
                widget->setFontRole(FontRole::Mono);
                TG_ASSERT(FontRole::Mono == widget->getFontRole());
                widget->setFontRole(FontRole::Label);

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                window->setKey(Key::Enter);
                TG_ASSERT(0 == index);
                TG_ASSERT(items[0] == item);

                Box2I g = widget->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0);
                window->setKey(Key::Escape);
                window->setKey(Key::Escape);
                window->setCursorPos(V2I(0, 0));

                window->setKey(Key::Down);
                TG_ASSERT(1 == index);
                window->setKey(Key::Up);
                TG_ASSERT(0 == index);
                window->setKey(Key::Escape);
                TG_ASSERT(!widget->hasKeyFocus());

                app->setDisplayScale(2.F);
                app->tick(1000);
                app->setDisplayScale(1.F);
                app->tick(1000);
            }
        }
    }
}

