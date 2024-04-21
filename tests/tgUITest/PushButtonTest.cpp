// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/PushButtonTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/PushButton.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        PushButtonTest::PushButtonTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::PushButtonTest")
        {}

        PushButtonTest::~PushButtonTest()
        {}

        std::shared_ptr<PushButtonTest> PushButtonTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<PushButtonTest>(new PushButtonTest(context));
        }
                
        void PushButtonTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("PushButtonTest");
                auto app = App::create(context, argv, "PushButtonTest", "Push button test.");
                auto window = Window::create(context, "PushButtonTest", Size2I(1280, 960));

                auto layout = VerticalLayout::create(context, window);
                auto pushButton0 = PushButton::create(context, "Push Button 0", layout);
                auto pushButton1 = PushButton::create(context, "Push Button 1", layout);

                std::string text = "Playback";
                pushButton1->setText(text);
                pushButton1->setText(text);
                TG_ASSERT(text == pushButton1->getText());

                FontRole fontRole = FontRole::Mono;
                pushButton1->setFontRole(fontRole);
                pushButton1->setFontRole(fontRole);
                TG_ASSERT(fontRole == pushButton1->getFontRole());

                pushButton1->setCheckable(true);
                pushButton1->setCheckable(true);
                TG_ASSERT(pushButton1->isCheckable());
                pushButton1->setChecked(true);
                pushButton1->setChecked(true);
                TG_ASSERT(pushButton1->isChecked());
                pushButton1->setChecked(false);

                std::string icon = "PlaybackForward";
                pushButton1->setIcon(icon);
                pushButton1->setIcon(icon);
                TG_ASSERT(icon == pushButton1->getIcon());
                icon = "PlaybackStop";
                pushButton1->setCheckedIcon(icon);
                pushButton1->setCheckedIcon(icon);
                TG_ASSERT(icon == pushButton1->getCheckedIcon());

                ColorRole colorRole = ColorRole::Blue;
                pushButton1->setButtonRole(colorRole);
                pushButton1->setButtonRole(colorRole);
                TG_ASSERT(colorRole == pushButton1->getButtonRole());
                colorRole = ColorRole::Red;
                pushButton1->setCheckedRole(colorRole);
                pushButton1->setCheckedRole(colorRole);
                TG_ASSERT(colorRole == pushButton1->getCheckedRole());

                bool hovered = false;
                pushButton1->setHoveredCallback([&hovered](bool value) { hovered = value; });
                bool pressed = false;
                pushButton1->setPressedCallback([&pressed] { pressed = true; });
                int clicks = 0;
                pushButton1->setClickedCallback([&clicks] { ++clicks; });
                bool checked = false;
                pushButton1->setCheckedCallback([&checked](bool value) { checked = value; });

                app->addWindow(window);
                window->show();
                app->run();

                pushButton1->mouseEnterEvent();
                TG_ASSERT(hovered);
                MouseMoveEvent mouseMoveEvent;
                mouseMoveEvent.pos = center(pushButton1->getGeometry());
                pushButton1->mouseMoveEvent(mouseMoveEvent);
                MouseClickEvent mouseClickEvent;
                mouseClickEvent.pos = mouseMoveEvent.pos;
                pushButton1->mousePressEvent(mouseClickEvent);
                TG_ASSERT(pressed);
                pushButton1->mouseReleaseEvent(mouseClickEvent);
                TG_ASSERT(1 == clicks);
                TG_ASSERT(checked);
                TG_ASSERT(pushButton1->hasKeyFocus());
                pushButton1->mouseLeaveEvent();
                TG_ASSERT(!hovered);
                app->run();

                KeyEvent keyEvent;
                keyEvent.key = Key::Enter;
                pushButton1->keyPressEvent(keyEvent);
                pushButton1->keyReleaseEvent(keyEvent);
                TG_ASSERT(2 == clicks);
                TG_ASSERT(!checked);
                app->run();

                keyEvent = KeyEvent();
                keyEvent.key = Key::Escape;
                pushButton1->keyPressEvent(keyEvent);
                pushButton1->keyReleaseEvent(keyEvent);
                TG_ASSERT(!pushButton1->hasKeyFocus());
                app->run();
            }
        }
    }
}

