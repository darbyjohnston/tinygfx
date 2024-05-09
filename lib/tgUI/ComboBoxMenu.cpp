// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ComboBoxPrivate.h>

#include <tgUI/RowLayout.h>
#include <tgUI/ScrollWidget.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct ComboBoxMenu::Private
        {
            std::vector<std::shared_ptr<ComboBoxButton> > buttons;
            int radio = -1;
            int current = -1;
            std::function<void(int)> callback;
            std::shared_ptr<VerticalLayout> layout;
            bool scrollInit = true;
        };

        void ComboBoxMenu::_init(
            const std::shared_ptr<Context>& context,
            const std::vector<ComboBoxItem>& items,
            int currentIndex,
            const std::shared_ptr<IWidget>& parent)
        {
            IMenuPopup::_init(context, "tg::ui::ComboBoxMenu", parent);
            TG_P();

            setAcceptsKeyFocus(true);

            p.layout = VerticalLayout::create(context, parent);
            p.layout->setSpacingRole(SizeRole::None);
            setWidget(p.layout);

            p.radio = currentIndex;
            p.current = currentIndex;
            for (size_t i = 0; i < items.size(); ++i)
            {
                auto button = ComboBoxButton::create(context, items[i], p.layout);
                button->setCheckable(true);
                button->setChecked(i == currentIndex);
                button->setCurrent(i == currentIndex);
                p.buttons.push_back(button);
                button->setCheckedCallback(
                    [this, i](bool value)
                    {
                        if (_p->radio >= 0 && _p->radio < _p->buttons.size())
                        {
                            _p->buttons[_p->radio]->setChecked(false);
                        }
                        _p->radio = i;
                        if (_p->radio >= 0 && _p->radio < _p->buttons.size())
                        {
                            _p->buttons[_p->radio]->setChecked(true);
                        }
                        if (_p->callback)
                        {
                            _p->callback(i);
                        }
                    });
            }
        }

        ComboBoxMenu::ComboBoxMenu() :
            _p(new Private)
        {}

        ComboBoxMenu::~ComboBoxMenu()
        {}

        std::shared_ptr<ComboBoxMenu> ComboBoxMenu::create(
            const std::shared_ptr<Context>& context,
            const std::vector<ComboBoxItem>& items,
            int currentIndex,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ComboBoxMenu>(new ComboBoxMenu);
            out->_init(context, items, currentIndex, parent);
            return out;
        }

        int ComboBoxMenu::getCurrent() const
        {
            return _p->current;
        }

        void ComboBoxMenu::setCurrent(int value)
        {
            TG_P();
            const int tmp = clamp(value, 0, static_cast<int>(p.buttons.size()) - 1);
            if (tmp == p.current)
                return;
            p.current = tmp;
            for (int i = 0; i < p.buttons.size(); ++i)
            {
                p.buttons[i]->setCurrent(p.current == i);
            }
            _scrollToCurrent();
        }

        void ComboBoxMenu::setCallback(const std::function<void(int)>& value)
        {
            _p->callback = value;
        }

        void ComboBoxMenu::setGeometry(const Box2I& value)
        {
            IMenuPopup::setGeometry(value);
            TG_P();
            if (p.scrollInit)
            {
                p.scrollInit = false;
                _scrollToCurrent();
            }
        }

        void ComboBoxMenu::keyPressEvent(KeyEvent& event)
        {
            TG_P();
            if (0 == event.modifiers)
            {
                switch (event.key)
                {
                case Key::Enter:
                    event.accept = true;
                    takeKeyFocus();
                    if (p.callback)
                    {
                        p.callback(p.current);
                    }
                    break;
                case Key::Up:
                    event.accept = true;
                    takeKeyFocus();
                    setCurrent(getCurrent() - 1);
                    break;
                case Key::Down:
                    event.accept = true;
                    takeKeyFocus();
                    setCurrent(getCurrent() + 1);
                    break;
                case Key::PageUp:
                    event.accept = true;
                    takeKeyFocus();
                    setCurrent(getCurrent() - 10);
                    break;
                case Key::PageDown:
                    event.accept = true;
                    takeKeyFocus();
                    setCurrent(getCurrent() + 10);
                    break;
                case Key::Home:
                    event.accept = true;
                    takeKeyFocus();
                    setCurrent(0);
                    break;
                case Key::End:
                    event.accept = true;
                    takeKeyFocus();
                    setCurrent(static_cast<int>(p.buttons.size()) - 1);
                    break;
                default: break;
                }
            }
            if (!event.accept)
            {
                IMenuPopup::keyPressEvent(event);
            }
        }

        void ComboBoxMenu::keyReleaseEvent(KeyEvent& event)
        {
            IMenuPopup::keyReleaseEvent(event);
            event.accept = true;
        }

        void ComboBoxMenu::_scrollToCurrent()
        {
            TG_P();
            if (p.current >= 0 && p.current < p.buttons.size())
            {
                auto button = p.buttons[p.current];
                Box2I g = button->getGeometry();
                g = move(g, -p.layout->getGeometry().min);
                _getScrollWidget()->scrollTo(g);
            }
        }
    }
}
