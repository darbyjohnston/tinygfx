// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <string>

namespace tg
{
    namespace core
    {
        //! \name Files
        ///@{

        //! Does a file exist?
        bool fileExists(const std::string&);

        //! Remove a file.
        bool rm(const std::string&);

        //! Create a directory.
        bool mkdir(const std::string&);

        //! Remove a directory.
        bool rmdir(const std::string&);

        //! Get the current working directory.
        std::string getCWD();

        //! Get the temporary directory.
        std::string getTempDir();

        //! Create a temporary directory.
        std::string createTempDir();
        
        ///@}
    }
}
