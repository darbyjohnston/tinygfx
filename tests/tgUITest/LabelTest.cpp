// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/LabelTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/IClipboard.h>
#include <tgUI/Label.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        LabelTest::LabelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::LabelTest")
        {}

        LabelTest::~LabelTest()
        {}

        std::shared_ptr<LabelTest> LabelTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<LabelTest>(new LabelTest(context));
        }
                
        void LabelTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("LabelTest");
                auto app = App::create(
                    context,
                    argv,
                    "LabelTest",
                    "Label test.");
                auto window = Window::create(context, app, "LabelTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto label = Label::create(context, layout);
                label->setText("Test");
                label->setText("Test");
                TG_ASSERT("Test" == label->getText());
                label->setTextRole(ColorRole::Red);
                label->setTextRole(ColorRole::Red);
                TG_ASSERT(ColorRole::Red == label->getTextRole());
                label->setMarginRole(SizeRole::Margin);
                label->setMarginRole(SizeRole::Margin);
                TG_ASSERT(SizeRole::Margin == label->getMarginRole());
                label->setFontRole(FontRole::Mono);
                label->setFontRole(FontRole::Mono);
                TG_ASSERT(FontRole::Mono == label->getFontRole());

                label->setEnabled(false);
                app->tick();
                label->setEnabled(true);
                app->tick();

                label->hide();
                app->tick();
                label->show();
                app->tick();
            }
        }
    }
}

