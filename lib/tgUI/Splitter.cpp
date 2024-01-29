// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Splitter.h>

#include <tgUI/LayoutUtil.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct Splitter::Private
        {
            Orientation orientation = Orientation::Horizontal;
            float split = .5F;
            SizeRole spacingRole = SizeRole::SpacingSmall;

            struct SizeData
            {
                bool sizeInit = true;
                int size = 0;
                int spacing = 0;
                int handle = 0;

                std::vector<Box2I> handleGeometry;
            };
            SizeData size;

            struct MouseData
            {
                int hoverHandle = -1;
                int pressedHandle = -1;
            };
            MouseData mouse;
        };

        void Splitter::_init(
            const std::shared_ptr<Context>& context,
            Orientation orientation,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::Splitter", parent);
            TG_P();
            _hStretch = Stretch::Expanding;
            _vStretch = Stretch::Expanding;
            _setMouseHover(true);
            _setMousePress(true);
            p.orientation = orientation;
        }

        Splitter::Splitter() :
            _p(new Private)
        {}

        Splitter::~Splitter()
        {}

        std::shared_ptr<Splitter> Splitter::create(
            const std::shared_ptr<Context>& context,
            Orientation orientation,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<Splitter>(new Splitter);
            out->_init(context, orientation, parent);
            return out;
        }

        float Splitter::getSplit() const
        {
            return _p->split;
        }

        void Splitter::setSplit(float value)
        {
            TG_P();
            if (value == p.split)
                return;
            p.split = value;
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        void Splitter::setSpacingRole(SizeRole value)
        {
            TG_P();
            if (value == p.spacingRole)
                return;
            p.spacingRole = value;
            p.size.sizeInit = true;
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        void Splitter::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            TG_P();

            const Box2I& g = _geometry;

            std::vector<bool> childVisible;
            for (const auto& child : _children)
            {
                childVisible.push_back(child->isVisible(false));
            }
            p.size.handleGeometry.clear();
            std::vector<Box2I> childGeometry;
            int x = g.x();
            int y = g.y();
            int w = 0;
            int h = 0;
            switch (p.orientation)
            {
            case Orientation::Horizontal:
                if (_children.size() > 1 &&
                    childVisible[0] &&
                    childVisible[1])
                {
                    w = g.w() * p.split - p.size.handle / 2;
                    h = g.h();
                    childGeometry.push_back(Box2I(x, y, w, h));
                    x += w;
                    x += p.size.spacing;
                    w = p.size.handle;
                    p.size.handleGeometry.push_back(Box2I(x, y, w, h));
                    x += w;
                    x += p.size.spacing;
                    w = g.x() + g.w() - x;
                    childGeometry.push_back(Box2I(x, y, w, h));
                }
                else
                {
                    for (size_t i = 0; i < _children.size(); ++i)
                    {
                        childGeometry.push_back(Box2I(x, y, g.w(), g.h()));
                    }
                }
                break;
            case Orientation::Vertical:
                if (_children.size() > 1 &&
                    childVisible[0] &&
                    childVisible[1])
                {
                    w = g.w();
                    h = g.h() * p.split - p.size.handle / 2;
                    childGeometry.push_back(Box2I(x, y, w, h));
                    y += h;
                    y += p.size.spacing;
                    h = p.size.handle;
                    p.size.handleGeometry.push_back(Box2I(x, y, w, h));
                    y += h;
                    y += p.size.spacing;
                    h = g.y() + g.h() - y;
                    childGeometry.push_back(Box2I(x, y, w, h));
                }
                else
                {
                    for (size_t i = 0; i < _children.size(); ++i)
                    {
                        childGeometry.push_back(Box2I(x, y, g.w(), g.h()));
                    }
                }
                break;
            }

            size_t i = 0;
            for (auto child : _children)
            {
                child->setGeometry(
                    i < childGeometry.size() ?
                    childGeometry[i] :
                    g);
                ++i;
            }
        }

        void Splitter::sizeHintEvent(const SizeHintEvent& event)
        {
            const bool displayScaleChanged = event.displayScale != _displayScale;
            IWidget::sizeHintEvent(event);
            TG_P();

            if (displayScaleChanged || p.size.sizeInit)
            {
                p.size.size = event.style->getSizeRole(SizeRole::ScrollArea, _displayScale);
                p.size.spacing = event.style->getSizeRole(p.spacingRole, _displayScale);
                p.size.handle = event.style->getSizeRole(SizeRole::HandleSmall, _displayScale);
            }
            p.size.sizeInit = false;

            _sizeHint.w = _sizeHint.h = p.size.size;
        }

        void Splitter::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();
            for (const auto& handle : p.size.handleGeometry)
            {
                event.render->drawRect(
                    Box2F(handle.x(), handle.y(), handle.w(), handle.h()),
                    event.style->getColorRole(ColorRole::Button));
            }
            if (p.mouse.pressedHandle >= 0 &&
                p.mouse.pressedHandle < p.size.handleGeometry.size())
            {
                const Box2I g = p.size.handleGeometry[p.mouse.pressedHandle];
                event.render->drawRect(
                    Box2F(g.x(), g.y(), g.w(), g.h()),
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (p.mouse.hoverHandle >= 0 &&
                p.mouse.hoverHandle < p.size.handleGeometry.size())
            {
                const Box2I g = p.size.handleGeometry[p.mouse.hoverHandle];
                event.render->drawRect(
                    Box2F(g.x(), g.y(), g.w(), g.h()),
                    event.style->getColorRole(ColorRole::Hover));
            }
        }

        void Splitter::mouseEnterEvent()
        {}

        void Splitter::mouseLeaveEvent()
        {
            TG_P();
            if (p.mouse.hoverHandle != -1)
            {
                p.mouse.hoverHandle = -1;
                _updates |= Update::Draw;
            }
        }

        void Splitter::mouseMoveEvent(MouseMoveEvent& event)
        {
            TG_P();
            event.accept = true;
            if (p.mouse.pressedHandle != -1)
            {
                const Box2I& g = _geometry;
                float split = 0.F;
                switch (p.orientation)
                {
                case Orientation::Horizontal:
                    split = (event.pos.x - g.min.x) / static_cast<float>(g.w());
                    break;
                case Orientation::Vertical:
                    split = (event.pos.y - g.min.y) / static_cast<float>(g.h());
                    break;
                }
                split = clamp(split, .1F, .9F);
                if (split != p.split)
                {
                    p.split = split;
                    _updates |= Update::Size;
                    _updates |= Update::Draw;
                }
            }
            else
            {
                int hoverHandle = -1;
                for (size_t i = 0; i < p.size.handleGeometry.size(); ++i)
                {
                    if (contains(p.size.handleGeometry[i], event.pos))
                    {
                        hoverHandle = i;
                        break;
                    }
                }
                if (hoverHandle != p.mouse.hoverHandle)
                {
                    p.mouse.hoverHandle = hoverHandle;
                    _updates |= Update::Draw;
                }
            }
        }

        void Splitter::mousePressEvent(MouseClickEvent& event)
        {
            TG_P();
            p.mouse.pressedHandle = -1;
            for (size_t i = 0; i < p.size.handleGeometry.size(); ++i)
            {
                if (contains(p.size.handleGeometry[i], event.pos))
                {
                    event.accept = true;
                    p.mouse.pressedHandle = i;
                    _updates |= Update::Draw;
                    break;
                }
            }
        }

        void Splitter::mouseReleaseEvent(MouseClickEvent& event)
        {
            TG_P();
            event.accept = true;
            p.mouse.pressedHandle = -1;
            _updates |= Update::Draw;
        }

        void Splitter::_releaseMouse()
        {
            IWidget::_releaseMouse();
            TG_P();
            if (p.mouse.hoverHandle || p.mouse.pressedHandle)
            {
                p.mouse.hoverHandle = -1;
                p.mouse.pressedHandle = -1;
                _updates |= Update::Draw;
            }
        }
    }
}
