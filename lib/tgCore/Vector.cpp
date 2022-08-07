// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Vector.h>

#include <tgCore/Error.h>
#include <tgCore/String.h>

#include <cmath>
#include <sstream>

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

        Vector2f normalize(const Vector2f& value)
        {
            Vector2f out = value;
            const float l = length(value);
            if (l != 0.F)
            {
                out.x /= l;
                out.y /= l;
            }
            return out;
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

        std::istream& operator >> (std::istream& is, Vector2i& value)
        {
            std::string s;
            is >> s;
            auto split = string::split(s, ',');
            if (split.size() != 2)
            {
                throw error::ParseError();
            }
            {
                std::stringstream ss(split[0]);
                ss >> value.x;
            }
            {
                std::stringstream ss(split[1]);
                ss >> value.y;
            }
            return is;
        }

        std::istream& operator >> (std::istream& is, Vector2f& value)
        {
            std::string s;
            is >> s;
            auto split = string::split(s, ',');
            if (split.size() != 2)
            {
                throw error::ParseError();
            }
            {
                std::stringstream ss(split[0]);
                ss >> value.x;
            }
            {
                std::stringstream ss(split[1]);
                ss >> value.y;
            }
            return is;
        }

        std::istream& operator >> (std::istream& is, Vector3f& value)
        {
            std::string s;
            is >> s;
            auto split = string::split(s, ',');
            if (split.size() != 3)
            {
                throw error::ParseError();
            }
            {
                std::stringstream ss(split[0]);
                ss >> value.x;
            }
            {
                std::stringstream ss(split[1]);
                ss >> value.y;
            }
            {
                std::stringstream ss(split[2]);
                ss >> value.z;
            }
            return is;
        }

        std::istream& operator >> (std::istream& is, Vector4f& value)
        {
            std::string s;
            is >> s;
            auto split = string::split(s, ',');
            if (split.size() != 4)
            {
                throw error::ParseError();
            }
            {
                std::stringstream ss(split[0]);
                ss >> value.x;
            }
            {
                std::stringstream ss(split[1]);
                ss >> value.y;
            }
            {
                std::stringstream ss(split[2]);
                ss >> value.z;
            }
            {
                std::stringstream ss(split[3]);
                ss >> value.w;
            }
            return is;
        }
    }
}
