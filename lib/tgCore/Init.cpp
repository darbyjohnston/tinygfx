// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/Init.h>

#include <tgCore/FontSystem.h>
#include <tgCore/LogSystem.h>
#include <tgCore/Timer.h>

#include <tgCore/Context.h>

namespace tg
{
    namespace core
    {
        void init(const std::shared_ptr<Context>& context)
        {
            if (!context->getSystem<LogSystem>())
            {
                context->addSystem(LogSystem::create(context));
            }
            if (!context->getSystem<FontSystem>())
            {
                context->addSystem(FontSystem::create(context));
            }
            if (!context->getSystem<TimerSystem>())
            {
                context->addSystem(TimerSystem::create(context));
            }
        }
    }
}

