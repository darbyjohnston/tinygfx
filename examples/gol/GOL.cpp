// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "GOL.h"

#include <tgCore/Random.h>
#include <tgCore/Range.h>

namespace tg
{
    namespace
    {
        const math::FloatRange cellThresholdRange(.8F, 1.F);
        const math::FloatRange cellColorRange(.1F, 1.F);
        const math::FloatRange cellColorVariationRange(-.1F, .1F);

        const std::chrono::milliseconds tickTime(0);
    }

    GOL::GOL()
    {}

    std::shared_ptr<GOL> GOL::create()
    {
        return std::shared_ptr<GOL>(new GOL);
    }

    const math::Vector2i& GOL::getSize() const
    {
        return _buffer.getSize();
    }

    void GOL::resize(const math::Vector2i& size)
    {
        DoubleBuffer<Cell> newBuffer(size);
        const math::Vector2i& prevSize = _buffer.getSize();
        for (math::Vector2i pos(0, 0); pos[1] < size[1]; ++pos[1])
        {
            for (pos[0] = 0; pos[0] < size[0]; ++pos[0])
            {
                if (pos[0] < prevSize[0] && pos[1] < prevSize[1])
                {
                    newBuffer.set(_buffer.get(pos), pos);
                }
                else
                {
                    newBuffer.set(
                        cellThresholdRange.contains(math::getRandom()) ?
                        Cell(
                            true,
                            math::Vector3f(
                                math::getRandom(cellColorRange),
                                math::getRandom(cellColorRange),
                                math::getRandom(cellColorRange))) :
                        Cell(),
                        pos);
                }
            }
        }
        _buffer = newBuffer;
        _buffer.swap();
    }

    const Buffer<Cell>& GOL::getBuffer() const
    {
        return _buffer.getBuffer();
    };

    void GOL::tick()
    {
        const auto now = std::chrono::steady_clock::now();
        if (now - _timer > tickTime)
        {
            _timer = now;

            const math::Vector2i& size = _buffer.getSize();
            for (math::Vector2i pos(0, 0); pos[1] < size[1]; ++pos[1])
            {
                for (pos[0] = 0; pos[0] < size[0]; ++pos[0])
                {
                    const auto neighbors = _getNeighbors(pos);
                    Cell c = _buffer.get(pos);
                    if (c.alive)
                    {
                        switch (neighbors.first)
                        {
                        case 2:
                        case 3:
                            break;
                        default:
                            c.alive = false;
                            break;
                        }
                    }
                    else if (3 == neighbors.first)
                    {
                        c.alive = true;
                        c.color = neighbors.second +
                            math::Vector3f(
                                math::getRandom(cellColorVariationRange),
                                math::getRandom(cellColorVariationRange),
                                math::getRandom(cellColorVariationRange));
                    }
                    _buffer.set(c, pos);
                }
            }

            ++_tick;

            _buffer.swap();
        }
    }

    namespace
    {
        const std::array<math::Vector2i, 8> neighbors =
        {
            math::Vector2i(-1, -1),
            math::Vector2i(0, -1),
            math::Vector2i(1, -1),
            math::Vector2i(-1,  0),
            math::Vector2i(1,  0),
            math::Vector2i(-1,  1),
            math::Vector2i(0,  1),
            math::Vector2i(1,  1)
        };
    }

    std::pair<int, math::Vector3f> GOL::_getNeighbors(const math::Vector2i& pos) const
    {
        auto out = std::make_pair(0, math::Vector3f(0.F, 0.F, 0.F));
        const math::Vector2i& size = _buffer.getSize();
        for (const auto& neighbor : neighbors)
        {
            math::Vector2i pos2 = pos + neighbor;
            if (pos2[0] < 0)
            {
                pos2[0] += size[0];
            }
            else if (pos2[0] >= size[0])
            {
                pos2[0] -= size[0];
            }
            if (pos2[1] < 0)
            {
                pos2[1] += size[1];
            }
            else if (pos2[1] >= size[1])
            {
                pos2[1] -= size[1];
            }
            const auto c = _buffer.get(pos2);
            if (c.alive)
            {
                ++out.first;
                out.second += c.color;
            }
        }
        if (out.first > 0)
        {
            out.second /= static_cast<float>(out.first);
        }
        return out;
    }
}
