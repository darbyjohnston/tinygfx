// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/PNG.h>

#include <png.h>

namespace tg
{
    namespace core
    {
        namespace png
        {
            //! PNG error.
            struct ErrorStruct
            {
                std::string message;
            };
        }
    }
}

extern "C"
{
    void pngErrorFunc(png_structp, png_const_charp);
    void pngWarningFunc(png_structp, png_const_charp);
}
