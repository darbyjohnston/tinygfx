// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/Init.h>

#include <tgCore/FontSystem.h>
#include <tgCore/Format.h>
#include <tgCore/ImageIO.h>
#include <tgCore/LogSystem.h>
#include <tgCore/OS.h>
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
                auto logSystem = LogSystem::create(context);
                context->addSystem(logSystem);
                const auto systemInfo = getSystemInfo();
                logSystem->print(
                    "tg::core::init",
                    Format(
                    "System information:\n"
                    "    Name:  {0}\n"
                    "    Cores: {1}\n"
                    "    RAM:   {2}GB").
                    arg(systemInfo.name).
                    arg(systemInfo.cores).
                    arg(systemInfo.ramGB));
            }
            if (!context->getSystem<FontSystem>())
            {
                context->addSystem(FontSystem::create(context));
            }
            if (!context->getSystem<ImageIO>())
            {
                context->addSystem(ImageIO::create(context));
            }
            if (!context->getSystem<TimerSystem>())
            {
                context->addSystem(TimerSystem::create(context));
            }
        }
    }
}

