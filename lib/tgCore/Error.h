// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <stdexcept>

namespace tg
{
    namespace core
    {
#if defined(_WINDOWS)
        //! Get an error string from a Windows system call.
        std::string getLastError();
#endif // _WINDOWS

        //! Parse error.
        class ParseError : public std::invalid_argument
        {
        public:
            ParseError();
        };
    }
}
