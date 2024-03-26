// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/FileEdit.h>

#include <tgUI/LineEdit.h>
#include <tgUI/FileBrowser.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ToolButton.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct FileEdit::Private
        {
            std::filesystem::path path;
            std::shared_ptr<LineEdit> lineEdit;
            std::shared_ptr<ToolButton> browseButton;
            std::shared_ptr<ToolButton> clearButton;
            std::shared_ptr<HorizontalLayout> layout;
            std::function<void(const std::filesystem::path&)> callback;
        };

        void FileEdit::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::FileEdit", parent);
            TG_P();

            setHStretch(Stretch::Expanding);

            p.lineEdit = LineEdit::create(context);
            p.lineEdit->setHStretch(Stretch::Expanding);

            p.browseButton = ToolButton::create(context);
            p.browseButton->setIcon("FileBrowser");
            p.browseButton->setTooltip("Show the file browser");

            p.clearButton = ToolButton::create(context);
            p.clearButton->setIcon("Reset");
            p.clearButton->setTooltip("Clear the file name");

            p.layout = HorizontalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::SpacingTool);
            p.lineEdit->setParent(p.layout);
            p.browseButton->setParent(p.layout);
            p.clearButton->setParent(p.layout);

            p.lineEdit->setTextCallback(
                [this](const std::string& value)
                {
                    _p->path = value;
                    if (_p->callback)
                    {
                        _p->callback(_p->path);
                    }
                });

            p.browseButton->setClickedCallback(
                [this]
                {
                    _openDialog();
                });

            p.clearButton->setClickedCallback(
                [this]
                {
                    _p->lineEdit->clearText();
                    _p->path = std::string();
                    if (_p->callback)
                    {
                        _p->callback(_p->path);
                    }
                });
        }

        FileEdit::FileEdit() :
            _p(new Private)
        {}

        FileEdit::~FileEdit()
        {}

        std::shared_ptr<FileEdit> FileEdit::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<FileEdit>(new FileEdit);
            out->_init(context, parent);
            return out;
        }

        void FileEdit::setPath(const std::filesystem::path& value)
        {
            TG_P();
            if (value == p.path)
                return;
            p.path = value;
            p.lineEdit->setText(value.string());
        }

        const std::filesystem::path& FileEdit::getPath() const
        {
            return _p->path;
        }

        void FileEdit::setCallback(const std::function<void(const std::filesystem::path&)>& value)
        {
            _p->callback = value;
        }

        void FileEdit::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void FileEdit::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->layout->getSizeHint());
        }

        void FileEdit::_openDialog()
        {
            TG_P();
            if (auto context = _getContext().lock())
            {
                if (auto fileBrowserSystem = context->getSystem<FileBrowserSystem>())
                {
                    fileBrowserSystem->open(
                        getWindow(),
                        [this](const std::filesystem::path& value)
                        {
                            _p->path = value;
                            _p->lineEdit->setText(_p->path.string());
                            if (_p->callback)
                            {
                                _p->callback(_p->path);
                            }
                        });
                }
            }
        }
    }
}
