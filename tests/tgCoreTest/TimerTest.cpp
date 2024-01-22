// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/TimerTest.h>

#include <tgCore/Assert.h>

#include <iostream>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        TimerTest::TimerTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::TimerTest")
        {
            _timer = Timer::create(context);
            TG_ASSERT(!_timer->isRepeating());
            
            _repeatTimer = Timer::create(context);
            _repeatTimer->setRepeating(true);
            TG_ASSERT(_repeatTimer->isRepeating());

            const std::chrono::milliseconds timeout(5);
            _timer->start(timeout, [] {});
            TG_ASSERT(_timer->isActive());
            TG_ASSERT(timeout == _timer->getTimeout());
            _timer->stop();
            TG_ASSERT(!_timer->isActive());

            _timer->start(
                timeout,
                [this]
                {
                    _timeout = true;
                });

            _repeatTimer->start(
                timeout,
                [this](
                    const std::chrono::steady_clock::time_point&,
                    const std::chrono::microseconds&)
                {
                    if (_repeatCount > 0)
                    {
                        --_repeatCount;
                    }
                });
        }

        TimerTest::~TimerTest()
        {}

        std::shared_ptr<TimerTest> TimerTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<TimerTest>(new TimerTest(context));
        }
        
        void TimerTest::run()
        {}

        bool TimerTest::doTick() const
        {
            return !_timeout || _repeatCount > 0;
        }
    }
}

