// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/WidgetOptions.h>

#include <tgCore/Box.h>

namespace tg
{
    namespace ui
    {
        //! \name Layouts
        ///@{
        
        //! Align within the given box.
        core::Box2I align(
            const core::Box2I&  box,
            const core::Size2I& sizeHint,
            Stretch             hStretch,
            Stretch             vStretch,
            HAlign              hAlign,
            VAlign              vAlign);

        //! Get a format string for the given number.
        std::string format(int);

        //! Get a format string for the given number.
        std::string format(float, int precision);
        
        ///@}
    }
}
