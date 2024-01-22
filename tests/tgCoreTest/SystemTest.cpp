// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/SystemTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Context.h>
#include <tgCore/ISystem.h>
#include <tgCore/LogSystem.h>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        namespace
        {
            class System1 : public ISystem
            {
            protected:
                System1(const std::shared_ptr<Context>& context) :
                    ISystem(context, "tg::core_test::System1")
                {}

            public:
                virtual ~System1()
                {}

                static std::shared_ptr<System1> create(
                    const std::shared_ptr<Context>& context)
                {
                    return std::shared_ptr<System1>(new System1(context));
                }
            };
            
            class System2 : public ISystem
            {
            protected:
                System2(const std::shared_ptr<Context>& context) :
                    ISystem(context, "tg::core_test::System2")
                {}

            public:
                virtual ~System2()
                {}

                static std::shared_ptr<System2> create(
                    const std::shared_ptr<Context>& context)
                {
                    return std::shared_ptr<System2>(new System2(context));
                }

                std::chrono::milliseconds getTickTime() const override
                {
                    return std::chrono::milliseconds(100);
                }
            };
        }
        
        SystemTest::SystemTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::SystemTest")
        {
            auto system = System1::create(context);
            TG_ASSERT(system->getContext().lock());
            TG_ASSERT(!system->getName().empty());
            context->addSystem(system);
            context->addSystem(System2::create(context));
        }

        SystemTest::~SystemTest()
        {}

        std::shared_ptr<SystemTest> SystemTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<SystemTest>(new SystemTest(context));
        }
        
        void SystemTest::run()
        {
            {
                LogItem a;
                LogItem b;
                TG_ASSERT(a == b);
                b.time = 1.F;
                TG_ASSERT(a != b);
            }
            if (auto context = _context.lock())
            {
                auto logSystem = context->getSystem<LogSystem>();
                logSystem->print(
                    "tg::core_test::SystemTest",
                    "This is a message",
                    LogType::Message);
                logSystem->print(
                    "tg::core_test::SystemTest",
                    "This is a warning!",
                    LogType::Warning);
                logSystem->print(
                    "tg::core_test::SystemTest",
                    "This is an error!",
                    LogType::Error);
            }
        }
    }
}

