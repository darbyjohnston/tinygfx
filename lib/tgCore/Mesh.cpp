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

            const auto& min = bbox.getMin();
            const auto& max = bbox.getMax();
            out.v.push_back(math::Vector2f(min[0], min[1]));
            out.v.push_back(math::Vector2f(max[0], min[1]));
            out.v.push_back(math::Vector2f(max[0], max[1]));
            out.v.push_back(math::Vector2f(min[0], max[1]));
            out.t.push_back(math::Vector2f(0.F, 0.F));
            out.t.push_back(math::Vector2f(1.F, 0.F));
            out.t.push_back(math::Vector2f(1.F, 1.F));
            out.t.push_back(math::Vector2f(0.F, 1.F));

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

            const auto& min = bbox.getMin();
            const auto& max = bbox.getMax();
            out.v.push_back(math::Vector3f(min[0], min[1], min[2]));
            out.v.push_back(math::Vector3f(max[0], min[1], min[2]));
            out.v.push_back(math::Vector3f(max[0], max[1], min[2]));
            out.v.push_back(math::Vector3f(min[0], max[1], min[2]));
            out.v.push_back(math::Vector3f(min[0], min[1], max[2]));
            out.v.push_back(math::Vector3f(max[0], min[1], max[2]));
            out.v.push_back(math::Vector3f(max[0], max[1], max[2]));
            out.v.push_back(math::Vector3f(min[0], max[1], max[2]));
            out.t.push_back(math::Vector2f(0.F, 0.F));
            out.t.push_back(math::Vector2f(1.F, 0.F));
            out.t.push_back(math::Vector2f(1.F, 1.F));
            out.t.push_back(math::Vector2f(0.F, 1.F));

            Mesh3D::Triangle triangle;
            triangle.v[0] = 1;
            triangle.v[1] = 4;
            triangle.v[2] = 3;
            triangle.t[0] = 2;
            triangle.t[1] = 3;
            triangle.t[2] = 4;
            out.triangles.push_back(triangle);
            triangle.v[0] = 3;
            triangle.v[1] = 2;
            triangle.v[2] = 1;
            triangle.t[0] = 4;
            triangle.t[1] = 1;
            triangle.t[2] = 2;
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

            triangle.v[0] = 2;
            triangle.v[1] = 3;
            triangle.v[2] = 7;
            triangle.t[0] = 2;
            triangle.t[1] = 3;
            triangle.t[2] = 4;
            out.triangles.push_back(triangle);
            triangle.v[0] = 7;
            triangle.v[1] = 6;
            triangle.v[2] = 2;
            triangle.t[0] = 4;
            triangle.t[1] = 1;
            triangle.t[2] = 2;
            out.triangles.push_back(triangle);

            triangle.v[0] = 1;
            triangle.v[1] = 5;
            triangle.v[2] = 8;
            triangle.t[0] = 1;
            triangle.t[1] = 2;
            triangle.t[2] = 3;
            out.triangles.push_back(triangle);
            triangle.v[0] = 8;
            triangle.v[1] = 4;
            triangle.v[2] = 1;
            triangle.t[0] = 3;
            triangle.t[1] = 4;
            triangle.t[2] = 1;
            out.triangles.push_back(triangle);

            triangle.v[0] = 3;
            triangle.v[1] = 4;
            triangle.v[2] = 8;
            triangle.t[0] = 3;
            triangle.t[1] = 4;
            triangle.t[2] = 1;
            out.triangles.push_back(triangle);
            triangle.v[0] = 8;
            triangle.v[1] = 7;
            triangle.v[2] = 3;
            triangle.t[0] = 1;
            triangle.t[1] = 2;
            triangle.t[2] = 3;
            out.triangles.push_back(triangle);

            triangle.v[0] = 1;
            triangle.v[1] = 2;
            triangle.v[2] = 6;
            triangle.t[0] = 1;
            triangle.t[1] = 2;
            triangle.t[2] = 3;
            out.triangles.push_back(triangle);
            triangle.v[0] = 6;
            triangle.v[1] = 5;
            triangle.v[2] = 1;
            triangle.t[0] = 3;
            triangle.t[1] = 4;
            triangle.t[2] = 1;
            out.triangles.push_back(triangle);

            return out;
        }
    }
}
