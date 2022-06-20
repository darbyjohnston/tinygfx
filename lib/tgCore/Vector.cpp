// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Vector.h>

namespace tg
{
    namespace math
    {
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
