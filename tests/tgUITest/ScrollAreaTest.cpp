// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/ScrollAreaTest.h>

#include <tgUI/ScrollArea.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        ScrollAreaTest::ScrollAreaTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::ScrollAreaTest")
        {}

        ScrollAreaTest::~ScrollAreaTest()
        {}

        std::shared_ptr<ScrollAreaTest> ScrollAreaTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ScrollAreaTest>(new ScrollAreaTest(context));
        }
                
        void ScrollAreaTest::run()
        {
            _enums();
        }
        
        void ScrollAreaTest::_enums()
        {
            TINYGFX_TEST_ENUM(ScrollType);
        }
    }
}

