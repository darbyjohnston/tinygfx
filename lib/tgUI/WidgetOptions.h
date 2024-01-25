// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Util.h>

#include <iostream>
#include <string>
#include <vector>

namespace tg
{
    namespace ui
    {
        //! Orientation.
        enum class Orientation
        {
            Horizontal,
            Vertical,
            
            Count,
            First = Horizontal
        };
        TG_ENUM(Orientation);

        //! Layout stretch.
        enum class Stretch
        {
            Fixed,
            Expanding,
            
            Count,
            First = Fixed
        };
        TG_ENUM(Stretch);

        //! Horizontal alignment.
        enum class HAlign
        {
            Left,
            Center,
            Right,
            
            Count,
            First = Left
        };
        TG_ENUM(HAlign);

        //! Vertical alignment.
        enum class VAlign
        {
            Top,
            Center,
            Bottom,
            
            Count,
            First = Top
        };
        TG_ENUM(VAlign);

        //! Updates.
        enum Update
        {
            None = 0,
            Size = 1,
            Draw = 2
        };
    }
}
