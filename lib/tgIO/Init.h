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

    //! I/O
    namespace io
    {
        //! Initialize the library.
        void init(const std::shared_ptr<core::Context>&);
    }
}

