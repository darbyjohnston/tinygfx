// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/Time.h>

#include <thread>

namespace tg
{
    namespace core
	{
        void sleep(const std::chrono::microseconds& value)
		{
            std::this_thread::sleep_for(value);
        }
    }
}
