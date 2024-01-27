// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Init.h>

#include <tgIO/Init.h>

#include <tgCore/Context.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        void init(const std::shared_ptr<Context>& context)
        {
            io::init(context);
        }
    }
}
