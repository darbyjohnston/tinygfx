// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/IntEditTest.h>

#include <tgUI/IntEdit.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        IntEditTest::IntEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::IntEditTest")
        {}

        IntEditTest::~IntEditTest()
        {}

        std::shared_ptr<IntEditTest> IntEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IntEditTest>(new IntEditTest(context));
        }
                
        void IntEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("IntEditTest");
                _app = App::create(context, argv, "IntEditTest", "Integer edit test.");
                _window = Window::create(context, "ButtonTest", Size2I(1280, 960));
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->run();

                auto edit = IntEdit::create(context, nullptr, _layout);
                int value = 0;
                edit->setCallback([&value](int v) { value = v; });

                edit->setValue(11);
                _app->run();
                TG_ASSERT(11 == edit->getValue());
                TG_ASSERT(11 == value);

                edit->setRange(RangeI(0, 10));
                _app->run();
                TG_ASSERT(RangeI(0, 10) == edit->getRange());
                TG_ASSERT(10 == value);
            }
        }
    }
}

