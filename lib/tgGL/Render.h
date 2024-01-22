// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgRender/IRender.h>

namespace tg
{
    namespace gl
    {
        //! OpenGL rendering.
        class Render : public render::IRender
        {
            TG_NON_COPYABLE(Render);

        protected:
            void _init(const std::shared_ptr<core::Context>&);

            Render();

        public:
            virtual ~Render();

            static std::shared_ptr<Render> create(
                const std::shared_ptr<core::Context>&);

            void begin(
                const core::Size2I&,
                const render::Options& = render::Options()) override;
            void end() override;
            core::Size2I getRenderSize() const override;
            void setRenderSize(const core::Size2I&) override;
            core::Box2I getViewport() const override;
            void setViewport(const core::Box2I&) override;
            void clearViewport(const core::Color4F&) override;
            bool getClipRectEnabled() const override;
            void setClipRectEnabled(bool) override;
            core::Box2I getClipRect() const override;
            void setClipRect(const core::Box2I&) override;
            core::M44F getTransform() const override;
            void setTransform(const core::M44F&) override;
            void drawRect(
                const core::Box2F&,
                const core::Color4F&) override;
            void drawLine(
                const core::V2F&,
                const core::V2F&,
                const core::Color4F&,
                const render::LineOptions& = render::LineOptions()) override;
            void drawMesh(
                const core::TriMesh2F&,
                const core::Color4F& = core::Color4F(1.F, 1.F, 1.F, 1.F),
                const core::V2F& pos = core::V2F()) override;
            void drawColorMesh(
                const core::TriMesh2F&,
                const core::Color4F& = core::Color4F(1.F, 1.F, 1.F, 1.F),
                const core::V2F& pos = core::V2F()) override;

        protected:
            TG_PRIVATE();
        };
    }
}

