// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

#include <tgCore/Timer.h>

namespace tg
{
    namespace core_test
    {
        class TimerTest : public test::ITest
        {
        protected:
            TimerTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~TimerTest();

            static std::shared_ptr<TimerTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
            bool doTick() const override;

        private:
            std::shared_ptr<core::Timer> _timer;
            bool _timeout = false;
            std::shared_ptr<core::Timer> _repeatTimer;
            int _repeatCount = 10;
        };
    }
}

