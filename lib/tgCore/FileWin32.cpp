// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/File.h>

#include <tgCore/String.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <combaseapi.h>

#include <cstring>

#define _STAT     struct _stati64
#define _STAT_FNC _wstati64

namespace tg
{
    namespace core
    {
        bool fileExists(const std::string& fileName)
        {
            _STAT info;
            std::memset(&info, 0, sizeof(_STAT));
            return 0 == _STAT_FNC(toWide(fileName).c_str(), &info);
        }

        bool rm(const std::string& fileName)
        {
            return 0 == _wremove(toWide(fileName).c_str());
        }

        bool mkdir(const std::string& fileName)
        {
            return 0 == _wmkdir(toWide(fileName).c_str());
        }

        bool rmdir(const std::string& fileName)
        {
            return 0 == _wrmdir(toWide(fileName).c_str());
        }

        std::string getCWD()
        {
            wchar_t buf[MAX_PATH];
            if (!::_wgetcwd(buf, MAX_PATH))
            {
                buf[0] = 0;
            }
            std::string out = fromWide(buf);
            const size_t size = out.size();
            if (size > 0 && out[size - 1] != '\\')
            {
                out.push_back('\\');
            }
            return out;
        }

        std::string getTempDir()
        {
            std::string out;
            WCHAR buf[MAX_PATH];
            DWORD r = GetTempPathW(MAX_PATH, buf);
            if (r && r < MAX_PATH)
            {
                out = fromWide(buf);
            }
            return out;
        }

        std::string createTempDir()
        {
            std::string out;

            // Get the temporary directory.
            char path[MAX_PATH];
            DWORD r = GetTempPath(MAX_PATH, path);
            if (r)
            {
                out = std::string(path);

                // Create a unique name from a GUID.
                GUID guid;
                CoCreateGuid(&guid);
                const uint8_t* guidP = reinterpret_cast<const uint8_t*>(&guid);
                for (int i = 0; i < 16; ++i)
                {
                    char buf[3] = "";
                    sprintf_s(buf, 3, "%02x", guidP[i]);
                    out += buf;
                }

                // Create a unique directory.
                CreateDirectory(out.c_str(), NULL);
            }

            return out;
        }
    }
}
