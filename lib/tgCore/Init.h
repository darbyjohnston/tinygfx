// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <memory>

namespace tg
{
    //! Core functionality
    namespace core
    {
        class Context;

        //! Initialize the library.
        void init(const std::shared_ptr<Context>&);
    }
}

