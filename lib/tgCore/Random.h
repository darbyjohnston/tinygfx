// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Range.h>

namespace tg
{
    namespace math
    {
        //! Get a random number between zero and one.
        float getRandom();

        //! Get a random number in the given range.
        float getRandom(const FloatRange&);

        //! Get a random number in the given range.
        int getRandom(const IntRange&);

        //! Seed the random value generator.
        void setRandomSeed(unsigned int);
    }
}
