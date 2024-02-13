// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/SearchBox.h>

#include <tgUI/LineEdit.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ToolButton.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct SearchBox::Private
        {
            std::shared_ptr<LineEdit> lineEdit;
            std::shared_ptr<ToolButton> clearButton;
            std::shared_ptr<HorizontalLayout> layout;

            std::function<void(const std::string&)> callback;
        };

        void SearchBox::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::SearchBox", parent);
            TG_P();

            p.lineEdit = LineEdit::create(context);
            p.lineEdit->setHStretch(Stretch::Expanding);

            p.clearButton = ToolButton::create(context);
            p.clearButton->setIcon("Reset");
            p.clearButton->setTooltip("Clear the search");

            p.layout = HorizontalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::SpacingTool);
            p.lineEdit->setParent(p.layout);
            p.clearButton->setParent(p.layout);

            p.lineEdit->setTextChangedCallback(
                [this](const std::string& value)
                {
                    _p->clearButton->setEnabled(!value.empty());
                    if (_p->callback)
                    {
                        _p->callback(value);
                    }
                });

            p.clearButton->setClickedCallback(
                [this]
                {
                    _p->lineEdit->clearText();
                    _p->clearButton->setEnabled(false);
                    if (_p->callback)
                    {
                        _p->callback(std::string());
                    }
                });
        }

        SearchBox::SearchBox() :
            _p(new Private)
        {}

        SearchBox::~SearchBox()
        {}

        std::shared_ptr<SearchBox> SearchBox::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<SearchBox>(new SearchBox);
            out->_init(context, parent);
            return out;
        }

        void SearchBox::setText(const std::string& value)
        {
            _p->lineEdit->setText(value);
            _p->clearButton->setEnabled(!value.empty());
        }

        void SearchBox::setCallback(const std::function<void(const std::string&)>& value)
        {
            _p->callback = value;
        }

        void SearchBox::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void SearchBox::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->layout->getSizeHint());
        }
    }
}
