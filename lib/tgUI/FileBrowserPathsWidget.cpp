// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/FileBrowserPrivate.h>

#include <tgUI/Bellows.h>
#include <tgUI/ButtonGroup.h>
#include <tgUI/DrivesModel.h>
#include <tgUI/ListButton.h>
#include <tgUI/RecentFilesModel.h>
#include <tgUI/RowLayout.h>

#include <tgCore/File.h>

#include <filesystem>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct PathsWidget::Private
        {
            std::shared_ptr<DrivesModel> drivesModel;
            std::vector<std::string> drives;
            std::shared_ptr<RecentFilesModel> recentFilesModel;
            std::vector<std::string> recent;
            std::vector<std::string> paths;
            std::vector<std::shared_ptr<ListButton> > buttons;
            std::shared_ptr<ButtonGroup> buttonGroup;
            std::map<std::string, std::shared_ptr<Bellows> > bellows;
            std::map<std::string, std::shared_ptr<VerticalLayout> > layouts;
            std::shared_ptr<VerticalLayout> layout;
            std::function<void(const std::string&)> callback;
            std::shared_ptr<ListObserver<std::string> > drivesObserver;
            std::shared_ptr<ListObserver<std::string> > recentObserver;
        };

        void PathsWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::PathsWidget", parent);
            TG_P();

            setBackgroundRole(ColorRole::Base);

            p.drivesModel = DrivesModel::create(context);

            p.buttonGroup = ButtonGroup::create(context, ButtonGroupType::Click);

            p.layout = VerticalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::None);

            p.bellows["Drives"] = Bellows::create(context, "Drives", p.layout);
            p.bellows["Drives"]->setOpen(true);
            p.layouts["Drives"] = VerticalLayout::create(context);
            p.layouts["Drives"]->setSpacingRole(SizeRole::None);
            p.bellows["Drives"]->setWidget(p.layouts["Drives"]);

            p.bellows["Shortcuts"] = Bellows::create(context, "Shortcuts", p.layout);
            p.bellows["Shortcuts"]->setOpen(true);
            p.layouts["Shortcuts"] = VerticalLayout::create(context);
            p.layouts["Shortcuts"]->setSpacingRole(SizeRole::None);
            p.bellows["Shortcuts"]->setWidget(p.layouts["Shortcuts"]);

            p.bellows["Recent"] = Bellows::create(context, "Recent", p.layout);
            p.bellows["Recent"]->setOpen(true);
            p.layouts["Recent"] = VerticalLayout::create(context);
            p.layouts["Recent"]->setSpacingRole(SizeRole::None);
            p.bellows["Recent"]->setWidget(p.layouts["Recent"]);

            _pathsUpdate();

            p.buttonGroup->setClickedCallback(
                [this](int value)
                {
                    TG_P();
                    if (value >= 0 && value < p.paths.size())
                    {
                        const std::string& path = p.paths[value];
                        if (p.callback)
                        {
                            p.callback(path);
                        }
                    }
                });

            p.drivesObserver = ListObserver<std::string>::create(
                p.drivesModel->observeDrives(),
                [this](const std::vector<std::string>& value)
                {
                    _p->drives = value;
                    _pathsUpdate();
                });
        }

        PathsWidget::PathsWidget() :
            _p(new Private)
        {}

        PathsWidget::~PathsWidget()
        {}

        std::shared_ptr<PathsWidget> PathsWidget::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<PathsWidget>(new PathsWidget);
            out->_init(context, parent);
            return out;
        }

        void PathsWidget::setCallback(const std::function<void(const std::string&)>& value)
        {
            _p->callback = value;
        }

        void PathsWidget::setRecentFilesModel(const std::shared_ptr<RecentFilesModel>& value)
        {
            TG_P();
            p.recentObserver.reset();
            p.recentFilesModel = value;
            if (p.recentFilesModel)
            {
                p.recentObserver = ListObserver<std::string>::create(
                    p.recentFilesModel->observeRecent(),
                    [this](const std::vector<std::string>& value)
                    {
                        _p->recent = value;
                        _pathsUpdate();
                    });
            }
        }

        void PathsWidget::setGeometry(const core::Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void PathsWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->layout->getSizeHint());
        }

        void PathsWidget::_createButton(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const std::string& toolTip,
            const std::shared_ptr<IWidget>& parent)
        {
            TG_P();
            auto button = ListButton::create(context, parent);
            button->setText(text);
            button->setTooltip(toolTip);
            p.buttons.push_back(button);
            p.buttonGroup->addButton(button);
        }

        void PathsWidget::_pathsUpdate()
        {
            TG_P();
            
            p.paths.clear();
            for (auto layout : p.layouts)
            {
                auto children = layout.second->getChildren();
                for (auto i : children)
                {
                    i->setParent(nullptr);
                }
            }
            p.buttons.clear();
            p.buttonGroup->clearButtons();

            if (auto context = _getContext().lock())
            {
                for (const auto& i : p.drives)
                {
                    _createButton(context, i, std::string(), p.layouts["Drives"]);
                    p.paths.push_back(i);
                }

                const std::string currentPath = std::filesystem::current_path().string();
                _createButton(context, "Current", currentPath, p.layouts["Shortcuts"]);
                p.paths.push_back(currentPath);
                for (auto userPath : getUserPathEnums())
                {
                    const std::string path = getUserPath(userPath);
                    _createButton(
                        context,
                        std::filesystem::path(path).filename().string(),
                        path,
                        p.layouts["Shortcuts"]);
                    p.paths.push_back(path);
                }

                for (auto recent : p.recent)
                {
                    _createButton(
                        context,
                        std::filesystem::path(recent).filename().string(),
                        recent,
                        p.layouts["Recent"]);
                    p.paths.push_back(std::filesystem::path(recent).parent_path().string());
                }
            }
        }
    }
}
