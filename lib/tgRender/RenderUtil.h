// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Box.h>
#include <tgCore/Util.h>

#include <memory>

namespace tg
{
    namespace render
    {
        class IRender;
        
        //! Set and restore the render size.
        class RenderSizeState
        {
        public:
            RenderSizeState(const std::shared_ptr<IRender>&);

            ~RenderSizeState();

        private:
            TG_PRIVATE();
        };

        //! Set and restore the viewport.
        class ViewportState
        {
        public:
            ViewportState(const std::shared_ptr<IRender>&);

            ~ViewportState();

        private:
            TG_PRIVATE();
        };

        //! Set and restore whether the clipping rectangle is enabled.
        class ClipRectEnabledState
        {
        public:
            ClipRectEnabledState(const std::shared_ptr<IRender>&);

            ~ClipRectEnabledState();

        private:
            TG_PRIVATE();
        };

        //! Set and restore the clipping rectangle.
        class ClipRectState
        {
        public:
            ClipRectState(const std::shared_ptr<IRender>&);

            ~ClipRectState();

            const core::Box2I& getClipRect() const;

        private:
            TG_PRIVATE();
        };

        //! Set and restore the transform.
        class TransformState
        {
        public:
            TransformState(const std::shared_ptr<IRender>&);

            ~TransformState();

        private:
            TG_PRIVATE();
        };
    }
}
