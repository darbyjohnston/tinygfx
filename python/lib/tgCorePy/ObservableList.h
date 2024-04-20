// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <pybind11/pybind11.h>

namespace tg
{
    namespace core
    {
        template<typename T>
        void observableList(pybind11::module_&, const std::string& type);
        void observableList(pybind11::module_&);
    }
}

#include <tgCorePy/ObservableListInline.h>
