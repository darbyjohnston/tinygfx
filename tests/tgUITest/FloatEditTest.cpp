// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/FloatEditTest.h>

#include <tgUI/FloatEdit.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        FloatEditTest::FloatEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::FloatEditTest")
        {}

        FloatEditTest::~FloatEditTest()
        {}

        std::shared_ptr<FloatEditTest> FloatEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FloatEditTest>(new FloatEditTest(context));
        }

        void FloatEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FloatEditTest");
                _app = App::create(
                    context,
                    argv,
                    "FloatEditTest",
                    "Float edit test.");
                _window = Window::create(context, _app, "FloatEditTest");
                _layout = VerticalLayout::create(context, _window);
                _layout->setMarginRole(SizeRole::MarginLarge);
                _app->addWindow(_window);
                _window->show();
                _app->tick();

                auto edit = FloatEdit::create(context, nullptr, _layout);
                TG_ASSERT(edit->getModel());
                float value = 0.F;
                edit->setCallback([&value](float v) { value = v; });
                edit->setValue(.9F);
                _app->tick();
                TG_ASSERT(.9F == edit->getValue());
                TG_ASSERT(.9F == value);
                edit->setRange(RangeF(0.F, .5F));
                _app->tick();
                TG_ASSERT(RangeF(0.F, .5F) == edit->getRange());
                TG_ASSERT(.5F == value);
                edit->setStep(.2F);
                TG_ASSERT(.2F == edit->getStep());
                edit->setLargeStep(.3F);
                TG_ASSERT(.3F == edit->getLargeStep());
                edit->setPrecision(3);
                TG_ASSERT(3 == edit->getPrecision());
                edit->setPrecision(2);
                edit->setFontRole(FontRole::Label);
                TG_ASSERT(FontRole::Label == edit->getFontRole());
                edit->setFontRole(FontRole::Mono);

                _window->setCursorEnter(true);
                _window->setKey(Key::Tab);
                _window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                _window->setKey(Key::Delete);
                _window->setText("0.1");
                _window->setKey(Key::Enter);
                TG_ASSERT(.1F == value);

                _window->setKey(Key::Up);
                TG_ASSERT(fuzzyCompare(.3F, value));
                _window->setKey(Key::PageUp);
                TG_ASSERT(fuzzyCompare(.5F, value));
                _window->setKey(Key::PageDown);
                TG_ASSERT(fuzzyCompare(.2F, value));
                _window->setKey(Key::Down);
                TG_ASSERT(fuzzyCompare(.0F, value));
            }
        }
    }
}

