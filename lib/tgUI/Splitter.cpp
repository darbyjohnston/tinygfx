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
                bool init = true;
                float displayScale = 0.F;
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
            setStretch(Stretch::Expanding);
            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);
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
            _setSizeUpdate();
            _setDrawUpdate();
        }

        SizeRole Splitter::getSpacingRole() const
        {
            return _p->spacingRole;
        }

        void Splitter::setSpacingRole(SizeRole value)
        {
            TG_P();
            if (value == p.spacingRole)
                return;
            p.spacingRole = value;
            p.size.init = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void Splitter::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            TG_P();

            const Box2I& g = getGeometry();

            std::vector<bool> childVisible;
            const auto& children = getChildren();
            for (const auto& child : children)
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
                if (children.size() > 1 &&
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
                    for (size_t i = 0; i < children.size(); ++i)
                    {
                        childGeometry.push_back(Box2I(x, y, g.w(), g.h()));
                    }
                }
                break;
            case Orientation::Vertical:
                if (children.size() > 1 &&
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
                    for (size_t i = 0; i < children.size(); ++i)
                    {
                        childGeometry.push_back(Box2I(x, y, g.w(), g.h()));
                    }
                }
                break;
            default: break;
            }

            size_t i = 0;
            for (auto child : children)
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
            IWidget::sizeHintEvent(event);
            TG_P();

            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.size = event.style->getSizeRole(SizeRole::ScrollArea, p.size.displayScale);
                p.size.spacing = event.style->getSizeRole(p.spacingRole, p.size.displayScale);
                p.size.handle = event.style->getSizeRole(SizeRole::HandleSmall, p.size.displayScale);
            }

            _setSizeHint(Size2I(p.size.size, p.size.size));
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
                    convert(handle),
                    event.style->getColorRole(ColorRole::Button));
            }
            if (p.mouse.pressedHandle >= 0 &&
                p.mouse.pressedHandle < p.size.handleGeometry.size())
            {
                const Box2I g = p.size.handleGeometry[p.mouse.pressedHandle];
                event.render->drawRect(
                    convert(g),
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (p.mouse.hoverHandle >= 0 &&
                p.mouse.hoverHandle < p.size.handleGeometry.size())
            {
                const Box2I g = p.size.handleGeometry[p.mouse.hoverHandle];
                event.render->drawRect(
                    convert(g),
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
                _setDrawUpdate();
            }
        }

        void Splitter::mouseMoveEvent(MouseMoveEvent& event)
        {
            TG_P();
            event.accept = true;
            if (p.mouse.pressedHandle != -1)
            {
                const Box2I& g = getGeometry();
                float split = 0.F;
                switch (p.orientation)
                {
                case Orientation::Horizontal:
                    split = (event.pos.x - g.min.x) / static_cast<float>(g.w());
                    break;
                case Orientation::Vertical:
                    split = (event.pos.y - g.min.y) / static_cast<float>(g.h());
                    break;
                default: break;
                }
                split = clamp(split, .1F, .9F);
                if (split != p.split)
                {
                    p.split = split;
                    _setSizeUpdate();
                    _setDrawUpdate();
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
                    _setDrawUpdate();
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
                    _setDrawUpdate();
                    break;
                }
            }
        }

        void Splitter::mouseReleaseEvent(MouseClickEvent& event)
        {
            TG_P();
            event.accept = true;
            p.mouse.pressedHandle = -1;
            _setDrawUpdate();
        }

        void Splitter::_releaseMouse()
        {
            IWidget::_releaseMouse();
            TG_P();
            if (p.mouse.hoverHandle || p.mouse.pressedHandle)
            {
                p.mouse.hoverHandle = -1;
                p.mouse.pressedHandle = -1;
                _setDrawUpdate();
            }
        }
    }
}
