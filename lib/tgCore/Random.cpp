// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Random.h>

#include <random>

namespace tg
{
    namespace math
    {
        namespace
        {
            std::random_device rd;
            std::mt19937 rng(rd());

        } // namespace

        float getRandom()
        {
            std::uniform_int_distribution<uint32_t> uint_dist;
            return uint_dist(rng) / static_cast<float>(uint_dist.max());
        }

        float getRandom(const FloatRange& range)
        {
            return range.getMin() + (range.getMax() - range.getMin()) * getRandom();
        }

        int getRandom(const IntRange& range)
        {
            std::uniform_int_distribution<uint32_t> uint_dist;
            const float r = static_cast<float>(uint_dist(rng)) / static_cast<float>(uint_dist.max());
            return range.getMin() + static_cast<int>(
                static_cast<float>(range.getMax() - range.getMin() + 1) * r);
        }

        void setRandomSeed(unsigned int value)
        {
            rng.seed(value);
        }
    }
}