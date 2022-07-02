// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Error.h>

#include <tgCore/String.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX
#include <windows.h>

namespace tg
{
    namespace error
    {
        std::string getLastError()
        {
            std::string out;
            const DWORD dw = GetLastError();
            if (dw != ERROR_SUCCESS)
            {
                TCHAR buf[string::cBufferSize];
                FormatMessage(
                    FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    dw,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    buf,
                    string::cBufferSize,
                    NULL);
                out = std::string(buf, lstrlen(buf));
                string::removeTrailingNewlines(out);
            }
            return out;
        }
    }
}