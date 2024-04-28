// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/FileBrowserWidgets.h>

#include <tgUI/ButtonGroup.h>
#include <tgUI/RowLayout.h>

#include <tgCore/String.h>

#include <filesystem>

using namespace tg::core;

namespace tg
{
    namespace ui
    {        
        struct FileBrowserDirectoryWidget::Private
        {
            std::filesystem::path path;
            FileBrowserOptions options;
            std::vector<FileBrowserInfo> info;
            std::vector<std::shared_ptr<FileBrowserButton> > buttons;
            std::shared_ptr<ButtonGroup> buttonGroup;
            std::shared_ptr<VerticalLayout> layout;
            std::function<void(const std::filesystem::path&)> callback;

            struct SizeData
            {
                int spacing = 0;
            };
            SizeData size;
        };

        void FileBrowserDirectoryWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::FileBrowserDirectoryWidget", parent);
            TG_P();

            setBackgroundRole(ColorRole::Base);

            p.buttonGroup = ButtonGroup::create(context, ButtonGroupType::Click);

            p.layout = VerticalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::None);

            p.buttonGroup->setClickedCallback(
                [this](int value)
                {
                    TG_P();
                    if (value >= 0 && value < p.info.size())
                    {
                        const FileBrowserInfo& info = p.info[value];
                        if (p.callback)
                        {
                            p.callback(info.path);
                        }
                        if (info.isDir)
                        {
                            p.path = info.path;
                            _directoryUpdate();
                        }
                    }
                });
        }

        FileBrowserDirectoryWidget::FileBrowserDirectoryWidget() :
            _p(new Private)
        {}

        FileBrowserDirectoryWidget::~FileBrowserDirectoryWidget()
        {}

        std::shared_ptr<FileBrowserDirectoryWidget> FileBrowserDirectoryWidget::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<FileBrowserDirectoryWidget>(new FileBrowserDirectoryWidget);
            out->_init(context, parent);
            return out;
        }

        const std::filesystem::path& FileBrowserDirectoryWidget::getPath() const
        {
            return _p->path;
        }

        void FileBrowserDirectoryWidget::setPath(const std::filesystem::path& path)
        {
            TG_P();
            if (path == p.path)
                return;
            p.path = path;
            _directoryUpdate();
        }

        void FileBrowserDirectoryWidget::reload()
        {
            _directoryUpdate();
        }

        void FileBrowserDirectoryWidget::setCallback(const std::function<void(const std::filesystem::path&)>& value)
        {
            _p->callback = value;
        }

        const FileBrowserOptions& FileBrowserDirectoryWidget::getOptions() const
        {
            return _p->options;
        }

        void FileBrowserDirectoryWidget::setOptions(const FileBrowserOptions& value)
        {
            TG_P();
            if (value == p.options)
                return;
            p.options = value;
            _directoryUpdate();
        }

        void FileBrowserDirectoryWidget::setGeometry(const Box2I& value)
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

        void FileBrowserDirectoryWidget::sizeHintEvent(const SizeHintEvent& event)
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
                std::vector<FileBrowserInfo>& out)
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

                std::function<int(const FileBrowserInfo& a, const FileBrowserInfo& b)> sort;
                switch (options.sort)
                {
                case FileBrowserSort::Name:
                    sort = [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.path.filename() < b.path.filename();
                    };
                    break;
                case FileBrowserSort::Extension:
                    sort = [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.path.extension() < b.path.extension();
                    };
                    break;
                case FileBrowserSort::Size:
                    sort = [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.size < b.size;
                    };
                    break;
                case FileBrowserSort::Time:
                    sort = [](const FileBrowserInfo& a, const FileBrowserInfo& b)
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
                    [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.isDir > b.isDir;
                    });
            }
        }

        void FileBrowserDirectoryWidget::_directoryUpdate()
        {
            TG_P();
            for (const auto& button : p.buttons)
            {
                button->setParent(nullptr);
            }
            p.buttons.clear();
            p.buttonGroup->clearButtons();
            p.info.clear();
            list(p.path, p.options, p.info);
            if (auto context = _getContext().lock())
            {
                for (const auto& info : p.info)
                {
                    auto button = FileBrowserButton::create(context, info);
                    button->setParent(p.layout);
                    p.buttons.push_back(button);
                    p.buttonGroup->addButton(button);
                }
            }
        }
    }
}
