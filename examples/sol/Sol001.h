// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include "ISol.h"

#include <tgGL/Shader.h>

#include <memory>

namespace tg
{
    class Sol001 : public ISol
    {
    protected:
        Sol001();

    public:
        static std::shared_ptr<Sol001> create();

        void tick(float delta) override;

        void render(const math::Vector2i& size) override;

    private:
        std::shared_ptr<gl::Shader> _shader;
    };
}
