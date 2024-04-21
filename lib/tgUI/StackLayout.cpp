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
                bool init = true;
                float displayScale = 0.F;
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
            const auto& children = getChildren();
            for (auto i = children.begin(); i != children.end(); ++i, ++index)
            {
                if (value == *i)
                {
                    setCurrentIndex(index);
                    break;
                }
            }
        }

        SizeRole StackLayout::getMarginRole() const
        {
            return _p->marginRole;
        }

        void StackLayout::setMarginRole(SizeRole value)
        {
            TG_P();
            if (value == p.marginRole)
                return;
            p.marginRole = value;
            p.size.init = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void StackLayout::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            TG_P();
            const Box2I g = margin(getGeometry(), -p.size.margin);
            for (const auto& child : getChildren())
            {
                child->setGeometry(g);
            }
        }

        Box2I StackLayout::getChildrenClipRect() const
        {
            return margin(getGeometry(), -_p->size.margin);
        }

        void StackLayout::childAddedEvent(const ChildEvent& event)
        {
            _widgetUpdate();
        }

        void StackLayout::childRemovedEvent(const ChildEvent& event)
        {
            TG_P();
            p.currentIndex = clamp(
                p.currentIndex,
                0,
                static_cast<int>(getChildren().size()) - 1);
            _widgetUpdate();
        }

        void StackLayout::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();

            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.margin = event.style->getSizeRole(p.marginRole, p.size.displayScale);
            }

            Size2I sizeHint;
            for (const auto& child : getChildren())
            {
                const Size2I& childSizeHint = child->getSizeHint();
                sizeHint.w = std::max(sizeHint.w, childSizeHint.w);
                sizeHint.h = std::max(sizeHint.h, childSizeHint.h);
            }
            sizeHint.w += p.size.margin * 2;
            sizeHint.h += p.size.margin * 2;
            _setSizeHint(sizeHint);
        }

        std::shared_ptr<IWidget> StackLayout::_getCurrentWidget() const
        {
            TG_P();
            std::shared_ptr<IWidget> out;
            int i = 0;
            for (const auto& child : getChildren())
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
            for (const auto& child : getChildren())
            {
                child->setVisible(child == currentWidget);
            }
            _setSizeUpdate();
            _setDrawUpdate();
        }
    }
}
