// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/BBox2.h>
#include <tgCore/BBox3.h>
#include <tgCore/Vector2.h>
#include <tgCore/Vector3.h>

#include <array>
#include <vector>

namespace tg
{
    namespace geom
    {
        //! Two-dimensional mesh.
        class Mesh2D
        {
        public:
            std::vector<math::Vector2f> v;
            std::vector<math::Vector2f> t;

            struct Triangle
            {
                std::array<size_t, 3> v = { 0, 0, 0 };
                std::array<size_t, 3> t = { 0, 0, 0 };
            };
            std::vector<Triangle> triangles;
        };

        //! Three-dimensional mesh.
        class Mesh3D
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

        //! Create a two-dimensional bounding box mesh.
        Mesh2D bbox(const math::BBox2f&);

        //! Create a three-dimensional bounding box mesh.
        Mesh3D bbox(const math::BBox3f&);
    }
}
