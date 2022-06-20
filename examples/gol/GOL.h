// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include "Buffer.h"

#include <array>
#include <chrono>
#include <memory>

namespace tg
{
    //! Game of life cell.
    struct Cell
    {
        Cell()
        {}

        Cell(bool alive, const math::Vector3f& color) :
            alive(alive),
            color(color)
        {}

        bool alive = false;
        math::Vector3f color;
    };

    //! Game of life logic.
    class GOL
    {
        GOL();

    public:
        static std::shared_ptr<GOL> create();

        const math::Vector2i& getSize() const;

        void resize(const math::Vector2i&);

        const Buffer<Cell>& getBuffer() const;

        void tick();

    private:
        std::pair<int, math::Vector3f> _getNeighbors(const math::Vector2i&) const;

        DoubleBuffer<Cell> _buffer;
        size_t _tick = 0;
        std::chrono::steady_clock::time_point _timer;
    };
}
