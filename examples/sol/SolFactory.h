// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include "ISol.h"

namespace tg
{
    //! Factory for Sol classes.
    class SolFactory
    {
        SolFactory();

    public:
        static std::shared_ptr<SolFactory> create();

        std::shared_ptr<ISol> createRandom(float duration);
    };
}
