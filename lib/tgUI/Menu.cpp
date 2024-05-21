// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/MenuPrivate.h>

#include <tgUI/Divider.h>
#include <tgUI/RowLayout.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {

        struct Menu::Private
        {
            std::vector<std::shared_ptr<Action> > items;
            std::vector<std::shared_ptr<MenuButton> > buttons;
            int current = -1;
            std::weak_ptr<Menu> parentMenu;
            std::map<std::shared_ptr<MenuButton>, std::shared_ptr<Menu> > subMenus;
            std::shared_ptr<VerticalLayout> layout;
        };

        void Menu::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IMenuPopup::_init(context, "tg::ui::Menu", parent);
            TG_P();
            setAcceptsKeyFocus(true);
            p.layout = VerticalLayout::create(context);
            p.layout->setSpacingRole(SizeRole::None);
            setWidget(p.layout);
        }

        Menu::Menu() :
            _p(new Private)
        {}

        Menu::~Menu()
        {}

        std::shared_ptr<Menu> Menu::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<Menu>(new Menu);
            out->_init(context, parent);
            return out;
        }

        void Menu::addItem(const std::shared_ptr<Action>& item)
        {
            TG_P();
            p.items.push_back(item);
            if (auto context = _getContext().lock())
            {
                auto button = MenuButton::create(context, p.layout);
                button->setText(item->text);
                button->setIcon(item->icon);
                button->setShortcut(item->shortcut, item->shortcutModifiers);
                button->setCheckable(item->checkable);
                button->setChecked(item->checked);

                const int index = p.buttons.size();
                p.buttons.push_back(button);

                button->setHoveredCallback(
                    [this, index](bool value)
                    {
                        if (value)
                        {
                            if (auto menu = _getOpenMenu())
                            {
                                menu->close();
                            }
                        }
                    });
                button->setClickedCallback(
                    [this, item, index]
                    {
                        _setCurrent(index);
                        _accept();
                        if (item->callback)
                        {
                            item->callback();
                        }
                    });
                button->setCheckedCallback(
                    [this, item, index](bool value)
                    {
                        item->checked = value;
                        _setCurrent(index);
                        _accept();
                        if (item->checkedCallback)
                        {
                            item->checkedCallback(value);
                        }
                    });

                if (-1 == p.current)
                {
                    p.current = 0;
                    _currentUpdate();
                }
            }
        }

        void Menu::setItemChecked(const std::shared_ptr<Action>& item, bool value)
        {
            TG_P();
            const auto i = std::find(p.items.begin(), p.items.end(), item);
            if (i != p.items.end())
            {
                (*i)->checked = value;
                p.buttons[i - p.items.begin()]->setChecked(value);
            }
        }

        void Menu::setItemEnabled(const std::shared_ptr<Action>& item, bool value)
        {
            TG_P();
            const auto i = std::find(p.items.begin(), p.items.end(), item);
            if (i != p.items.end())
            {
                p.buttons[i - p.items.begin()]->setEnabled(value);
            }
        }

        std::shared_ptr<Menu> Menu::addSubMenu(const std::string& text)
        {
            TG_P();
            std::shared_ptr<Menu> out;
            if (auto context = _getContext().lock())
            {
                out = Menu::create(context);
                out->setPopup(MenuPopup::SubMenu);
                out->_p->parentMenu = std::dynamic_pointer_cast<Menu>(shared_from_this());

                auto button = MenuButton::create(context, p.layout);
                button->setText(text);
                button->setSubMenuIcon("SubMenuArrow");
                p.subMenus[button] = out;

                const int index = p.buttons.size();
                p.buttons.push_back(button);

                auto buttonWeak = std::weak_ptr<MenuButton>(button);
                button->setHoveredCallback(
                    [this, out, buttonWeak](bool value)
                    {
                        if (value)
                        {
                            if (!out->isOpen())
                            {
                                if (auto openMenu = _getOpenMenu())
                                {
                                    openMenu->close();
                                }
                                if (auto button = buttonWeak.lock())
                                {
                                    out->open(getWindow(), button->getGeometry());
                                }
                            }
                        }
                    });
                button->setPressedCallback(
                    [this, out, buttonWeak, index]
                    {
                        _setCurrent(index);
                        if (!out->isOpen())
                        {
                            if (auto openMenu = _getOpenMenu())
                            {
                                openMenu->close();
                            }
                            if (auto button = buttonWeak.lock())
                            {
                                out->open(getWindow(), button->getGeometry());
                            }
                        }
                    });

                if (-1 == p.current)
                {
                    p.current = 0;
                    _currentUpdate();
                }
            }
            return out;
        }

        void Menu::addDivider()
        {
            TG_P();
            if (auto context = _getContext().lock())
            {
                Divider::create(context, Orientation::Horizontal, p.layout);
            }
        }

        void Menu::clear()
        {
            TG_P();
            p.items.clear();
            for (auto button : p.buttons)
            {
                button->setParent(nullptr);
            }
            p.buttons.clear();
            p.current = -1;
            p.parentMenu.reset();
            p.subMenus.clear();
        }

        bool Menu::shortcut(Key shortcut, int modifiers)
        {
            TG_P();
            bool out = false;
            for (const auto& item : p.items)
            {
                if (shortcut == item->shortcut &&
                    modifiers == item->shortcutModifiers)
                {
                    if (item->callback)
                    {
                        item->callback();
                        out = true;
                    }
                    if (item->checkedCallback)
                    {
                        setItemChecked(item, !item->checked);
                        item->checkedCallback(item->checked);
                        out = true;
                    }
                }
            }
            return out;
        }

        void Menu::close()
        {
            TG_P();
            for (const auto& subMenu : p.subMenus)
            {
                subMenu.second->close();
            }
            IMenuPopup::close();
        }

        void Menu::keyFocusEvent(bool value)
        {
            IMenuPopup::keyFocusEvent(value);
            _currentUpdate();
        }

        void Menu::keyPressEvent(KeyEvent& event)
        {
            TG_P();
            if (0 == event.modifiers)
            {
                switch (event.key)
                {
                case Key::Enter:
                    event.accept = true;
                    takeKeyFocus();
                    if (p.current >= 0 && p.current < p.buttons.size())
                    {
                        auto button = p.buttons[p.current];
                        const auto i = p.subMenus.find(button);
                        if (i != p.subMenus.end())
                        {
                            i->second->open(getWindow(), button->getGeometry());
                        }
                        else
                        {
                            button->click();
                        }
                    }
                    break;
                case Key::Up:
                    event.accept = true;
                    takeKeyFocus();
                    _setCurrent(p.current - 1);
                    break;
                case Key::Down:
                    event.accept = true;
                    takeKeyFocus();
                    _setCurrent(p.current + 1);
                    break;
                case Key::Home:
                    event.accept = true;
                    takeKeyFocus();
                    _setCurrent(0);
                    break;
                case Key::End:
                    event.accept = true;
                    takeKeyFocus();
                    _setCurrent(static_cast<int>(p.buttons.size()) - 1);
                    break;
                default: break;
                }
            }
            if (!event.accept)
            {
                IMenuPopup::keyPressEvent(event);
            }
        }

        void Menu::keyReleaseEvent(KeyEvent& event)
        {
            IMenuPopup::keyReleaseEvent(event);
            event.accept = true;
        }

        void Menu::_setCurrent(int value)
        {
            TG_P();
            const int tmp = clamp(value, 0, static_cast<int>(p.buttons.size()) - 1);
            if (tmp == p.current)
                return;
            p.current = tmp;
            _currentUpdate();
        }

        void Menu::_currentUpdate()
        {
            TG_P();
            const bool focus = hasKeyFocus();
            for (int i = 0; i < p.buttons.size(); ++i)
            {
                p.buttons[i]->setCurrent(p.current == i && focus);
            }
        }

        std::shared_ptr<Menu> Menu::_getOpenMenu() const
        {
            TG_P();
            std::shared_ptr<Menu> out;
            for (const auto i : p.subMenus)
            {
                if (i.second->isOpen())
                {
                    out = i.second;
                    break;
                }
            }
            return out;
        }

        void Menu::_accept()
        {
            TG_P();
            close();
            if (auto parentMenu = p.parentMenu.lock())
            {
                parentMenu->_accept();
            }
        }
    }
}
