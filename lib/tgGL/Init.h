// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <memory>

namespace tg
{
    namespace core
    {
        class Context;
    }

    //! OpenGL support
    namespace gl
    {
        //! Initialize the library.
        void init(const std::shared_ptr<core::Context>&);

        //! Initialize GLAD.
        void initGLAD();
    }
}

