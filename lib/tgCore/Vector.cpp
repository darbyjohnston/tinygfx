// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Vector.h>

#include <cmath>

namespace tg
{
    namespace math
    {
        float length(const Vector2i& value)
        {
            return std::sqrtf(value.x * value.x + value.y * value.y);
        }

        float length(const Vector2f& value)
        {
            return std::sqrtf(value.x * value.x + value.y * value.y);
        }

        float distance(const Vector2i& a, const Vector2i& b)
        {
            return length(b - a);
        }

        float distance(const Vector2f& a, const Vector2f& b)
        {
            return length(b - a);
        }

        std::ostream& operator << (std::ostream& os, const Vector2i& value)
        {
            os << value.x << "," << value.y;
            return os;
        }

        std::ostream& operator << (std::ostream& os, const Vector2f& value)
        {
            os << value.x << "," << value.y;
            return os;
        }

        std::ostream& operator << (std::ostream& os, const Vector3f& value)
        {
            os << value.x << "," << value.y << "," << value.z;
            return os;
        }

        std::ostream& operator << (std::ostream& os, const Vector4f& value)
        {
            os << value.x << "," << value.y << "," << value.z << "," << value.w;
            return os;
        }
    }
}
