// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/RecentFilesModel.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct RecentFilesModel::Private
        {
            std::shared_ptr<ObservableValue<size_t> > recentMax;
            std::shared_ptr<ObservableList<std::filesystem::path> > recent;
        };

        void RecentFilesModel::_init(const std::shared_ptr<Context>& context)
        {
            TG_P();
            p.recentMax = ObservableValue<size_t>::create(10);
            p.recent = ObservableList<std::filesystem::path>::create();
        }

        RecentFilesModel::RecentFilesModel() :
            _p(new Private)
        {}

        RecentFilesModel::~RecentFilesModel()
        {}

        std::shared_ptr<RecentFilesModel> RecentFilesModel::create(
            const std::shared_ptr<Context>& context)
        {
            auto out = std::shared_ptr<RecentFilesModel>(new RecentFilesModel);
            out->_init(context);
            return out;
        }

        size_t RecentFilesModel::getRecentMax() const
        {
            return _p->recentMax->get();
        }

        std::shared_ptr<IObservableValue<size_t> > RecentFilesModel::observeRecentMax() const
        {
            return _p->recentMax;
        }

        void RecentFilesModel::setRecentMax(size_t value)
        {
            TG_P();
            if (p.recentMax->setIfChanged(value))
            {
                if (p.recent->getSize() > p.recentMax->get())
                {
                    auto recent = p.recent->get();
                    while (recent.size() > p.recentMax->get())
                    {
                        recent.erase(recent.begin());
                    }
                    p.recent->setIfChanged(recent);
                }
            }
        }

        const std::vector<std::filesystem::path>& RecentFilesModel::getRecent() const
        {
            return _p->recent->get();
        }

        std::shared_ptr<IObservableList<std::filesystem::path> > RecentFilesModel::observeRecent() const
        {
            return _p->recent;
        }

        void RecentFilesModel::setRecent(const std::vector<std::filesystem::path>& value)
        {
            TG_P();
            auto recent = value;
            while (recent.size() > p.recentMax->get())
            {
                recent.erase(recent.begin());
            }
            p.recent->setIfChanged(recent);
        }

        void RecentFilesModel::addRecent(const std::filesystem::path& value)
        {
            TG_P();
            auto recent = p.recent->get();
            auto i = recent.begin();
            while (i != recent.end())
            {
                if (*i == value)
                {
                    i = recent.erase(i);
                }
                else
                {
                    ++i;
                }
            }
            recent.push_back(value);
            while (recent.size() > p.recentMax->get())
            {
                recent.erase(recent.begin());
            }
            p.recent->setIfChanged(recent);
        }
    }
}

