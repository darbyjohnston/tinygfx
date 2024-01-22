// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgRender/IRender.h>

namespace tg
{
    namespace render
    {
        void IRender::_init(const std::shared_ptr<core::Context>& context)
        {
            _context = context;
        }

        IRender::IRender()
        {}

        IRender::~IRender()
        {}
    }
}

