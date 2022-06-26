// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "SolFactory.h"

#include "Sol000.h"

namespace tg
{
    SolFactory::SolFactory()
    {}
    
    std::shared_ptr<SolFactory> SolFactory::create()
    {
        return std::shared_ptr<SolFactory>(new SolFactory);
    }

    std::shared_ptr<ISol> SolFactory::createRandom(float duration)
    {
        return Sol000::create(duration);
    }
}
