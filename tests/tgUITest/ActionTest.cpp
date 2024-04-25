// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/ActionTest.h>

#include <tgUI/Action.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        ActionTest::ActionTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::ActionTest")
        {}

        ActionTest::~ActionTest()
        {}

        std::shared_ptr<ActionTest> ActionTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ActionTest>(new ActionTest(context));
        }
                
        void ActionTest::run()
        {
            {
                const Action a;
                TG_ASSERT(a.text.empty());
            }
            {
                const Action a(
                    "Test",
                    [] {});
                TG_ASSERT("Test" == a.text);
                TG_ASSERT(a.callback);
            }
            {
                const Action a(
                    "Test",
                    "Icon",
                    [] {});
                TG_ASSERT("Test" == a.text);
                TG_ASSERT("Icon" == a.icon);
                TG_ASSERT(a.callback);
            }
            {
                const Action a(
                    "Test",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [] {});
                TG_ASSERT("Test" == a.text);
                TG_ASSERT(Key::T == a.shortcut);
                TG_ASSERT(static_cast<int>(KeyModifier::Control) == a.shortcutModifiers);
                TG_ASSERT(a.callback);
            }
            {
                const Action a(
                    "Test",
                    "Icon",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [] {});
                TG_ASSERT("Test" == a.text);
                TG_ASSERT("Icon" == a.icon);
                TG_ASSERT(Key::T == a.shortcut);
                TG_ASSERT(static_cast<int>(KeyModifier::Control) == a.shortcutModifiers);
                TG_ASSERT(a.callback);
            }
            {
                const Action a(
                    "Test",
                    [](bool) {});
                TG_ASSERT("Test" == a.text);
                TG_ASSERT(a.checkedCallback);
            }
            {
                const Action a(
                    "Test",
                    "Icon",
                    [](bool) {});
                TG_ASSERT("Test" == a.text);
                TG_ASSERT("Icon" == a.icon);
                TG_ASSERT(a.checkedCallback);
            }
            {
                const Action a(
                    "Test",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [](bool) {});
                TG_ASSERT("Test" == a.text);
                TG_ASSERT(Key::T == a.shortcut);
                TG_ASSERT(static_cast<int>(KeyModifier::Control) == a.shortcutModifiers);
                TG_ASSERT(a.checkedCallback);
            }
            {
                const Action a(
                    "Test",
                    "Icon",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [](bool) {});
                TG_ASSERT("Test" == a.text);
                TG_ASSERT("Icon" == a.icon);
                TG_ASSERT(Key::T == a.shortcut);
                TG_ASSERT(static_cast<int>(KeyModifier::Control) == a.shortcutModifiers);
                TG_ASSERT(a.checkedCallback);
            }
        }
    }
}

