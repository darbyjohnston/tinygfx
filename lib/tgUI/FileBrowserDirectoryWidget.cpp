// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/FileBrowserPrivate.h>

#include <tgUI/ButtonGroup.h>
#include <tgUI/RowLayout.h>

#include <tgCore/String.h>

#include <filesystem>

using namespace tg::core;

namespace tg
{
    namespace ui
    {        
        struct DirectoryWidget::Private
        {
            std::filesystem::path path;
            FileBrowserOptions options;
            std::vector<FileInfo> fileInfo;
            std::vector<std::shared_ptr<Button> > buttons;
            std::shared_ptr<ButtonGroup> buttonGroup;
            std::shared_ptr<VerticalLayout> layout;
            std::function<void(const std::filesystem::path&)> callback;

            struct SizeData
            {
                int spacing = 0;
            };
            SizeData size;
        };

        void DirectoryWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::DirectoryWidget", parent);
            TG_P();

            setBackgroundRole(ColorRole::Base);

            p.buttonGroup = ButtonGroup::create(context, ButtonGroupType::Click);

            p.layout = VerticalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::None);

            p.buttonGroup->setClickedCallback(
                [this](int value)
                {
                    TG_P();
                    if (value >= 0 && value < p.fileInfo.size())
                    {
                        const FileInfo fileInfo = p.fileInfo[value];
                        if (p.callback)
                        {
                            p.callback(fileInfo.path);
                        }
                        if (fileInfo.isDir)
                        {
                            p.path = fileInfo.path;
                            _directoryUpdate();
                        }
                    }
                });
        }

        DirectoryWidget::DirectoryWidget() :
            _p(new Private)
        {}

        DirectoryWidget::~DirectoryWidget()
        {}

        std::shared_ptr<DirectoryWidget> DirectoryWidget::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<DirectoryWidget>(new DirectoryWidget);
            out->_init(context, parent);
            return out;
        }

        void DirectoryWidget::setPath(const std::filesystem::path& path)
        {
            TG_P();
            if (path == p.path)
                return;
            p.path = path;
            _directoryUpdate();
        }

        void DirectoryWidget::reload()
        {
            _directoryUpdate();
        }

        void DirectoryWidget::setCallback(const std::function<void(const std::filesystem::path&)>& value)
        {
            _p->callback = value;
        }

        void DirectoryWidget::setOptions(const FileBrowserOptions& value)
        {
            TG_P();
            if (value == p.options)
                return;
            p.options = value;
            _directoryUpdate();
        }

        const FileBrowserOptions& DirectoryWidget::getOptions() const
        {
            return _p->options;
        }

        void DirectoryWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            TG_P();
            std::vector<int> columns;
            for (const auto& button : p.buttons)
            {
                if (columns.empty())
                {
                    columns = button->getTextWidths();
                }
                else
                {
                    const auto textWidths = button->getTextWidths();
                    for (size_t i = 0; i < columns.size() && i < textWidths.size(); ++i)
                    {
                        columns[i] = std::max(columns[i], textWidths[i]);
                    }
                }
            }
            if (!columns.empty())
            {
                for (size_t i = 0; i < columns.size() - 1; ++i)
                {
                    columns[i] += p.size.spacing;
                }
            }
            for (const auto& button : p.buttons)
            {
                button->setColumns(columns);
            }
            _p->layout->setGeometry(value);
        }

        void DirectoryWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();

            p.size.spacing = event.style->getSizeRole(SizeRole::Spacing, event.displayScale);

            std::vector<int> columns;
            for (const auto& button : p.buttons)
            {
                if (columns.empty())
                {
                    columns = button->getTextWidths();
                }
                else
                {
                    const auto textWidths = button->getTextWidths();
                    for (size_t i = 0; i < columns.size() && i < textWidths.size(); ++i)
                    {
                        columns[i] = std::max(columns[i], textWidths[i]);
                    }
                }
            }
            if (!columns.empty())
            {
                for (size_t i = 0; i < columns.size() - 1; ++i)
                {
                    columns[i] += p.size.spacing;
                }
            }
            for (const auto& button : p.buttons)
            {
                button->setColumns(columns);
            }

            Size2I sizeHint = p.layout->getSizeHint();
            for (size_t i = 0; i < columns.size(); ++i)
            {
                sizeHint.w += columns[i];
            }
            _setSizeHint(sizeHint);
        }
        
        namespace
        {
            void list(
                const std::filesystem::path& path,
                const FileBrowserOptions& options,
                std::vector<FileInfo>& out)
            {
                try
                {
                    for (const auto& i : std::filesystem::directory_iterator(path))
                    {
                        const auto& path = i.path();
                        const std::string fileName = path.filename().string();
                        bool keep = true;
                        if (!options.search.empty())
                        {
                            keep = contains(
                                fileName,
                                options.search,
                                Compare::CaseInsensitive);
                        }
                        const bool isDir = std::filesystem::is_directory(path);
                        std::string extension;
                        if (!isDir)
                        {
                            extension = path.extension().string();
                        }
                        if (!isDir && !options.extension.empty())
                        {
                            keep = compare(
                                extension,
                                options.extension,
                                Compare::CaseInsensitive);
                        }
                        if (keep)
                        {
                            out.push_back({
                                path,
                                isDir,
                                isDir ? 0 : std::filesystem::file_size(path),
                                std::filesystem::last_write_time(path) });
                        }
                    }
                }
                catch (const std::exception&)
                {}

                std::function<int(const FileInfo& a, const FileInfo& b)> sort;
                switch (options.sort)
                {
                case FileBrowserSort::Name:
                    sort = [](const FileInfo& a, const FileInfo& b)
                    {
                        return a.path.filename() < b.path.filename();
                    };
                    break;
                case FileBrowserSort::Extension:
                    sort = [](const FileInfo& a, const FileInfo& b)
                    {
                        return a.path.extension() < b.path.extension();
                    };
                    break;
                case FileBrowserSort::Size:
                    sort = [](const FileInfo& a, const FileInfo& b)
                    {
                        return a.size < b.size;
                    };
                    break;
                case FileBrowserSort::Time:
                    sort = [](const FileInfo& a, const FileInfo& b)
                    {
                        return a.time < b.time;
                    };
                    break;
                default: break;
                }
                if (sort)
                {
                    if (options.reverseSort)
                    {
                        std::sort(out.rbegin(), out.rend(), sort);
                    }
                    else
                    {
                        std::sort(out.begin(), out.end(), sort);
                    }
                }
                std::stable_sort(
                    out.begin(),
                    out.end(),
                    [](const FileInfo& a, const FileInfo& b)
                    {
                        return a.isDir > b.isDir;
                    });
            }
        }

        void DirectoryWidget::_directoryUpdate()
        {
            TG_P();
            for (const auto& button : p.buttons)
            {
                button->setParent(nullptr);
            }
            p.buttons.clear();
            p.buttonGroup->clearButtons();
            p.fileInfo.clear();
            list(p.path, p.options, p.fileInfo);
            if (auto context = _getContext().lock())
            {
                for (const auto& fileInfo : p.fileInfo)
                {
                    auto button = Button::create(context, fileInfo);
                    button->setParent(p.layout);
                    p.buttons.push_back(button);
                    p.buttonGroup->addButton(button);
                }
            }
        }
    }
}
