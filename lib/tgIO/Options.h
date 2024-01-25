// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <map>
#include <string>

namespace tg
{
    namespace io
    {
        //! Image I/O options.
        typedef std::map<std::string, std::string> Options;

        //! Merge image I/O options.
        Options merge(const Options&, const Options&);
    }
}

