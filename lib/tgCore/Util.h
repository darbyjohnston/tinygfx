// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

//! Convenience macro for making a class non-copyable.
#define TG_NON_COPYABLE(CLASS) \
    CLASS(const CLASS&) = delete; \
    CLASS& operator = (const CLASS&) = delete

//! Convenience macro for private implementations.
//! 
//! Required includes:
//! * memory
#define TG_PRIVATE() \
    struct Private; \
    std::unique_ptr<Private> _p

//! Convenience macro for accessing private implementations.
#define TG_P() \
    auto& p = *_p

//! Convenience macro for enum utilities.
//! 
//! Required includes:
//! * iostream
//! * string
//! * vector
#define TG_ENUM(ENUM) \
    std::vector<ENUM> get##ENUM##Enums(); \
    std::vector<std::string> get##ENUM##Labels(); \
    std::string getLabel(ENUM); \
    std::ostream& operator << (std::ostream&, ENUM); \
    std::istream& operator >> (std::istream&, ENUM&)

//! Implementation macro for enum utilities.
//! 
//! Required includes:
//! * tgCore/Error.h
//! * tgCore/String.h
//! * algorithm
//! * array
#define TG_ENUM_IMPL(ENUM, ...) \
    std::vector<ENUM> get##ENUM##Enums() \
    { \
        std::vector<ENUM> out; \
        for (std::size_t i = 0; i < static_cast<std::size_t>(ENUM::Count); ++i) \
        { \
            out.push_back(static_cast<ENUM>(i)); \
        } \
        return out; \
    } \
    \
    std::vector<std::string> get##ENUM##Labels() \
    { \
        return { __VA_ARGS__ }; \
    } \
    \
    std::string getLabel(ENUM value) \
    { \
        const std::array<std::string, static_cast<std::size_t>(ENUM::Count)> data = { __VA_ARGS__ }; \
        return data[static_cast<std::size_t>(value)]; \
    } \
    std::ostream& operator << (std::ostream& os, ENUM in) \
    { \
        os << get##ENUM##Labels()[static_cast<std::size_t>(in)]; \
        return os; \
    } \
    \
    std::istream& operator >> (std::istream& is, ENUM& out) \
    { \
        std::string s; \
        is >> s; \
        const auto labels = get##ENUM##Labels(); \
        const auto i = std::find_if( \
            labels.begin(), \
            labels.end(), \
            [s](const std::string& value) \
            { \
                return tg::core::compare(s, value, tg::core::Compare::CaseInsensitive); \
            }); \
        if (i == labels.end()) \
        { \
            throw tg::core::ParseError(); \
        } \
        out = static_cast<ENUM>(i - labels.begin()); \
        return is; \
    }

