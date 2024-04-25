// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/LayoutUtilTest.h>

#include <tgUI/LayoutUtil.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        LayoutUtilTest::LayoutUtilTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::LayoutUtilTest")
        {}

        LayoutUtilTest::~LayoutUtilTest()
        {}

        std::shared_ptr<LayoutUtilTest> LayoutUtilTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<LayoutUtilTest>(new LayoutUtilTest(context));
        }
                
        void LayoutUtilTest::run()
        {
            _print(Format("Format {0}: {1}").arg(0).arg(format(0)));
            _print(Format("Format {0}: {1}").arg(10).arg(format(10)));
            _print(Format("Format {0}: {1}").arg(100).arg(format(100)));

            _print(Format("Format {0}: {1}").arg(0.01).arg(format(0.01, 2)));
            _print(Format("Format {0}: {1}").arg(10.01).arg(format(10.01, 2)));
            _print(Format("Format {0}: {1}").arg(100.01).arg(format(100.01, 2)));
        }
    }
}

