// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/ErrorTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Error.h>

namespace tg
{
    namespace core_tests
    {
        ErrorTest::ErrorTest() :
            ITest("core_tests::ErrorTest")
        {}

        std::shared_ptr<ErrorTest> ErrorTest::create()
        {
            return std::shared_ptr<ErrorTest>(new ErrorTest);
        }

        void ErrorTest::run()
        {
            try
            {
                throw error::ParseError();
            }
            catch (const std::exception& e)
            {
                _print(e.what());
            }
        }
    }
}
