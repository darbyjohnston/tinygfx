// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

//! tinygfx
namespace tg
{
    namespace error
    {
        //! Assert (for convenience use the TINYGFX_ASSERT macro).
        void _assert(const char* file, int line);
    }
}

//! Assert macro.
#if defined(TINYGFX_ASSERT)
#undef TINYGFX_ASSERT
#define TINYGFX_ASSERT(value) \
    if (!(value)) \
        tg::error::_assert(__FILE__, __LINE__)
#else
#define TINYGFX_ASSERT(value)
#endif
