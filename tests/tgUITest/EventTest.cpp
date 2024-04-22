// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/EventTest.h>

#include <tgUI/Event.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        EventTest::EventTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::EventTest")
        {}

        EventTest::~EventTest()
        {}

        std::shared_ptr<EventTest> EventTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<EventTest>(new EventTest(context));
        }
                
        void EventTest::run()
        {
            _enums();
        }
        
        void EventTest::_enums()
        {
            TINYGFX_TEST_ENUM(Key);
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::None)));
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::Shift)));
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::Control)));
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::Alt)));
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::Super)));
            _print(getShortcutLabel(Key::O, static_cast<int>(KeyModifier::Control)));
        }
    }
}

