// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ListWidget.h>

#include <tgUI/ButtonGroup.h>
#include <tgUI/ListButton.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ScrollWidget.h>

#include <tgCore/String.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct ListWidget::Private
        {
            std::vector<std::string> items;
            int currentItem = -1;
            std::string search;

            std::shared_ptr<ButtonGroup> buttonGroup;
            std::shared_ptr<VerticalLayout> layout;
            std::shared_ptr<ScrollWidget> scrollWidget;

            std::function<void(int)> callback;
        };

        void ListWidget::_init(
            const std::shared_ptr<Context>& context,
            ButtonGroupType type,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::ListWidget", parent);
            TG_P();

            p.buttonGroup = ButtonGroup::create(context, type);

            p.layout = VerticalLayout::create(context);
            p.layout->setSpacingRole(SizeRole::None);

            p.scrollWidget = ScrollWidget::create(context, ScrollType::Both, shared_from_this());
            p.scrollWidget->setWidget(p.layout);

            switch (type)
            {
            case ButtonGroupType::Click:
                p.buttonGroup->setClickedCallback(
                    [this](int index)
                    {
                        if (_p->callback)
                        {
                            _p->callback(index);
                        }
                    });
                break;
            case ButtonGroupType::Check:
            case ButtonGroupType::Radio:
            case ButtonGroupType::Toggle:
                p.buttonGroup->setCheckedCallback(
                    [this](int index, bool value)
                    {
                        if (value && _p->callback)
                        {
                            _p->callback(index);
                        }
                    });
                break;
            default: break;
            }
        }

        ListWidget::ListWidget() :
            _p(new Private)
        {}

        ListWidget::~ListWidget()
        {}

        std::shared_ptr<ListWidget> ListWidget::create(
            const std::shared_ptr<Context>& context,
            ButtonGroupType type,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ListWidget>(new ListWidget);
            out->_init(context, type, parent);
            return out;
        }

        void ListWidget::setItems(const std::vector<std::string>& value)
        {
            TG_P();
            if (value == p.items)
                return;
            p.items = value;
            p.currentItem = clamp(p.currentItem, 0, static_cast<int>(p.items.size()) - 1);
            _widgetUpdate();
            _searchUpdate();
        }

        void ListWidget::setCurrentItem(int value)
        {
            TG_P();
            if (value == p.currentItem)
                return;
            p.currentItem = value;
            p.buttonGroup->setChecked(p.currentItem, true);
        }

        void ListWidget::setCallback(const std::function<void(int)>& value)
        {
            _p->callback = value;
        }

        void ListWidget::setSearch(const std::string& value)
        {
            TG_P();
            if (value == p.search)
                return;
            p.search = value;
            _searchUpdate();
        }

        void ListWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->scrollWidget->setGeometry(value);
        }

        void ListWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->scrollWidget->getSizeHint());
        }

        void ListWidget::_widgetUpdate()
        {
            TG_P();
            p.buttonGroup->clearButtons();
            auto children = p.layout->getChildren();
            for (const auto& child : children)
            {
                child->setParent(nullptr);
            }
            if (auto context = _getContext().lock())
            {
                for (const auto& item : p.items)
                {
                    auto button = ListButton::create(context, item, p.layout);
                    p.buttonGroup->addButton(button);
                }
            }
            p.buttonGroup->setChecked(p.currentItem, true);
        }

        void ListWidget::_searchUpdate()
        {
            TG_P();
            size_t i = 0;
            for (const auto& child : p.layout->getChildren())
            {
                if (i < p.items.size())
                {
                    child->setVisible(contains(
                        p.items[i],
                        p.search,
                        Compare::CaseInsensitive));
                }
                ++i;
            }
        }
    }
}
