// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Matrix.h>

namespace tg
{
    namespace math
    {
        std::ostream& operator << (std::ostream& os, const Matrix3x3f& value)
        {
            os << value.e[0] << ",";
            os << value.e[1] << ",";
            os << value.e[2] << "/";
            os << value.e[3] << ",";
            os << value.e[4] << ",";
            os << value.e[5] << "/";
            os << value.e[6] << ",";
            os << value.e[7] << ",";
            os << value.e[8];
            return os;
        }

        std::ostream& operator << (std::ostream& os, const Matrix4x4f& value)
        {
            os << value.e[ 0] << ",";
            os << value.e[ 1] << ",";
            os << value.e[ 2] << ",";
            os << value.e[ 3] << "/";
            os << value.e[ 4] << ",";
            os << value.e[ 5] << ",";
            os << value.e[ 6] << ",";
            os << value.e[ 7] << "/";
            os << value.e[ 8] << ",";
            os << value.e[ 9] << ",";
            os << value.e[10] << ",";
            os << value.e[11] << "/";
            os << value.e[12] << ",";
            os << value.e[13] << ",";
            os << value.e[14] << ",";
            os << value.e[15];
            return os;
        }
    }
}
