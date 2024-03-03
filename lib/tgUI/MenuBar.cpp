// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/MenuBar.h>

#include <tgUI/DrawUtil.h>
#include <tgUI/ListButton.h>
#include <tgUI/RowLayout.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct MenuBar::Private
        {
            std::list<std::shared_ptr<Menu> > menus;
            std::list<std::shared_ptr<ListButton> > buttons;
            std::shared_ptr<HorizontalLayout> layout;
        };

        void MenuBar::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::MenuBar", parent);
            TG_P();
            p.layout = HorizontalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::None);
        }

        MenuBar::MenuBar() :
            _p(new Private)
        {}

        MenuBar::~MenuBar()
        {}

        std::shared_ptr<MenuBar> MenuBar::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<MenuBar>(new MenuBar);
            out->_init(context, parent);
            return out;
        }
        
        void MenuBar::addMenu(
            const std::string& text,
            const std::shared_ptr<Menu>& menu)
        {
            TG_P();
            p.menus.push_back(menu);
            if (auto context = _getContext().lock())
            {
                auto button = ListButton::create(context);
                button->setText(text);
                button->setLabelMarginRole(SizeRole::MarginSmall);
                p.buttons.push_back(button);
                button->setParent(p.layout);
                auto menuWeak = std::weak_ptr<Menu>(menu);
                button->setHoveredCallback(
                    [this, menuWeak, button](bool value)
                    {
                        if (value)
                        {
                            if (auto menu = menuWeak.lock())
                            {
                                std::shared_ptr<Menu> openMenu;
                                for (auto& i : _p->menus)
                                {
                                    if (i->isOpen())
                                    {
                                        openMenu = i;
                                        break;
                                    }
                                }
                                if (openMenu && menu != openMenu)
                                {
                                    openMenu->close();
                                    button->takeKeyFocus();
                                    menu->open(getWindow(), button->getGeometry());
                                }
                            }
                        }
                    });
                button->setPressedCallback(
                    [this, menuWeak, button]
                    {
                        if (auto menu = menuWeak.lock())
                        {
                            if (!menu->isOpen())
                            {
                                menu->open(getWindow(), button->getGeometry());
                            }
                            else
                            {
                                menu->close();
                            }
                        }
                    });
                menu->setCloseCallback(
                    [button]
                    {
                        button->takeKeyFocus();
                    });
                _setSizeUpdate();
                _setDrawUpdate();
            }
        }

        bool MenuBar::shortcut(Key shortcut, int modifiers)
        {
            TG_P();
            bool out = false;
            for (const auto& menu : p.menus)
            {
                if (menu->isEnabled())
                {
                    out |= menu->shortcut(shortcut, modifiers);
                }
            }
            return out;
        }

        void MenuBar::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void MenuBar::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->layout->getSizeHint());
        }
    }
}
