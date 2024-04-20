// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/WidgetOptionsTest.h>

#include <tgUI/WidgetOptions.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        WidgetOptionsTest::WidgetOptionsTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::WidgetOptionsTest")
        {}

        WidgetOptionsTest::~WidgetOptionsTest()
        {}

        std::shared_ptr<WidgetOptionsTest> WidgetOptionsTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<WidgetOptionsTest>(new WidgetOptionsTest(context));
        }
                
        void WidgetOptionsTest::run()
        {
            _enums();
        }
        
        void WidgetOptionsTest::_enums()
        {
            TINYGFX_TEST_ENUM(Orientation);
            TINYGFX_TEST_ENUM(Stretch);
            TINYGFX_TEST_ENUM(HAlign);
            TINYGFX_TEST_ENUM(VAlign);
        }
    }
}

