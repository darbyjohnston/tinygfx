// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/ObservableList.h>
#include <tgCore/ObservableValue.h>

#include <string>

namespace tg
{
    namespace core
    {
        class Context;
    }

    namespace ui
    {
        //! Recent files model.
        class RecentFilesModel : public std::enable_shared_from_this<RecentFilesModel>
        {
            TG_NON_COPYABLE(RecentFilesModel);

        protected:
            void _init(const std::shared_ptr<Context>&);

            RecentFilesModel();

        public:
            ~RecentFilesModel();

            //! Create a new model.
            static std::shared_ptr<RecentFilesModel> create(
                const std::shared_ptr<Context>&);

            //! Get the maximum number of recent files.
            size_t getRecentMax() const;

            //! Observe the maximum number of recent files.
            std::shared_ptr<core::IObservableValue<size_t> > observeRecentMax() const;

            //! Set the maximum number of recent files.
            void setRecentMax(size_t);

            //! Get the list of recent files.
            const std::vector<std::string>& getRecent() const;

            //! Observe the list of recent files.
            std::shared_ptr<core::IObservableList<std::string> > observeRecent() const;

            //! Set the recent files.
            void setRecent(const std::vector<std::string>&);

            //! Add a recent file.
            void addRecent(const std::string&);

        private:
            TG_PRIVATE();
        };
    }
}
