// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/StackLayout.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct StackLayout::Private
        {
            int currentIndex = 0;
            SizeRole marginRole = SizeRole::None;

            struct SizeData
            {
                bool sizeInit = true;
                int margin = 0;
            };
            SizeData size;
        };

        void StackLayout::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::StackLayout", parent);
        }

        StackLayout::StackLayout() :
            _p(new Private)
        {}

        StackLayout::~StackLayout()
        {}

        std::shared_ptr<StackLayout> StackLayout::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<StackLayout>(new StackLayout);
            out->_init(context, parent);
            return out;
        }

        int StackLayout::getCurrentIndex() const
        {
            return _p->currentIndex;
        }

        void StackLayout::setCurrentIndex(int value)
        {
            TG_P();
            if (value == p.currentIndex)
                return;
            p.currentIndex = value;
            _widgetUpdate();
        }

        void StackLayout::setCurrentWidget(const std::shared_ptr<IWidget>& value)
        {
            int index = 0;
            for (auto i = _children.begin(); i != _children.end(); ++i, ++index)
            {
                if (value == *i)
                {
                    setCurrentIndex(index);
                    break;
                }
            }
        }

        void StackLayout::setMarginRole(SizeRole value)
        {
            TG_P();
            if (value == p.marginRole)
                return;
            p.marginRole = value;
            p.size.sizeInit = true;
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        void StackLayout::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            TG_P();
            const Box2I g = margin(_geometry, -p.size.margin);
            for (const auto& child : _children)
            {
                child->setGeometry(g);
            }
        }

        Box2I StackLayout::getChildrenClipRect() const
        {
            return margin(_geometry, -_p->size.margin);
        }

        void StackLayout::childAddedEvent(const ChildEvent& event)
        {
            _widgetUpdate();
        }

        void StackLayout::childRemovedEvent(const ChildEvent& event)
        {
            _widgetUpdate();
        }

        void StackLayout::sizeHintEvent(const SizeHintEvent& event)
        {
            const bool displayScaleChanged = event.displayScale != _displayScale;
            IWidget::sizeHintEvent(event);
            TG_P();

            if (displayScaleChanged || p.size.sizeInit)
            {
                p.size.margin = event.style->getSizeRole(p.marginRole, _displayScale);
            }
            p.size.sizeInit = false;

            _sizeHint = Size2I();
            for (const auto& child : _children)
            {
                const Size2I& sizeHint = child->getSizeHint();
                _sizeHint.w = std::max(_sizeHint.w, sizeHint.w);
                _sizeHint.h = std::max(_sizeHint.h, sizeHint.h);
            }
            _sizeHint.w += p.size.margin * 2;
            _sizeHint.h += p.size.margin * 2;
        }

        std::shared_ptr<IWidget> StackLayout::_getCurrentWidget() const
        {
            TG_P();
            std::shared_ptr<IWidget> out;
            int i = 0;
            for (const auto& child : _children)
            {
                if (i == p.currentIndex)
                {
                    out = child;
                    break;
                }
                ++i;
            }
            return out;
        }

        void StackLayout::_widgetUpdate()
        {
            const auto currentWidget = _getCurrentWidget();
            for (const auto& child : _children)
            {
                child->setVisible(child == currentWidget);
            }
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }
    }
}
