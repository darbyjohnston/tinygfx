// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Error.h>

namespace tg
{
    namespace error
    {
        ParseError::ParseError() :
            invalid_argument("Cannot parse value")
        {}
    }
}
