// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/FileBrowserPrivate.h>

#include <tgUI/ComboBox.h>
#include <tgUI/Divider.h>
#include <tgUI/Label.h>
#include <tgUI/LineEdit.h>
#include <tgUI/PushButton.h>
#include <tgUI/RecentFilesModel.h>
#include <tgUI/RowLayout.h>
#include <tgUI/SearchBox.h>
#include <tgUI/ScrollWidget.h>
#include <tgUI/Spacer.h>
#include <tgUI/Splitter.h>
#include <tgUI/ToolButton.h>

#include <tgCore/Format.h>

#include <filesystem>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct FileBrowserWidget::Private
        {
            std::string path;
            FileBrowserOptions options;
            std::vector<std::string> extensions;
            std::shared_ptr<RecentFilesModel> recentFilesModel;

            std::shared_ptr<Label> titleLabel;
            std::shared_ptr<ToolButton> upButton;
            std::shared_ptr<ToolButton> reloadButton;
            std::shared_ptr<LineEdit> pathEdit;
            std::shared_ptr<PathsWidget> pathsWidget;
            std::shared_ptr<ScrollWidget> pathsScrollWidget;
            std::shared_ptr<DirectoryWidget> directoryWidget;
            std::shared_ptr<ScrollWidget> directoryScrollWidget;
            std::shared_ptr<SearchBox> searchBox;
            std::shared_ptr<ComboBox> extensionsComboBox;
            std::shared_ptr<ComboBox> sortComboBox;
            std::shared_ptr<ToolButton> reverseSortButton;
            std::shared_ptr<PushButton> okButton;
            std::shared_ptr<PushButton> cancelButton;
            std::shared_ptr<Splitter> splitter;
            std::shared_ptr<VerticalLayout> layout;

            std::function<void(const std::string&)> callback;
            std::function<void(void)> cancelCallback;
            std::function<void(const FileBrowserOptions&)> optionsCallback;
        };

        void FileBrowserWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::string& path,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::FileBrowserWidget", parent);
            TG_P();

            setHStretch(Stretch::Expanding);
            setVStretch(Stretch::Expanding);
            _setMouseHover(true);
            _setMousePress(true);

            p.path = path;

            p.titleLabel = Label::create(context, "File Browser");
            p.titleLabel->setMarginRole(SizeRole::MarginSmall);
            p.titleLabel->setBackgroundRole(ColorRole::Button);

            p.upButton = ToolButton::create(context);
            p.upButton->setIcon("DirectoryUp");
            p.upButton->setToolTip("Go up a directory");

            p.reloadButton = ToolButton::create(context);
            p.reloadButton->setIcon("Reload");
            p.reloadButton->setToolTip("Reload the current directory");

            p.pathEdit = LineEdit::create(context);
            p.pathEdit->setHStretch(Stretch::Expanding);
            p.pathEdit->setToolTip("The current directory");

            p.pathsWidget = PathsWidget::create(context);
            p.pathsScrollWidget = ScrollWidget::create(context);
            p.pathsScrollWidget->setWidget(p.pathsWidget);
            p.pathsScrollWidget->setVStretch(Stretch::Expanding);

            p.directoryWidget = DirectoryWidget::create(context);
            p.directoryScrollWidget = ScrollWidget::create(context);
            p.directoryScrollWidget->setWidget(p.directoryWidget);
            p.directoryScrollWidget->setVStretch(Stretch::Expanding);

            p.searchBox = SearchBox::create(context);

            std::vector<std::string> extensionsLabels;
            p.extensions.push_back(std::string());
            extensionsLabels.push_back("*.*");
            p.extensionsComboBox = ComboBox::create(context, extensionsLabels);
            if (!extensionsLabels.empty())
            {
                p.extensionsComboBox->setCurrentIndex(extensionsLabels.size() - 1);
            }
            p.extensionsComboBox->setToolTip("Filter by extension");

            p.sortComboBox = ComboBox::create(context, getFileBrowserSortLabels());
            p.sortComboBox->setToolTip("Sorting");

            p.reverseSortButton = ToolButton::create(context);
            p.reverseSortButton->setCheckable(true);
            p.reverseSortButton->setToolTip("Reverse sorting");

            p.okButton = PushButton::create(context);
            p.okButton->setText("Ok");

            p.cancelButton = PushButton::create(context);
            p.cancelButton->setText("Cancel");

            p.layout = VerticalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::None);
            p.titleLabel->setParent(p.layout);
            Divider::create(context, Orientation::Vertical, p.layout);
            auto vLayout = VerticalLayout::create(context, p.layout);
            vLayout->setSpacingRole(SizeRole::SpacingSmall);
            vLayout->setMarginRole(SizeRole::MarginSmall);
            vLayout->setVStretch(Stretch::Expanding);
            auto hLayout = HorizontalLayout::create(context, vLayout);
            hLayout->setSpacingRole(SizeRole::SpacingSmall);
            p.upButton->setParent(hLayout);
            p.reloadButton->setParent(hLayout);
            p.pathEdit->setParent(hLayout);
            p.splitter = Splitter::create(context, Orientation::Horizontal, vLayout);
            p.splitter->setSplit(0.2);
            p.pathsScrollWidget->setParent(p.splitter);
            p.directoryScrollWidget->setParent(p.splitter);
            hLayout = HorizontalLayout::create(context, vLayout);
            hLayout->setSpacingRole(SizeRole::SpacingSmall);
            p.searchBox->setParent(hLayout);
            p.extensionsComboBox->setParent(hLayout);
            p.sortComboBox->setParent(hLayout);
            p.reverseSortButton->setParent(hLayout);
            auto spacer = Spacer::create(context, Orientation::Horizontal, hLayout);
            spacer->setSpacingRole(SizeRole::None);
            spacer->setHStretch(Stretch::Expanding);
            p.okButton->setParent(hLayout);
            p.cancelButton->setParent(hLayout);

            _pathUpdate();
            _optionsUpdate();

            p.upButton->setClickedCallback(
                [this]
                {
                    _p->path = std::filesystem::path(_p->path).parent_path().string();
                    _pathUpdate();
                });

            p.reloadButton->setClickedCallback(
                [this]
                {
                    _p->directoryWidget->reload();
                });

            p.pathEdit->setTextCallback(
                [this](const std::string& value)
                {
                    _p->path = value;
                    _pathUpdate();
                });

            p.pathsWidget->setCallback(
                [this](const std::string& value)
                {
                    _p->path = value;
                    _pathUpdate();
                });

            p.directoryWidget->setCallback(
                [this](const std::string& value)
                {
                    TG_P();
                    if (std::filesystem::is_directory(value))
                    {
                        p.path = value;
                        _pathUpdate();
                    }
                    else
                    {
                        if (p.recentFilesModel)
                        {
                            p.recentFilesModel->addRecent(value);
                        }
                        if (p.callback)
                        {
                            p.callback(value);
                        }
                    }
                });

            p.searchBox->setCallback(
                [this](const std::string& value)
                {
                    TG_P();
                    p.options.search = value;
                    p.directoryWidget->setOptions(p.options);
                    if (p.optionsCallback)
                    {
                        p.optionsCallback(p.options);
                    }
                });

            p.extensionsComboBox->setIndexCallback(
                [this](int value)
                {
                    TG_P();
                    if (value >= 0 && value < p.extensions.size())
                    {
                        p.options.extension = p.extensions[value];
                        p.directoryWidget->setOptions(p.options);
                        if (p.optionsCallback)
                        {
                            p.optionsCallback(p.options);
                        }
                    }
                });

            p.sortComboBox->setIndexCallback(
                [this](int value)
                {
                    TG_P();
                    p.options.sort = static_cast<FileBrowserSort>(value);
                    p.directoryWidget->setOptions(p.options);
                    if (p.optionsCallback)
                    {
                        p.optionsCallback(p.options);
                    }
                });

            p.reverseSortButton->setCheckedCallback(
                [this](bool value)
                {
                    TG_P();
                    p.options.reverseSort = value;
                    p.directoryWidget->setOptions(p.options);
                    if (p.optionsCallback)
                    {
                        p.optionsCallback(p.options);
                    }
                });

            p.okButton->setClickedCallback(
                [this]
                {
                    TG_P();
                    if (p.recentFilesModel)
                    {
                        p.recentFilesModel->addRecent(p.path);
                    }
                    if (p.callback)
                    {
                        p.callback(p.path);
                    }
                });

            p.cancelButton->setClickedCallback(
                [this]
                {
                    TG_P();
                    if (p.cancelCallback)
                    {
                        p.cancelCallback();
                    }
                });
        }

        FileBrowserWidget::FileBrowserWidget() :
            _p(new Private)
        {}

        FileBrowserWidget::~FileBrowserWidget()
        {}

        std::shared_ptr<FileBrowserWidget> FileBrowserWidget::create(
            const std::shared_ptr<Context>& context,
            const std::string& path,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<FileBrowserWidget>(new FileBrowserWidget);
            out->_init(context, path, parent);
            return out;
        }

        void FileBrowserWidget::setCallback(const std::function<void(const std::string&)>& value)
        {
            _p->callback = value;
        }

        void FileBrowserWidget::setCancelCallback(const std::function<void(void)>& value)
        {
            _p->cancelCallback = value;
        }

        const std::string& FileBrowserWidget::getPath() const
        {
            return _p->path;
        }
        
        const FileBrowserOptions& FileBrowserWidget::getOptions() const
        {
            return _p->directoryWidget->getOptions();
        }

        void FileBrowserWidget::setOptions(const FileBrowserOptions& value)
        {
            TG_P();
            if (value == p.options)
                return;
            p.options = value;
            _optionsUpdate();
        }
        
        void FileBrowserWidget::setOptionsCallback(const std::function<void(const FileBrowserOptions&)>& value)
        {
            _p->optionsCallback = value;
        }

        void FileBrowserWidget::setRecentFilesModel(const std::shared_ptr<RecentFilesModel>& value)
        {
            TG_P();
            p.recentFilesModel = value;
            p.pathsWidget->setRecentFilesModel(value);
        }

        void FileBrowserWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void FileBrowserWidget::sizeHintEvent(const SizeHintEvent& value)
        {
            IWidget::sizeHintEvent(value);
            _setSizeHint(_p->layout->getSizeHint());
        }

        void FileBrowserWidget::_pathUpdate()
        {
            TG_P();
            p.pathEdit->setText(p.path);
            p.directoryWidget->setPath(p.path);
            p.directoryScrollWidget->setScrollPos(V2I());
        }
        
        void FileBrowserWidget::_optionsUpdate()
        {
            TG_P();
            p.directoryWidget->setOptions(p.options);
            p.searchBox->setText(p.options.search);
            const auto i = std::find(
                p.extensions.begin(),
                p.extensions.end(),
                p.options.extension);
            if (i != p.extensions.end())
            {
                p.extensionsComboBox->setCurrentIndex(i - p.extensions.begin());
            }
            p.sortComboBox->setCurrentIndex(static_cast<int>(p.options.sort));
            p.reverseSortButton->setChecked(p.options.reverseSort);
        }
    }
}
