// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/ErrorTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Error.h>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        ErrorTest::ErrorTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::ErrorTest")
        {}

        ErrorTest::~ErrorTest()
        {}

        std::shared_ptr<ErrorTest> ErrorTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ErrorTest>(new ErrorTest(context));
        }
        
        void ErrorTest::run()
        {
            try
            {
                throw ParseError();
            }
            catch (const std::exception&)
            {}
        }
    }
}

