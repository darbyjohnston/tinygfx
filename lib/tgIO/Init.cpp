// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgIO/Init.h>

#include <tgIO/ImageIO.h>

#include <tgCore/Context.h>

using namespace tg::core;

namespace tg
{
    namespace io
    {
        void init(const std::shared_ptr<Context>& context)
        {
            if (!context->getSystem<ImageIO>())
            {
                context->addSystem(ImageIO::create(context));
            }
        }
    }
}
