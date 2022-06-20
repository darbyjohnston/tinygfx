// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

//! tinygfx
namespace tg
{
    namespace error
    {
        //! Assert (for convenience use the TG_ASSERT macro).
        void _assert(const char* file, int line);
    }
}

//! Assert macro.
#if defined(TG_ASSERT)
#undef TG_ASSERT
#define TG_ASSERT(value) \
    if (!(value)) \
        tr::error::_assert(__FILE__, __LINE__)
#else
#define TG_ASSERT(value)
#endif
