// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgGL/Shader.h>

#include <tgCore/Mesh.h>
#include <tgCore/Range.h>
#include <tgCore/Util.h>
#include <tgCore/Vector.h>

#include <array>
#include <memory>
#include <vector>

namespace tg
{
    //! Line.
    struct Line
    {
        std::array<math::Vector2f, 2> p;
        float width;
        math::Vector4f color;
    };

    //! Polyline joints.
    enum class PolylineJoint
    {
        Bevel,
        Round,
        Miter
    };

    //! Polyline end caps.
    enum class PolyLineCap
    {
        Flush,
        Round,
        Square
    };

    //! Polyline.
    struct Polyline
    {
        std::vector<math::Vector2f> p;
        float width;
        PolylineJoint joint = PolylineJoint::Bevel;
        PolyLineCap cap = PolyLineCap::Flush;
        math::Vector4f color;
    };

    //! Bezier.
    struct Bezier
    {
        std::array<math::Vector2f, 4> p;
        float width;
        math::Vector4f color;
    };

    //! Disc.
    struct Disc
    {
        math::Vector2f p;
        float radius;
        size_t resolution = 16;
        math::Vector4f color;
    };

    //! Renderer.
    class Render :
        public NonCopyable,
        std::enable_shared_from_this<Render>
    {
        void _init();

        Render();

    public:
        static std::shared_ptr<Render> create();

        void begin(const math::Vector2i& size);
        void end();

        void draw(const Line&);
        void draw(const Polyline&);
        void draw(const Bezier&);
        void draw(const Disc&);

    private:
        std::shared_ptr<gl::Shader> _shader;

        math::Vector2i _size;

        struct Mesh
        {
            geom::Mesh2D m;
            math::Vector4f color;
        };
        std::vector<Mesh> _meshes;
    };
}
