// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/GroupBoxTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/GroupBox.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        GroupBoxTest::GroupBoxTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::GroupBoxTest")
        {}

        GroupBoxTest::~GroupBoxTest()
        {}

        std::shared_ptr<GroupBoxTest> GroupBoxTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<GroupBoxTest>(new GroupBoxTest(context));
        }
                
        void GroupBoxTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("GroupBoxTest");
                auto app = App::create(
                    context,
                    argv,
                    "GroupBoxTest",
                    "Group box test.");
                auto window = Window::create(context, app, "GroupBoxTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget = GroupBox::create(context, "Test", layout);
                widget->setText("Group");
                widget->setText("Group");
                TG_ASSERT("Group" == widget->getText());
                widget->setFontRole(FontRole::Mono);
                widget->setFontRole(FontRole::Mono);
                TG_ASSERT(FontRole::Mono == widget->getFontRole());
                widget->setFontRole(FontRole::Label);
                app->tick();
            }
        }
    }
}

