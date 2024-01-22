// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/Math.h>

#include <cmath>

namespace tg
{
    namespace core
    {
        size_t digits(int value)
        {
            size_t out = 0;
            if (value != 0)
            {
                while (value)
                {
                    value /= 10;
                    ++out;
                }
            }
            else
            {
                out = 1;
            }
            return out;
        }

        bool fuzzyCompare(double a, double b, double e)
        {
            return fabs(a - b) < e;
        }

        bool fuzzyCompare(float a, float b, float e)
        {
            return fabsf(a - b) < e;
        }
    }
}

