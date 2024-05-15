// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/RecentFilesModel.h>

#include <tgUI/RecentFilesModel.h>

#include <tgCore/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void recentFilesModel(py::module_& m)
        {
            py::class_<RecentFilesModel, std::shared_ptr<RecentFilesModel> >(m, "RecentFilesModel")
                .def(
                    py::init(&RecentFilesModel::create),
                    py::arg("context"))
                .def_property(
                    "recentMax",
                    &RecentFilesModel::getRecentMax,
                    &RecentFilesModel::setRecentMax)
                .def("observeRecentMax", &RecentFilesModel::observeRecentMax)
                .def_property(
                    "recent",
                    &RecentFilesModel::getRecent,
                    &RecentFilesModel::setRecent)
                .def("observeRecent", &RecentFilesModel::observeRecent)
                .def("addRecent", &RecentFilesModel::addRecent);
        }
    }
}
