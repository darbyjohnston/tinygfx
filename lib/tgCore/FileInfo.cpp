// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/FileInfo.h>

#include <fseq.h>

namespace tg
{
    namespace file
    {
        FileInfo::FileInfo()
        {}

        FileInfo::FileInfo(const Path& path) :
            _path(path)
        {
            std::string error;
            _stat(&error);
        }

        std::vector<FileInfo> dirList(const std::string& path, const file::PathOptions& pathOptions)
        {
            std::vector<FileInfo> out;
            FSeqDirOptions dirOptions;
            fseqDirOptionsInit(&dirOptions);
            dirOptions.fileNameOptions.maxNumberDigits = pathOptions.maxNumberDigits;
            FSeqBool error = FSEQ_FALSE;
            auto dirList = fseqDirList(path.c_str(), &dirOptions, &error);
            if (FSEQ_FALSE == error)
            {
                std::string directory = path;
                const size_t size = directory.size();
                if (size > 0 && !('/' == directory[size - 1] || '\\' == directory[size - 1]))
                {
                    directory += '/';
                }
                for (auto entry = dirList; entry; entry = entry->next)
                {
                    out.push_back(FileInfo(Path(
                        directory,
                        entry->fileName.base,
                        entry->fileName.number,
                        entry->framePadding,
                        entry->fileName.extension)));
                }
            }
            fseqDirListDel(dirList);
            return out;
        }
    }
}
