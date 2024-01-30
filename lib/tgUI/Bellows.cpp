// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Bellows.h>

#include <tgUI/Divider.h>
#include <tgUI/ListButton.h>
#include <tgUI/RowLayout.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct Bellows::Private
        {
            std::shared_ptr<ListButton> button;
            std::shared_ptr<IWidget> widget;
            std::shared_ptr<VerticalLayout> layout;
        };

        void Bellows::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::Bellows", parent);
            TG_P();

            p.button = ListButton::create(context);
            p.button->setCheckable(true);
            p.button->setIcon("BellowsClosed");
            p.button->setCheckedIcon("BellowsOpen");
            p.button->setButtonRole(ColorRole::Button);
            p.button->setCheckedRole(ColorRole::Button);

            p.layout = VerticalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::None);
            p.button->setParent(p.layout);
            Divider::create(context, Orientation::Horizontal, p.layout);

            p.button->setCheckedCallback(
                [this](bool value)
                {
                    setOpen(value);
                });
        }

        Bellows::Bellows() :
            _p(new Private)
        {}

        Bellows::~Bellows()
        {}

        std::shared_ptr<Bellows> Bellows::create(
            const std::shared_ptr<Context>&context,
            const std::shared_ptr<IWidget>&parent)
        {
            auto out = std::shared_ptr<Bellows>(new Bellows);
            out->_init(context, parent);
            return out;
        }

        std::shared_ptr<Bellows> Bellows::create(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<Bellows>(new Bellows);
            out->_init(context, parent);
            out->setText(text);
            return out;
        }

        void Bellows::setText(const std::string& value)
        {
            _p->button->setText(value);
        }

        void Bellows::setWidget(const std::shared_ptr<IWidget>& value)
        {
            TG_P();
            if (value == p.widget)
                return;
            if (p.widget)
            {
                p.widget->setParent(nullptr);
            }
            p.widget = value;
            if (p.widget)
            {
                p.widget->setParent(_p->layout);
                p.widget->setVisible(p.button->isChecked());
            }
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        bool Bellows::isOpen() const
        {
            return _p->button->isChecked();
        }

        void Bellows::setOpen(bool value)
        {
            TG_P();
            p.button->setChecked(value);
            if (p.widget)
            {
                p.widget->setVisible(value);
            }
        }

        void Bellows::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void Bellows::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _sizeHint = _p->layout->getSizeHint();
        }
    }
}