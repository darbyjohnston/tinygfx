// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ScrollArea.h>

#include <tgUI/DrawUtil.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct ScrollArea::Private
        {
            ScrollType scrollType = ScrollType::Both;
            V2I scrollSize;
            V2I scrollPos;
            std::function<void(const V2I&)> scrollSizeCallback;
            std::function<void(const V2I&)> scrollPosCallback;
            bool border = true;

            struct SizeData
            {
                bool sizeInit = true;
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

        const V2I& ScrollArea::getScrollSize() const
        {
            return _p->scrollSize;
        }

        void ScrollArea::setScrollSizeCallback(const std::function<void(const V2I&)>& value)
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
                const Box2I g = margin(_geometry, -p.size.border);
                tmp = V2I(
                    core::clamp(tmp.x, 0, std::max(0, p.scrollSize.x - g.w())),
                    core::clamp(tmp.y, 0, std::max(0, p.scrollSize.y - g.h())));
            }
            if (tmp == p.scrollPos)
                return;
            p.scrollPos = tmp;
            _updates |= Update::Size;
            _updates |= Update::Draw;
            if (p.scrollPosCallback)
            {
                p.scrollPosCallback(p.scrollPos);
            }
        }

        void ScrollArea::setScrollPosCallback(const std::function<void(const V2I&)>& value)
        {
            _p->scrollPosCallback = value;
        }

        Box2I ScrollArea::getChildrenClipRect() const
        {
            TG_P();
            return margin(_geometry, -p.size.border);
        }

        void ScrollArea::setBorder(bool value)
        {
            TG_P();
            if (value == p.border)
                return;
            p.border = value;
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        void ScrollArea::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            TG_P();
            const Box2I g = margin(value, -p.size.border);

            V2I scrollSize;
            for (const auto& child : _children)
            {
                Size2I sizeHint = child->getSizeHint();
                switch (p.scrollType)
                {
                case ScrollType::Horizontal:
                    sizeHint.h = std::max(sizeHint.h, g.h());
                    break;
                case ScrollType::Vertical:
                case ScrollType::Menu:
                    sizeHint.w = std::max(sizeHint.w, g.w());
                    break;
                case ScrollType::Both:
                    sizeHint.w = std::max(sizeHint.w, g.w());
                    sizeHint.h = std::max(sizeHint.h, g.h());
                    break;
                default: break;
                }
                scrollSize.x = std::max(scrollSize.x, sizeHint.w);
                scrollSize.y = std::max(scrollSize.y, sizeHint.h);
                const Box2I g2(
                    g.min.x - p.scrollPos.x,
                    g.min.y - p.scrollPos.y,
                    sizeHint.w,
                    sizeHint.h);
                child->setGeometry(g2);
            }
            if (scrollSize != p.scrollSize)
            {
                p.scrollSize = scrollSize;
                _updates |= Update::Size;
                _updates |= Update::Draw;
                if (p.scrollSizeCallback)
                {
                    p.scrollSizeCallback(p.scrollSize);
                }
            }

            const V2I scrollPos(
                clamp(p.scrollPos.x, 0, std::max(0, p.scrollSize.x - g.w())),
                clamp(p.scrollPos.y, 0, std::max(0, p.scrollSize.y - g.h())));
            if (scrollPos != p.scrollPos)
            {
                p.scrollPos = scrollPos;
                _updates |= Update::Size;
                _updates |= Update::Draw;
                if (p.scrollPosCallback)
                {
                    p.scrollPosCallback(p.scrollPos);
                }
            }
        }

        void ScrollArea::sizeHintEvent(const SizeHintEvent& event)
        {
            const bool displayScaleChanged = event.displayScale != _displayScale;
            IWidget::sizeHintEvent(event);
            TG_P();

            if (displayScaleChanged || p.size.sizeInit)
            {
                p.size.size = event.style->getSizeRole(SizeRole::ScrollArea, _displayScale);
                p.size.border = p.border ?
                    event.style->getSizeRole(SizeRole::Border, _displayScale) :
                    0;
            }
            p.size.sizeInit = false;

            _sizeHint = Size2I();
            for (const auto& child : _children)
            {
                const Size2I& sizeHint = child->getSizeHint();
                _sizeHint.w = std::max(_sizeHint.w, sizeHint.w);
                _sizeHint.h = std::max(_sizeHint.h, sizeHint.h);
            }
            switch (p.scrollType)
            {
                case ScrollType::Horizontal:
                    _sizeHint.w = p.size.size;
                    break;
                case ScrollType::Vertical:
                    _sizeHint.h = p.size.size;
                    break;
                case ScrollType::Both:
                    _sizeHint.w = _sizeHint.h = p.size.size;
                    break;
                default: break;
            }
            _sizeHint.w += p.size.border * 2;
            _sizeHint.h += p.size.border * 2;
        }

        void ScrollArea::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();
            const Box2I& g = _geometry;
            if (p.border)
            {
                event.render->drawMesh(
                    border(g, p.size.border),
                    event.style->getColorRole(ColorRole::Border));
            }
        }
    }
}
