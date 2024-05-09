// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ComboBoxPrivate.h>

#include <tgUI/ScrollWidget.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct ComboBoxMenu::Private
        {
            std::shared_ptr<ComboBoxWidget> widget;
            std::shared_ptr<ValueObserver<int> > currentObserver;
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

            p.widget = ComboBoxWidget::create(context, items, currentIndex, parent);
            setWidget(p.widget);

            p.currentObserver = ValueObserver<int>::create(
                p.widget->observeCurrent(),
                [this](int value)
                {
                    if (value >= 0)
                    {
                        const Box2I r = _p->widget->getRect(value);
                        _getScrollWidget()->scrollTo(r);
                    }
                });
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

        void ComboBoxMenu::setCallback(const std::function<void(int)>& value)
        {
            _p->widget->setCallback(value);
        }

        void ComboBoxMenu::setGeometry(const Box2I& value)
        {
            IMenuPopup::setGeometry(value);
            TG_P();
            if (p.scrollInit)
            {
                p.scrollInit = false;
                const Box2I r = p.widget->getRect(p.widget->getCurrent());
                _getScrollWidget()->scrollTo(r);
            }
        }
    }
}
