// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/OSTest.h>

#include <tgCore/Assert.h>
#include <tgCore/OS.h>
#include <tgCore/String.h>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        OSTest::OSTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::OSTest")
        {}

        OSTest::~OSTest()
        {}

        std::shared_ptr<OSTest> OSTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<OSTest>(new OSTest(context));
        }
        
        void OSTest::run()
        {
            _env();
        }
        
        void OSTest::_env()
        {
            setEnv("TINYGFX_OSTEST_ENV", "ABC");
            std::string s;
            TG_ASSERT(getEnv("TINYGFX_OSTEST_ENV", s));
            TG_ASSERT("ABC" == s);
            setEnv("TINYGFX_OSTEST_ENV", "123");
            int i = 0;
            TG_ASSERT(getEnv("TINYGFX_OSTEST_ENV", i));
            TG_ASSERT(123 == i);
            setEnv("TINYGFX_OSTEST_ENV", join({ "A", "B", "C" }, envListSeparator));
            std::vector<std::string> l;
            TG_ASSERT(getEnv("TINYGFX_OSTEST_ENV", l));
            TG_ASSERT(std::vector<std::string>({ "A", "B", "C" }) == l);
            delEnv("TINYGFX_OSTEST_ENV");
            TG_ASSERT(!getEnv("TINYGFX_OSTEST_ENV", s));
            TG_ASSERT(!getEnv("TINYGFX_OSTEST_ENV", i));
            TG_ASSERT(!getEnv("TINYGFX_OSTEST_ENV", l));
        }
    }
}

