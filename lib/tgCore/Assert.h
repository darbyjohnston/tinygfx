// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

//! Project namespace
namespace tg
{
    namespace core
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
        tg::core::_assert(__FILE__, __LINE__)
#else // TG_ASSERT
#define TG_ASSERT(value)
#endif // TG_ASSERT

