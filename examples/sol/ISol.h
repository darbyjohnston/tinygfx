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
    protected:
        ISol(const std::string& name, float duration);

    public:
        virtual ~ISol() = 0;

        virtual void tick(float delta) = 0;

        virtual void render(const math::Vector2i& size) = 0;

    protected:
        std::string _name;
        float _duration = 0.F;
    };
}
