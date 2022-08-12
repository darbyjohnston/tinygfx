// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Vector2.h>

#include <array>
#include <vector>

namespace tg
{
    //! Buffer.
    template<typename T>
    class Buffer
    {
    public:
        Buffer();
        Buffer(const math::Vector2i& size);

        const math::Vector2i& getSize() const;

        const T& get(const math::Vector2i&) const;

        void set(const T&, const math::Vector2i&);

        const std::vector<T>& getData() const;

    private:
        math::Vector2i _size = math::Vector2i(0, 0);
        std::vector<T> _data;
    };

    //! Double buffer.
    template<typename T>
    class DoubleBuffer
    {
    public:
        DoubleBuffer();
        DoubleBuffer(const math::Vector2i& size);

        const math::Vector2i& getSize() const;

        const T& get(const math::Vector2i&) const;

        void set(const T&, const math::Vector2i&);

        void swap();

        const Buffer<T>& getBuffer() const;

    private:
        std::array<Buffer<T>, 2> _buffer;
        size_t _current = 0;
    };
}

#include "BufferInline.h"
