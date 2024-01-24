// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Image.h>

#include <iostream>
#include <string>
#include <vector>

namespace tg
{
    namespace render
    {
        //! Input video levels.
        enum class InputVideoLevels
        {
            FromFile,
            FullRange,
            LegalRange,

            Count,
            First = FromFile
        };
        TG_ENUM(InputVideoLevels);

        //! Alpha channel blending.
        //!
        //! References:
        //! - https://microsoft.github.io/Win2D/html/PremultipliedAlpha.htm
        enum class AlphaBlend
        {
            None,
            Straight,
            Premultiplied,

            Count,
            First = None
        };
        TG_ENUM(AlphaBlend);

        //! Image filtering.
        enum class ImageFilter
        {
            Nearest,
            Linear,

            Count,
            First = Nearest
        };
        TG_ENUM(ImageFilter);

        //! Image filters.
        struct ImageFilters
        {
            ImageFilter minify  = ImageFilter::Linear;
            ImageFilter magnify = ImageFilter::Linear;

            bool operator == (const ImageFilters&) const;
            bool operator != (const ImageFilters&) const;
        };

        //! Image options.
        struct ImageOptions
        {
            InputVideoLevels videoLevels  = InputVideoLevels::FromFile;
            AlphaBlend       alphaBlend   = AlphaBlend::Straight;
            ImageFilters     imageFilters;
            bool             cache        = true;

            bool operator == (const ImageOptions&) const;
            bool operator != (const ImageOptions&) const;
        };
    }
}

#include <tgRender/ImageOptionsInline.h>
