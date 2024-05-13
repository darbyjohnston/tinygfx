// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ScrollArea.h>

#include <tgUI/DrawUtil.h>

#include <tgCore/Error.h>
#include <tgCore/String.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        TG_ENUM_IMPL(
            ScrollType,
            "Both",
            "Horizontal",
            "Vertical",
            "Menu");

        struct ScrollArea::Private
        {
            ScrollType scrollType = ScrollType::Both;
            Size2I scrollSize;
            V2I scrollPos;
            std::function<void(const Size2I&)> scrollSizeCallback;
            std::function<void(const V2I&)> scrollPosCallback;
            bool border = true;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int size = 0;
                int border = 0;
            };
            SizeData size;
        };

        void ScrollArea::_init(
            const std::shared_ptr<Context>& context,
            ScrollType scrollType,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::ScrollArea", parent);
            TG_P();
            p.scrollType = scrollType;
        }

        ScrollArea::ScrollArea() :
            _p(new Private)
        {}

        ScrollArea::~ScrollArea()
        {}

        std::shared_ptr<ScrollArea> ScrollArea::create(
            const std::shared_ptr<Context>& context,
            ScrollType scrollType,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ScrollArea>(new ScrollArea);
            out->_init(context, scrollType, parent);
            return out;
        }

        const Size2I& ScrollArea::getScrollSize() const
        {
            return _p->scrollSize;
        }

        void ScrollArea::setScrollSizeCallback(const std::function<void(const Size2I&)>& value)
        {
            _p->scrollSizeCallback = value;
        }

        const V2I& ScrollArea::getScrollPos() const
        {
            return _p->scrollPos;
        }

        void ScrollArea::setScrollPos(const V2I& value, bool clamp)
        {
            TG_P();
            V2I tmp = value;
            if (clamp)
            {
                const Box2I g = margin(getGeometry(), -p.size.border);
                tmp = V2I(
                    core::clamp(tmp.x, 0, std::max(0, p.scrollSize.w - g.w())),
                    core::clamp(tmp.y, 0, std::max(0, p.scrollSize.h - g.h())));
            }
            if (tmp == p.scrollPos)
                return;
            p.scrollPos = tmp;
            _setSizeUpdate();
            _setDrawUpdate();
            if (p.scrollPosCallback)
            {
                p.scrollPosCallback(p.scrollPos);
            }
        }
        
        void ScrollArea::scrollTo(const Box2I& value)
        {
            TG_P();
            const Size2I size = getChildrenClipRect().size();
            V2I scrollPos = _p->scrollPos;
            if (value.min.x < scrollPos.x)
            {
                scrollPos.x = value.min.x;
            }
            else if (value.max.x > scrollPos.x + size.w)
            {
                scrollPos.x = value.max.x - size.w + 1;
            }
            if (value.min.y < scrollPos.y)
            {
                scrollPos.y = value.min.y;
            }
            else if (value.max.y > scrollPos.y + size.h)
            {
                scrollPos.y = value.max.y - size.h + 1;
            }
            setScrollPos(scrollPos);
        }

        void ScrollArea::setScrollPosCallback(const std::function<void(const V2I&)>& value)
        {
            _p->scrollPosCallback = value;
        }

        Box2I ScrollArea::getChildrenClipRect() const
        {
            return margin(getGeometry(), -_p->size.border);
        }

        bool ScrollArea::hasBorder() const
        {
            return _p->border;
        }

        void ScrollArea::setBorder(bool value)
        {
            TG_P();
            if (value == p.border)
                return;
            p.border = value;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void ScrollArea::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            TG_P();
            const Box2I g = margin(value, -p.size.border);

            Size2I scrollSize;
            for (const auto& child : getChildren())
            {
                Size2I childSizeHint = child->getSizeHint();
                switch (p.scrollType)
                {
                case ScrollType::Horizontal:
                    childSizeHint.h = std::max(childSizeHint.h, g.h());
                    break;
                case ScrollType::Vertical:
                case ScrollType::Menu:
                    childSizeHint.w = std::max(childSizeHint.w, g.w());
                    break;
                case ScrollType::Both:
                    childSizeHint.w = std::max(childSizeHint.w, g.w());
                    childSizeHint.h = std::max(childSizeHint.h, g.h());
                    break;
                default: break;
                }
                scrollSize.w = std::max(scrollSize.w, childSizeHint.w);
                scrollSize.h = std::max(scrollSize.h, childSizeHint.h);
                const Box2I g2(
                    g.min.x - p.scrollPos.x,
                    g.min.y - p.scrollPos.y,
                    childSizeHint.w,
                    childSizeHint.h);
                child->setGeometry(g2);
            }
            if (scrollSize != p.scrollSize)
            {
                p.scrollSize = scrollSize;
                _setSizeUpdate();
                _setDrawUpdate();
                if (p.scrollSizeCallback)
                {
                    p.scrollSizeCallback(p.scrollSize);
                }
            }

            const V2I scrollPos(
                clamp(p.scrollPos.x, 0, std::max(0, p.scrollSize.w - g.w())),
                clamp(p.scrollPos.y, 0, std::max(0, p.scrollSize.h - g.h())));
            if (scrollPos != p.scrollPos)
            {
                p.scrollPos = scrollPos;
                _setSizeUpdate();
                _setDrawUpdate();
                if (p.scrollPosCallback)
                {
                    p.scrollPosCallback(p.scrollPos);
                }
            }
        }

        void ScrollArea::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();

            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.size = event.style->getSizeRole(SizeRole::ScrollArea, p.size.displayScale);
                p.size.border = p.border ?
                    event.style->getSizeRole(SizeRole::Border, p.size.displayScale) :
                    0;
            }

            Size2I sizeHint;
            for (const auto& child : getChildren())
            {
                const Size2I& childSizeHint = child->getSizeHint();
                sizeHint.w = std::max(sizeHint.w, childSizeHint.w);
                sizeHint.h = std::max(sizeHint.h, childSizeHint.h);
            }
            switch (p.scrollType)
            {
                case ScrollType::Horizontal:
                    sizeHint.w = p.size.size;
                    break;
                case ScrollType::Vertical:
                    sizeHint.h = p.size.size;
                    break;
                case ScrollType::Both:
                    sizeHint.w = sizeHint.h = p.size.size;
                    break;
                default: break;
            }
            sizeHint = margin(sizeHint, p.size.border);
            _setSizeHint(sizeHint);
        }

        void ScrollArea::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();
            const Box2I& g = getGeometry();
            if (p.border)
            {
                event.render->drawMesh(
                    border(g, p.size.border),
                    event.style->getColorRole(ColorRole::Border));
            }
        }
    }
}
