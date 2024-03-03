// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Init.h>

#include <tgUI/FileBrowser.h>
#include <tgUI/MessageDialog.h>

#include <tgCore/Context.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        void init(const std::shared_ptr<Context>& context)
        {
            if (!context->getSystem<FileBrowserSystem>())
            {
                context->addSystem(FileBrowserSystem::create(context));
            }
            if (!context->getSystem<MessageDialogSystem>())
            {
                context->addSystem(MessageDialogSystem::create(context));
            }
        }
    }
}
