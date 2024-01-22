// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <string>
#include <vector>

namespace tg
{
    namespace core
    {
        //! Arbitrary C string size.
        constexpr size_t cStringSize = 4096;

        //! \name Splitting and Joining
        ///@{

        //! String split options.
        enum class SplitOptions
        {
            DiscardEmpty,
            KeepEmpty
        };

        //! Split a string.
        std::vector<std::string> split(
            const std::string&,
            char delimeter,
            SplitOptions = SplitOptions::DiscardEmpty);

        //! Split a string.
        std::vector<std::string> split(
            const std::string&,
            const std::vector<char>& delimeters,
            SplitOptions = SplitOptions::DiscardEmpty);

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

        //! Elide a string.
        std::string elide(const std::string&, size_t = 32);

        ///@}

        //! \name Comparison
        ///@{

        enum class Compare
        {
            CaseSensitive,
            CaseInsensitive
        };

        //! Compare strings.
        bool compare(
            const std::string&,
            const std::string&,
            Compare = Compare::CaseSensitive);

        //! Does a string contain the sub string?
        bool contains(
            const std::string&,
            const std::string& substr,
            Compare = Compare::CaseSensitive);

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
