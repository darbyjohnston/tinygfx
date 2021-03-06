// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <string>
#include <vector>

namespace tg
{
    namespace string
    {
        //! C string buffer size.
        const std::size_t cBufferSize = 4096;

        //! \name Splitting and Joining
        ///@{

        //! Split a string.
        std::vector<std::string> split(const std::string&, char delimeter, bool keepEmpty = false);

        //! Split a string.
        std::vector<std::string> split(const std::string&, const std::vector<char>& delimeters, bool keepEmpty = false);

        //! Join a list of strings.
        std::string join(const std::vector<std::string>&, char delimeter);

        //! Join a list of strings.
        std::string join(const std::vector<std::string>&, const std::string& delimeter);

        ///@}

        //! \name Formatting
        ///@{

        //! Convert to upper case.
        std::string toUpper(const std::string&);

        //! Convert to lower case.
        std::string toLower(const std::string&);

        //! Remove trailing newlines.
        void removeTrailingNewlines(std::string&);

        //! Remove trailing newlines.
        std::string removeTrailingNewlines(const std::string&);

        ///@}

        //! \name Comparison
        ///@{

        //! Compare case insensitive.
        bool compareNoCase(const std::string&, const std::string&);

        ///@}

        //! \name Labels
        ///@{

        //! Get a label.
        std::string getLabel(bool);

        ///@}

        //! \name Conversion
        ///@{

        //! Convert a regular string to a wide string.
        std::wstring toWide(const std::string&);

        //! Convert a wide string to a regular string.
        std::string fromWide(const std::wstring&);

        ///@}
    }
}
