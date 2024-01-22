// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/String.h>

#include <algorithm>
#include <codecvt>
#include <locale>

namespace tg
{
    namespace core
    {
        std::vector<std::string> split(
            const std::string& s,
            char delimeter,
            SplitOptions options)
        {
            std::vector<std::string> out;
            bool word = false;
            std::size_t wordStart = 0;
            std::size_t i = 0;
            for (; i < s.size(); ++i)
            {
                if (s[i] != delimeter)
                {
                    if (!word)
                    {
                        word = true;
                        wordStart = i;
                    }
                }
                else
                {
                    if (word)
                    {
                        word = false;
                        out.push_back(s.substr(wordStart, i - wordStart));
                    }
                    if (SplitOptions::KeepEmpty == options &&
                        i > 0 &&
                        s[i - 1] == delimeter)
                    {
                        out.push_back(std::string());
                    }
                }
            }
            if (word)
            {
                out.push_back(s.substr(wordStart, i - wordStart));
            }
            return out;
        }

        std::vector<std::string> split(
            const std::string& s,
            const std::vector<char>& delimeters,
            SplitOptions options)
        {
            std::vector<std::string> out;
            bool word = false;
            std::size_t wordStart = 0;
            std::size_t i = 0;
            for (; i < s.size(); ++i)
            {
                if (std::find(delimeters.begin(), delimeters.end(), s[i]) == delimeters.end())
                {
                    if (!word)
                    {
                        word = true;
                        wordStart = i;
                    }
                }
                else
                {
                    if (word)
                    {
                        word = false;
                        out.push_back(s.substr(wordStart, i - wordStart));
                    }
                    if (SplitOptions::KeepEmpty == options &&
                        i > 0 &&
                        std::find(delimeters.begin(), delimeters.end(), s[i - 1]) != delimeters.end())
                    {
                        out.push_back(std::string());
                    }
                }
            }
            if (word)
            {
                out.push_back(s.substr(wordStart, i - wordStart));
            }
            return out;
        }

        std::string join(const std::vector<std::string>& values, char delimeter)
        {
            std::string out;
            const std::size_t size = values.size();
            for (std::size_t i = 0; i < size; ++i)
            {
                out += values[i];
                if (i < size - 1)
                {
                    out += delimeter;
                }
            }
            return out;
        }

        std::string join(const std::vector<std::string>& values, const std::string& delimeter)
        {
            std::string out;
            const std::size_t size = values.size();
            for (std::size_t i = 0; i < size; ++i)
            {
                out += values[i];
                if (i < size - 1)
                {
                    out += delimeter;
                }
            }
            return out;
        }

        std::string toUpper(const std::string& value)
        {
            std::string out;
            for (auto i : value)
            {
                out.push_back(std::toupper(i));
            }
            return out;
        }

        std::string toLower(const std::string& value)
        {
            std::string out;
            for (auto i : value)
            {
                out.push_back(std::tolower(i));
            }
            return out;
        }

        void removeTrailingNewlines(std::string& value)
        {
            size_t size = value.size();
            while (size && ('\n' == value[size - 1] || '\r' == value[size - 1]))
            {
                value.pop_back();
                size = value.size();
            }
        }

        std::string elide(const std::string& value, size_t max)
        {
            std::string out = value.substr(0, max);
            if (out.size() < value.size())
            {
                out.push_back('.');
                out.push_back('.');
                out.push_back('.');
            }
            return out;
        }

        bool compare(
            const std::string& a,
            const std::string& b,
            Compare compare)
        {
            bool out = false;
            switch (compare)
            {
            case Compare::CaseSensitive:
                out = a == b;
                break;
            case Compare::CaseInsensitive:
                out = toLower(a) == toLower(b);
                break;
            }
            return out;
        }

        bool contains(
            const std::string& input,
            const std::string& substr,
            Compare compare)
        {
            size_t i = std::string::npos;
            switch (compare)
            {
            case Compare::CaseSensitive:
                i = input.find(substr);
                break;
            case Compare::CaseInsensitive:
                i = toLower(input).find(toLower(substr));
                break;
            }
            return i != std::string::npos;
        }

        std::wstring toWide(const std::string& value)
        {
            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
            return converter.from_bytes(value);
        }

        std::string fromWide(const std::wstring& value)
        {
            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
            return converter.to_bytes(value);
        }
    }
}
