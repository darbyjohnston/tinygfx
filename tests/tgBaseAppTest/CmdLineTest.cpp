// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgBaseAppTest/CmdLineTest.h>

#include <tgBaseApp/CmdLine.h>

#include <tgCore/Assert.h>

using namespace tg::core;
using namespace tg::app;

namespace tg
{
    namespace app_test
    {
        CmdLineTest::CmdLineTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::app_test::CmdLineTest")
        {}

        CmdLineTest::~CmdLineTest()
        {}

        std::shared_ptr<CmdLineTest> CmdLineTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<CmdLineTest>(new CmdLineTest(context));
        }
        
        void CmdLineTest::run()
        {
            bool flag = false;
            bool boolOption = false;
            int intOption = 0;
            int intArg = 0;
            std::string stringArg;

            std::vector<std::string> argv = {
                "-flag",
                "-boolOption", "1",
                "-intOption", "10",
                "100",
                "string" };

            auto flagCmdLineOption = CmdLineFlagOption::create(
                flag,
                { "-flag" },
                "This is a flag option");
            _print(join(flagCmdLineOption->getHelp(), '\n'));
            flagCmdLineOption->parse(argv);
            TG_ASSERT(flag);
            TG_ASSERT(!flagCmdLineOption->getMatchedName().empty());

            auto boolCmdLineOption = CmdLineValueOption<bool>::create(
                boolOption,
                { "-boolOption" },
                "This is a boolean option",
                "0",
                join({ "0", "1" }, ", "));
            _print(join(boolCmdLineOption->getHelp(), '\n'));
            boolCmdLineOption->parse(argv);
            TG_ASSERT(boolOption);

            auto intCmdLineOption = CmdLineValueOption<int>::create(
                intOption,
                { "-intOption" },
                "This is an integer option",
                "0");
            _print(join(intCmdLineOption->getHelp(), '\n'));
            intCmdLineOption->parse(argv);
            TG_ASSERT(10 == intOption);

            auto intCmdLineArg = CmdLineValueArg<int>::create(
                intArg,
                "int",
                "This is an integer argument");
            TG_ASSERT(!intCmdLineArg->getName().empty());
            TG_ASSERT(!intCmdLineArg->isOptional());
            _print(intCmdLineArg->getHelp());
            intCmdLineArg->parse(argv);
            TG_ASSERT(100 == intArg);

            auto stringCmdLineArg = CmdLineValueArg<std::string>::create(
                stringArg,
                "string",
                "This is a string argument");
            TG_ASSERT(!stringCmdLineArg->getName().empty());
            TG_ASSERT(!stringCmdLineArg->isOptional());
            _print(stringCmdLineArg->getHelp());
            stringCmdLineArg->parse(argv);
            TG_ASSERT("string" == stringArg);

            try
            {
                intCmdLineArg->parse(argv);
                TG_ASSERT(false);
            }
            catch (const std::exception&)
            {}
            try
            {
                stringCmdLineArg->parse(argv);
                TG_ASSERT(false);
            }
            catch (const std::exception&)
            {}
            argv.push_back("-intOption");
            try
            {
                intCmdLineOption->parse(argv);
                TG_ASSERT(false);
            }
            catch (const std::exception&)
            {}
        }
    }
}

