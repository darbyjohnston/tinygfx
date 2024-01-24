// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Color.h>
#include <tgCore/Memory.h>

namespace tg
{
    namespace render
    {
        //! Render options.
        struct Options
        {
            //! Clear the canvas before rendering.
            bool clear = true;

            //! Clear color.
            core::Color4F clearColor = core::Color4F(0.F, 0.F, 0.F, 0.F);

            //! Texture cache byte count.
            size_t textureCacheByteCount = core::gigabyte / 4;

            bool operator == (const Options&) const;
            bool operator != (const Options&) const;
        };

        //! Line drawing options.
        struct LineOptions
        {
            float width = 1.F;

            bool operator == (const LineOptions&) const;
            bool operator != (const LineOptions&) const;
        };
    }
}

#include <tgRender/RenderOptionsInline.h>

