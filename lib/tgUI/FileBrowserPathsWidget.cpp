// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/FileBrowserPrivate.h>

#include <tgUI/Bellows.h>
#include <tgUI/ButtonGroup.h>
#include <tgUI/DrivesModel.h>
#include <tgUI/ListItemsWidget.h>
#include <tgUI/RecentFilesModel.h>
#include <tgUI/RowLayout.h>

#include <tgCore/File.h>

#include <filesystem>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct FileBrowserPathsWidget::Private
        {
            std::shared_ptr<DrivesModel> drivesModel;
            std::vector<std::filesystem::path> drives;
            std::vector<std::filesystem::path> shortcuts;
            std::shared_ptr<RecentFilesModel> recentFilesModel;
            std::vector<std::filesystem::path> recent;
            std::map<std::string, std::shared_ptr<ListItemsWidget> > listWidgets;
            std::map<std::string, std::shared_ptr<Bellows> > bellows;
            std::shared_ptr<VerticalLayout> layout;
            std::function<void(const std::filesystem::path&)> callback;
            std::shared_ptr<ListObserver<std::filesystem::path> > drivesObserver;
            std::shared_ptr<ListObserver<std::filesystem::path> > recentObserver;
        };

        void FileBrowserPathsWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::FileBrowserPathsWidget", parent);
            TG_P();

            setBackgroundRole(ColorRole::Base);

            p.drivesModel = DrivesModel::create(context);

            p.layout = VerticalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::None);

            p.listWidgets["Drives"] = ListItemsWidget::create(context, ButtonGroupType::Click);
            p.bellows["Drives"] = Bellows::create(context, "Drives", p.layout);
            p.bellows["Drives"]->setOpen(true);
            p.bellows["Drives"]->setWidget(p.listWidgets["Drives"]);

            p.listWidgets["Shortcuts"] = ListItemsWidget::create(context, ButtonGroupType::Click);
            p.bellows["Shortcuts"] = Bellows::create(context, "Shortcuts", p.layout);
            p.bellows["Shortcuts"]->setOpen(true);
            p.bellows["Shortcuts"]->setWidget(p.listWidgets["Shortcuts"]);

            p.listWidgets["Recent"] = ListItemsWidget::create(context, ButtonGroupType::Click);
            p.bellows["Recent"] = Bellows::create(context, "Recent", p.layout);
            p.bellows["Recent"]->setOpen(true);
            p.bellows["Recent"]->setWidget(p.listWidgets["Recent"]);

            _pathsUpdate();

            p.listWidgets["Drives"]->setCallback(
                [this](int index, bool)
                {
                    TG_P();
                    if (index >= 0 && index < p.drives.size() && p.callback)
                    {
                        p.callback(p.drives[index]);
                    }
                });

            p.listWidgets["Shortcuts"]->setCallback(
                [this](int index, bool)
                {
                    TG_P();
                    if (index >= 0 && index < p.shortcuts.size() && p.callback)
                    {
                        p.callback(p.shortcuts[index]);
                    }
                });

            p.listWidgets["Recent"]->setCallback(
                [this](int index, bool)
                {
                    TG_P();
                    if (index >= 0 && index < p.recent.size() && p.callback)
                    {
                        p.callback(p.recent[index]);
                    }
                });

            p.drivesObserver = ListObserver<std::filesystem::path>::create(
                p.drivesModel->observeDrives(),
                [this](const std::vector<std::filesystem::path>& value)
                {
                    _p->drives = value;
                    _pathsUpdate();
                });
        }

        FileBrowserPathsWidget::FileBrowserPathsWidget() :
            _p(new Private)
        {}

        FileBrowserPathsWidget::~FileBrowserPathsWidget()
        {}

        std::shared_ptr<FileBrowserPathsWidget> FileBrowserPathsWidget::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<FileBrowserPathsWidget>(new FileBrowserPathsWidget);
            out->_init(context, parent);
            return out;
        }

        void FileBrowserPathsWidget::setCallback(const std::function<void(const std::filesystem::path&)>& value)
        {
            _p->callback = value;
        }

        void FileBrowserPathsWidget::setRecentFilesModel(const std::shared_ptr<RecentFilesModel>& value)
        {
            TG_P();
            p.recentObserver.reset();
            p.recentFilesModel = value;
            if (p.recentFilesModel)
            {
                p.recentObserver = ListObserver<std::filesystem::path>::create(
                    p.recentFilesModel->observeRecent(),
                    [this](const std::vector<std::filesystem::path>& value)
                    {
                        _p->recent = value;
                        _pathsUpdate();
                    });
            }
        }

        void FileBrowserPathsWidget::setGeometry(const core::Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void FileBrowserPathsWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->layout->getSizeHint());
        }

        void FileBrowserPathsWidget::_pathsUpdate()
        {
            TG_P();
            
            std::vector<ListItem> items;
            for (const auto& drive : p.drives)
            {
                items.push_back(ListItem(drive.string(), drive.string()));
            }
            p.listWidgets["Drives"]->setItems(items);

            p.shortcuts.clear();
            items.clear();
            std::filesystem::path path = std::filesystem::current_path();
            p.shortcuts.push_back(path);
            items.push_back(ListItem("Current", path.string()));
            for (auto userPath : getUserPathEnums())
            {
                path = getUserPath(userPath);
                p.shortcuts.push_back(path);
                items.push_back(ListItem(path.filename().string(), path.string()));
            }
            p.listWidgets["Shortcuts"]->setItems(items);

            items.clear();
            for (const auto& recent : p.recent)
            {
                items.push_back(ListItem(recent.filename().string(), recent.string()));
            }
            p.listWidgets["Recent"]->setItems(items);
        }
    }
}
