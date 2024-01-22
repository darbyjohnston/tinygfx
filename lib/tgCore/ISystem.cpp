// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/ISystem.h>

namespace tg
{
    namespace core
    {
        ISystem::ISystem(
            const std::shared_ptr<Context>& context,
            const std::string& name) :
            _context(context),
            _name(name)
        {}

        ISystem::~ISystem()
        {}

        void ISystem::tick()
        {}

        std::chrono::milliseconds ISystem::getTickTime() const
        {
            return std::chrono::milliseconds(0);
        }
    }
}
