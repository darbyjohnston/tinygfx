// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgRender/ImageOptions.h>
#include <tgRender/RenderOptions.h>

#include <tgCore/FontSystem.h>
#include <tgCore/Matrix.h>
#include <tgCore/Mesh.h>
#include <tgCore/Vector.h>

#include <memory>

namespace tg
{
    namespace core
    {
        class Context;
    }

    //! Rendering
    namespace render
    {
        //! Base class for renderers.
        class IRender : public std::enable_shared_from_this<IRender>
        {
            TG_NON_COPYABLE(IRender);

        protected:
            void _init(const std::shared_ptr<core::Context>&);

            IRender() = default;

        public:
            virtual ~IRender() = 0;

            //! Begin a render.
            virtual void begin(
                const core::Size2I&,
                const RenderOptions& = RenderOptions()) = 0;

            //! Finish a render.
            virtual void end() = 0;

            //! Get the render size.
            virtual core::Size2I getRenderSize() const = 0;

            //! Set the render size.
            virtual void setRenderSize(const core::Size2I&) = 0;

            //! Get the viewport.
            virtual core::Box2I getViewport() const = 0;

            //! Set the viewport.
            virtual void setViewport(const core::Box2I&) = 0;

            //! Clear the viewport.
            virtual void clearViewport(const core::Color4F&) = 0;

            //! Get whether the clipping rectangle is enabled.
            virtual bool getClipRectEnabled() const = 0;

            //! Set whether the clipping rectangle is enabled.
            virtual void setClipRectEnabled(bool) = 0;

            //! Get the clipping rectangle.
            virtual core::Box2I getClipRect() const = 0;

            //! Set the clipping rectangle.
            virtual void setClipRect(const core::Box2I&) = 0;

            //! Get the transformation matrix.
            virtual core::M44F getTransform() const = 0;

            //! Set the transformation matrix.
            virtual void setTransform(const core::M44F&) = 0;

            //! Draw a filled rectangle.
            virtual void drawRect(
                const core::Box2F&,
                const core::Color4F&) = 0;
            
            //! Draw a line.
            virtual void drawLine(
                const core::V2F&,
                const core::V2F&,
                const core::Color4F&,
                const LineOptions& = LineOptions()) = 0;

            //! Draw a triangle mesh.
            virtual void drawMesh(
                const core::TriMesh2F&,
                const core::Color4F& = core::Color4F(1.F, 1.F, 1.F, 1.F),
                const core::V2F& pos = core::V2F()) = 0;

            //! Draw a triangle mesh with vertex color information.
            virtual void drawColorMesh(
                const core::TriMesh2F&,
                const core::Color4F& = core::Color4F(1.F, 1.F, 1.F, 1.F),
                const core::V2F& pos = core::V2F()) = 0;

            //! Draw text.
            virtual void drawText(
                const std::vector<std::shared_ptr<core::Glyph> >&,
                const core::V2F& position,
                const core::Color4F& = core::Color4F(1.F, 1.F, 1.F, 1.F)) = 0;

            //! Draw an image.
            virtual void drawImage(
                const std::shared_ptr<core::Image>&,
                const core::Box2F&,
                const core::Color4F& = core::Color4F(1.F, 1.F, 1.F, 1.F),
                const ImageOptions& = ImageOptions()) = 0;

        protected:
            std::weak_ptr<core::Context> _context;
        };
    }
}

