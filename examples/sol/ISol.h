// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Vector.h>

namespace tg
{
    //! Base class for Sol artworks.
    class ISol
    {
    public:
        virtual ~ISol() = 0;

        virtual void tick(float delta) = 0;

        virtual void render(const math::Vector2i& size) = 0;
    };
}
