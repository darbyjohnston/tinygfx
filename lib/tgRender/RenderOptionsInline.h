// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

namespace tg
{
    namespace render
    {
        inline bool RenderOptions::operator == (const RenderOptions& other) const
        {
            return
                clear == other.clear &&
                clearColor == other.clearColor &&
                textureCacheByteCount == other.textureCacheByteCount;
        }

        inline bool RenderOptions::operator != (const RenderOptions& other) const
        {
            return !(*this == other);
        }

        inline bool LineOptions::operator == (const LineOptions& other) const
        {
            return
                width == other.width;
        }

        inline bool LineOptions::operator != (const LineOptions& other) const
        {
            return !(*this == other);
        }
    }
}
