// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Util.h>

#include <chrono>
#include <utility>

namespace tg
{
    namespace core
    {
        //! Sleep for a given time.
        void sleep(const std::chrono::microseconds&);

        //! Sleep up to the given time.
        void sleep(
            const std::chrono::microseconds&,
            const std::chrono::steady_clock::time_point& t0,
            const std::chrono::steady_clock::time_point& t1);

        //! Convert a floating point rate to a rational.
        std::pair<int, int> toRational(double);
    }
}

