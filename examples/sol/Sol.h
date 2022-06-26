// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgGL/Shader.h>

namespace tg
{
    class Sol
    {
    protected:
        Sol(float duration);

    public:
        static std::shared_ptr<Sol> create(float duration);

        void tick(float delta);

        void render(const math::Vector2i& size);

    private:
        float _duration = 0.F;
        float _t = 0.F;
        math::Vector2i _size = math::Vector2i(0, 0);
        std::vector<math::Vector2f> _pts;
        std::vector<std::pair<size_t, size_t> > _lines;
        std::shared_ptr<gl::Shader> _shader;
    };
}
