// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

namespace tg
{
    namespace core
    {
        inline FileMemoryRead::FileMemoryRead(const uint8_t* p, size_t size) :
            p(p),
            size(size)
        {}

        inline bool FileMemoryRead::operator == (const FileMemoryRead& other) const
        {
            return
                p == other.p &&
                size == other.size;
        }

        inline bool FileMemoryRead::operator != (const FileMemoryRead& other) const
        {
            return !(*this == other);
        }
    }
}
