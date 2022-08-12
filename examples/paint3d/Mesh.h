// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Vector2.h>
#include <tgCore/Vector3.h>

#include <array>
#include <vector>

namespace tg
{
    //! Mesh.
    class Mesh
    {
    public:
        std::vector<math::Vector3f> v;
        std::vector<math::Vector2f> t;
        std::vector<math::Vector3f> n;

        struct Triangle
        {
            std::array<size_t, 3> v = { 0, 0, 0 };
            std::array<size_t, 3> t = { 0, 0, 0 };
            std::array<size_t, 3> n = { 0, 0, 0 };
        };
        std::vector<Triangle> triangles;
    };
}
