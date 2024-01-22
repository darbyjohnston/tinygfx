// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/File.h>

#include <cstring>
#include <vector>

#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#if defined(__APPLE__)
#define _STAT struct ::stat
#define _STAT_FNC    ::stat
#else // __APPLE__
#define _STAT struct ::stat64
#define _STAT_FNC    ::stat64
#endif // __APPLE__

namespace tg
{
    namespace core
    {
        bool fileExists(const std::string& fileName)
        {
            _STAT info;
            memset(&info, 0, sizeof(_STAT));
            return 0 == _STAT_FNC(fileName.c_str(), &info);
        }
        
        bool rm(const std::string& fileName)
        {
            return 0 == ::remove(fileName.c_str());
        }

        bool mkdir(const std::string& fileName)
        {
            return 0 == ::mkdir(fileName.c_str(), S_IRWXU | S_IRWXG);
        }

        bool rmdir(const std::string& fileName)
        {
            return 0 == ::rmdir(fileName.c_str());
        }

        std::string getCWD()
        {
            char buf[PATH_MAX];
            if (!getcwd(buf, PATH_MAX))
            {
                buf[0] = 0;
            }
            std::string out(buf);
            const size_t size = out.size();
            if (size > 0 && out[size - 1] != '/')
            {
                out.push_back('/');
            }
            return out;
        }
            
        std::string getTempDir()
        {
            std::string out;
            char* env = nullptr;
            if ((env = getenv("TEMP")))
            {
                out = env;
            }
            else if ((env = getenv("TMP")))
            {
                out = env;
            }
            else if ((env = getenv("TMPDIR")))
            {
                out = env;
            }
            else
            {
                for (const auto& path : { "/tmp", "/var/tmp", "/usr/tmp" })
                {
                    if (fileExists(path))
                    {
                        out = path;
                        break;
                    }
                }
            }
            return out;
        }

        std::string createTempDir()
        {
            std::string out;
            const std::string path = getTempDir() + "/XXXXXX";
            const size_t size = path.size();
            std::vector<char> buf(size + 1);
            std::memcpy(buf.data(), path.c_str(), size);
            buf[size] = 0;
            if (char* s = mkdtemp(buf.data()))
            {
                out = s;
            }
            return out;
        }
    }
}
