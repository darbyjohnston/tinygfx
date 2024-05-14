// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/MenuBarPrivate.h>

#include <tgUI/DrawUtil.h>
#include <tgUI/RowLayout.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct MenuBar::Private
        {
            std::vector<std::shared_ptr<Menu> > menus;
            std::vector<std::shared_ptr<MenuBarButton> > buttons;
            std::shared_ptr<HorizontalLayout> layout;
            int current = -1;
        };

        void MenuBar::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::MenuBar", parent);
            TG_P();

            setAcceptsKeyFocus(true);

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
                auto button = MenuBarButton::create(context, text, p.layout);

                const int index = p.buttons.size();
                p.buttons.push_back(button);
                
                auto menuWeak = std::weak_ptr<Menu>(menu);
                button->setHoveredCallback(
                    [this, index](bool value)
                    {
                        if (value && _getOpenMenu())
                        {
                            _setCurrent(index);
                        }
                    });
                button->setPressedCallback(
                    [this, index]
                    {
                        takeKeyFocus();
                        _setCurrent(index);
                        _openMenu(index);
                    });

                if (-1 == p.current)
                {
                    p.current = 0;
                    _currentUpdate();
                }
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

        void MenuBar::keyFocusEvent(bool value)
        {
            IWidget::keyFocusEvent(value);
            _currentUpdate();
        }

        void MenuBar::keyPressEvent(KeyEvent& event)
        {
            TG_P();
            if (0 == event.modifiers)
            {
                switch (event.key)
                {
                case Key::Left:
                    if (!_getOpenMenu())
                    {
                        event.accept = true;
                        takeKeyFocus();
                        _setCurrent(p.current - 1);
                    }
                    break;
                case Key::Right:
                    if (!_getOpenMenu())
                    {
                        event.accept = true;
                        takeKeyFocus();
                        _setCurrent(p.current + 1);
                    }
                    break;
                case Key::Home:
                    if (!_getOpenMenu())
                    {
                        event.accept = true;
                        takeKeyFocus();
                        _setCurrent(0);
                    }
                    break;
                case Key::End:
                    if (!_getOpenMenu())
                    {
                        event.accept = true;
                        takeKeyFocus();
                        _setCurrent(static_cast<int>(p.buttons.size()) - 1);
                    }
                    break;
                case Key::Enter:
                    if (p.current >= 0 && p.current < p.menus.size())
                    {
                        event.accept = true;
                        takeKeyFocus();
                        _openMenu(p.current);
                    }
                    break;
                case Key::Escape:
                    if (hasKeyFocus())
                    {
                        event.accept = true;
                        releaseKeyFocus();
                    }
                    break;
                default: break;
                }
            }
            if (!event.accept)
            {
                IWidget::keyPressEvent(event);
            }
        }

        void MenuBar::keyReleaseEvent(KeyEvent& event)
        {
            IWidget::keyReleaseEvent(event);
            event.accept = true;
        }

        void MenuBar::_setCurrent(int value)
        {
            TG_P();
            const int tmp = clamp(value, 0, static_cast<int>(p.buttons.size()) - 1);
            if (tmp == p.current)
                return;
            p.current = tmp;
            _currentUpdate();
            if (auto openMenu = _getOpenMenu())
            {
                openMenu->close();
                _openMenu(p.current);
            }
        }

        void MenuBar::_currentUpdate()
        {
            TG_P();
            const bool focus = hasKeyFocus();
            for (int i = 0; i < p.buttons.size(); ++i)
            {
                p.buttons[i]->setCurrent(p.current == i && focus);
            }
        }

        std::shared_ptr<Menu> MenuBar::_getOpenMenu() const
        {
            TG_P();
            std::shared_ptr<Menu> out;
            for (auto& menu : p.menus)
            {
                if (menu->isOpen())
                {
                    out = menu;
                    break;
                }
            }
            return out;
        }

        void MenuBar::_openMenu(int value)
        {
            TG_P();
            if (value >= 0 && value < p.buttons.size())
            {
                auto menu = p.menus[value];
                auto openMenu = _getOpenMenu();
                if (menu != openMenu)
                {
                    if (openMenu)
                    {
                        openMenu->close();
                    }
                    menu->open(getWindow(), p.buttons[value]->getGeometry());
                }
            }
        }
    }
}
