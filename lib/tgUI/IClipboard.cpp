// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IClipboard.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        void IClipboard::_init(const std::shared_ptr<Context>& context)
        {
            _context = context;
        }

        IClipboard::IClipboard()
        {}

        IClipboard::~IClipboard()
        {}
    }
}
