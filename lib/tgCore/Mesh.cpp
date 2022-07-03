// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Mesh.h"

namespace tg
{
    namespace geom
    {
        Mesh2D bbox(const math::BBox2f& bbox)
        {
            Mesh2D out;

            out.v.push_back(math::Vector2f(bbox.min.x, bbox.min.y));
            out.v.push_back(math::Vector2f(bbox.max.x, bbox.min.y));
            out.v.push_back(math::Vector2f(bbox.max.x, bbox.max.y));
            out.v.push_back(math::Vector2f(bbox.min.x, bbox.max.y));
            out.t.push_back(math::Vector2f(0.F, 1.F));
            out.t.push_back(math::Vector2f(1.F, 1.F));
            out.t.push_back(math::Vector2f(1.F, 0.F));
            out.t.push_back(math::Vector2f(0.F, 0.F));

            Mesh2D::Triangle triangle;
            triangle.v[0] = 1;
            triangle.v[1] = 2;
            triangle.v[2] = 3;
            triangle.t[0] = 1;
            triangle.t[1] = 2;
            triangle.t[2] = 3;
            out.triangles.push_back(triangle);
            triangle.v[0] = 3;
            triangle.v[1] = 4;
            triangle.v[2] = 1;
            triangle.t[0] = 3;
            triangle.t[1] = 4;
            triangle.t[2] = 1;
            out.triangles.push_back(triangle);

            return out;
        }

        Mesh3D bbox(const math::BBox3f& bbox)
        {
            Mesh3D out;

            out.v.push_back(math::Vector3f(bbox.min.x, bbox.min.y, bbox.min.z));
            out.v.push_back(math::Vector3f(bbox.max.x, bbox.min.y, bbox.min.z));
            out.v.push_back(math::Vector3f(bbox.max.x, bbox.max.y, bbox.min.z));
            out.v.push_back(math::Vector3f(bbox.min.x, bbox.max.y, bbox.min.z));
            out.v.push_back(math::Vector3f(bbox.min.x, bbox.min.y, bbox.max.z));
            out.v.push_back(math::Vector3f(bbox.max.x, bbox.min.y, bbox.max.z));
            out.v.push_back(math::Vector3f(bbox.max.x, bbox.max.y, bbox.max.z));
            out.v.push_back(math::Vector3f(bbox.min.x, bbox.max.y, bbox.max.z));
            out.t.push_back(math::Vector2f(0.F, 1.F));
            out.t.push_back(math::Vector2f(1.F, 1.F));
            out.t.push_back(math::Vector2f(1.F, 0.F));
            out.t.push_back(math::Vector2f(0.F, 0.F));

            Mesh3D::Triangle triangle;
            triangle.v[0] = 1;
            triangle.v[1] = 2;
            triangle.v[2] = 3;
            triangle.t[0] = 1;
            triangle.t[1] = 2;
            triangle.t[2] = 3;
            out.triangles.push_back(triangle);
            triangle.v[0] = 3;
            triangle.v[1] = 4;
            triangle.v[2] = 1;
            triangle.t[0] = 3;
            triangle.t[1] = 4;
            triangle.t[2] = 1;
            out.triangles.push_back(triangle);

            triangle.v[0] = 5;
            triangle.v[1] = 6;
            triangle.v[2] = 7;
            triangle.t[0] = 1;
            triangle.t[1] = 2;
            triangle.t[2] = 3;
            out.triangles.push_back(triangle);
            triangle.v[0] = 7;
            triangle.v[1] = 8;
            triangle.v[2] = 5;
            triangle.t[0] = 3;
            triangle.t[1] = 4;
            triangle.t[2] = 1;
            out.triangles.push_back(triangle);

            return out;
        }
    }
}
