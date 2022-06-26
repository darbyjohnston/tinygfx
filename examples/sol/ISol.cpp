// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "ISol.h"

namespace tg
{
    ISol::ISol(const std::string& name, float duration) :
        _name(name),
        _duration(duration)
    {}

    ISol::~ISol()
    {}
}
