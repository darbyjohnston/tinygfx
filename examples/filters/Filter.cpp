// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Filter.h"

namespace tg
{
    std::shared_ptr<image::Image> testGrid()
    {
        std::shared_ptr<image::Image> out;
        const image::Info info(image::Info(1280, 720, image::Format::RGBA, image::Type::Float));
        out = image::Image::create(info);
        out->zero();
        const math::Vector2i spacing(20, 20);
        float* p = reinterpret_cast<float*>(out->getData());
        for (int y = 0; y < info.size.y; ++y)
        {
            for (int x = 0; x < info.size.x; ++x)
            {
                if (0 == x % spacing.x || 0 == y % spacing.y)
                {
                    p[0] = p[1] = p[2] = 1.F;
                    p[3] = 1.F;
                }
                p += 4;
            }
        }
        return out;
    }
}
