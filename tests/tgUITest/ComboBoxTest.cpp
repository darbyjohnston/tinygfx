// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/ComboBoxTest.h>

#include <tgUI/ComboBox.h>

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
                _app = App::create(context, argv, "ComboBoxTest", "Combo box test.");
                _window = Window::create(context, "ComboBoxTest", Size2I(1280, 960));
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->run();

                auto widget = ComboBox::create(context, {}, _layout);
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

                _window->cursorEnter(true);
                _app->run();
                _window->key(Key::Tab, true, 0);
                _app->run();
                _window->key(Key::Tab, false, 0);
                _app->run();
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                _window->key(Key::Enter, true, 0);
                _app->run();
                _window->key(Key::Enter, false, 0);
                _app->run();
                TG_ASSERT(0 == index);
                TG_ASSERT(items[0] == item);

                Box2I g = widget->getGeometry();
                V2I c = center(g);
                _window->cursorPos(c);
                _app->run();
                _window->button(0, true, 0);
                _app->run();
                _window->button(0, false, 0);
                _window->key(Key::Escape, true, 0);
                _app->run();
                _window->key(Key::Escape, false, 0);
                _app->run();
                _window->key(Key::Escape, true, 0);
                _app->run();
                _window->key(Key::Escape, false, 0);
                _app->run();
                _window->cursorPos(V2I(0, 0));
                _app->run();

                _window->key(Key::Down, true, 0);
                _app->run();
                _window->key(Key::Down, false, 0);
                _app->run();
                TG_ASSERT(1 == index);
                _window->key(Key::Up, true, 0);
                _app->run();
                _window->key(Key::Up, false, 0);
                _app->run();
                TG_ASSERT(0 == index);
                _window->key(Key::Escape, true, 0);
                _app->run();
                _window->key(Key::Escape, false, 0);
                _app->run();
                TG_ASSERT(!widget->hasKeyFocus());

                _app->setDisplayScale(2.F);
                _app->run();
                _app->setDisplayScale(1.F);
                _app->run();
            }
        }
    }
}

