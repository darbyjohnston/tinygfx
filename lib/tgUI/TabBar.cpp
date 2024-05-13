// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/TabBar.h>

#include <tgUI/ButtonGroup.h>
#include <tgUI/ListButton.h>
#include <tgUI/RowLayout.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct TabBar::Private
        {
            std::vector<std::string> tabs;
            int currentTab = -1;
            std::shared_ptr<ButtonGroup> buttonGroup;
            std::vector<std::shared_ptr<ListButton> > buttons;
            std::shared_ptr<HorizontalLayout> layout;
            std::function<void(int)> callback;
        };

        void TabBar::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::TabBar", parent);
            TG_P();

            p.buttonGroup = ButtonGroup::create(context, ButtonGroupType::Radio);

            p.layout = HorizontalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::None);

            p.buttonGroup->setCheckedCallback(
                [this](int index, bool value)
                {
                    if (value && _p->callback)
                    {
                        _p->callback(index);
                    }
                });
        }

        TabBar::TabBar() :
            _p(new Private)
        {}

        TabBar::~TabBar()
        {}

        std::shared_ptr<TabBar> TabBar::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<TabBar>(new TabBar);
            out->_init(context, parent);
            return out;
        }

        const std::vector<std::string>& TabBar::getTabs() const
        {
            return _p->tabs;
        }

        void TabBar::setTabs(const std::vector<std::string>& value)
        {
            TG_P();
            if (value == p.tabs)
                return;
            p.tabs = value;
            p.currentTab = clamp(p.currentTab, 0, static_cast<int>(p.tabs.size()) - 1);
            _widgetUpdate();
        }

        void TabBar::addTab(const std::string& value)
        {
            TG_P();
            p.tabs.push_back(value);
            if (p.currentTab < 0)
            {
                p.currentTab = 0;
            }
            _widgetUpdate();
        }

        void TabBar::clearTabs()
        {
            TG_P();
            p.tabs.clear();
            p.currentTab = -1;
            _widgetUpdate();
        }

        int TabBar::getCurrentTab() const
        {
            return _p->currentTab;
        }

        void TabBar::setCurrentTab(int value)
        {
            TG_P();
            const int tmp = clamp(value, 0, static_cast<int>(p.tabs.size()) - 1);
            if (tmp == _p->currentTab)
                return;
            _p->currentTab = tmp;
            _p->buttonGroup->setChecked(_p->currentTab, true);
        }

        void TabBar::setCallback(const std::function<void(int)>& value)
        {
            _p->callback = value;
        }

        void TabBar::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void TabBar::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->layout->getSizeHint());
        }

        void TabBar::_widgetUpdate()
        {
            TG_P();
            p.buttonGroup->clearButtons();
            p.buttons.clear();
            auto children = p.layout->getChildren();
            for (const auto& child : children)
            {
                child->setParent(nullptr);
            }
            if (auto context = _getContext().lock())
            {
                for (const auto& tab : p.tabs)
                {
                    auto button = ListButton::create(context, tab, p.layout);
                    button->setCheckedRole(ColorRole::Button);
                    p.buttonGroup->addButton(button);
                    p.buttons.push_back(button);
                }
            }
            p.buttonGroup->setChecked(p.currentTab, true);
        }
    }
}
