// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/RowLayout.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct RowLayout::Private
        {
            Orientation orientation = Orientation::Horizontal;
            SizeRole marginRole = SizeRole::None;
            SizeRole spacingRole = SizeRole::Spacing;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int margin = 0;
                int spacing = 0;
            };
            SizeData size;
        };

        void RowLayout::_init(
            const std::shared_ptr<Context>& context,
            Orientation orientation,
            const std::string& objectName,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, objectName, parent);
            TG_P();
            p.orientation = orientation;
        }

        RowLayout::RowLayout() :
            _p(new Private)
        {}

        RowLayout::~RowLayout()
        {}

        std::shared_ptr<RowLayout> RowLayout::create(
            const std::shared_ptr<Context>& context,
            Orientation orientation,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<RowLayout>(new RowLayout);
            out->_init(context, orientation, "tg::ui::RowLayout", parent);
            return out;
        }

        SizeRole RowLayout::getMarginRole() const
        {
            return _p->marginRole;
        }

        void RowLayout::setMarginRole(SizeRole value)
        {
            TG_P();
            if (value == p.marginRole)
                return;
            p.marginRole = value;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        SizeRole RowLayout::getSpacingRole() const
        {
            return _p->spacingRole;
        }

        void RowLayout::setSpacingRole(SizeRole value)
        {
            TG_P();
            if (value == p.spacingRole)
                return;
            p.spacingRole = value;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void RowLayout::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            TG_P();
            const Box2I g = margin(getGeometry(), -p.size.margin);
            std::vector<Size2I> sizeHints;
            size_t expanding = 0;
            std::shared_ptr<IWidget> lastVisibleChild;
            const auto& children = getChildren();
            for (const auto& child : children)
            {
                if (child->isVisible(false))
                {
                    sizeHints.push_back(child->getSizeHint());
                    switch (p.orientation)
                    {
                    case Orientation::Horizontal:
                        if (Stretch::Expanding == child->getHStretch())
                        {
                            ++expanding;
                        }
                        break;
                    case Orientation::Vertical:
                        if (Stretch::Expanding == child->getVStretch())
                        {
                            ++expanding;
                        }
                        break;
                    default: break;
                    }
                    lastVisibleChild = child;
                }
            }
            const std::pair<int, int> extra(
                getGeometry().w() - getSizeHint().w,
                getGeometry().h() - getSizeHint().h);
            V2I pos = g.min;
            size_t count = 0;
            for (const auto& child : children)
            {
                if (child->isVisible(false))
                {
                    Size2I size = sizeHints[count];
                    switch (p.orientation)
                    {
                    case Orientation::Horizontal:
                        size.h = g.h();
                        if (expanding > 0 && Stretch::Expanding == child->getHStretch())
                        {
                            size.w += extra.first / expanding;
                            if (child == lastVisibleChild)
                            {
                                size.w += extra.first - (extra.first / expanding * expanding);
                            }
                        }
                        break;
                    case Orientation::Vertical:
                        size.w = g.w();
                        if (expanding > 0 && Stretch::Expanding == child->getVStretch())
                        {
                            size.h += extra.second / expanding;
                            if (child == lastVisibleChild)
                            {
                                size.h += extra.second - (extra.second / expanding * expanding);
                            }
                        }
                        break;
                    default: break;
                    }
                    child->setGeometry(Box2I(pos, size));
                    switch (p.orientation)
                    {
                    case Orientation::Horizontal:
                        pos.x += size.w;
                        if (sizeHints[count].w > 0)
                        {
                            for (size_t i = count + 1; i < sizeHints.size(); ++i)
                            {
                                if (sizeHints[i].w > 0)
                                {
                                    pos.x += p.size.spacing;
                                    break;
                                }
                            }
                        }
                        break;
                    case Orientation::Vertical:
                        pos.y += size.h;
                        if (sizeHints[count].h > 0)
                        {
                            for (size_t i = count + 1; i < sizeHints.size(); ++i)
                            {
                                if (sizeHints[i].h > 0)
                                {
                                    pos.y += p.size.spacing;
                                    break;
                                }
                            }
                        }
                        break;
                    default: break;
                    }
                    ++count;
                }
            }
        }

        Box2I RowLayout::getChildrenClipRect() const
        {
            return margin(getGeometry(), -_p->size.margin);
        }

        void RowLayout::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();

            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.margin = event.style->getSizeRole(p.marginRole, p.size.displayScale);
                p.size.spacing = event.style->getSizeRole(p.spacingRole, p.size.displayScale);
            }

            Size2I sizeHint;
            std::vector<Size2I> sizeHints;
            size_t visible = 0;
            for (const auto& child : getChildren())
            {
                if (child->isVisible(false))
                {
                    const Size2I& childSizeHint = child->getSizeHint();
                    sizeHints.push_back(childSizeHint);
                    switch (p.orientation)
                    {
                    case Orientation::Horizontal:
                        sizeHint.w += childSizeHint.w;
                        sizeHint.h = std::max(sizeHint.h, childSizeHint.h);
                        if (sizeHint.w > 0)
                        {
                            ++visible;
                        }
                        break;
                    case Orientation::Vertical:
                        sizeHint.w = std::max(sizeHint.w, childSizeHint.w);
                        sizeHint.h += childSizeHint.h;
                        if (sizeHint.h > 0)
                        {
                            ++visible;
                        }
                        break;
                    default: break;
                    }
                }
            }
            if (visible > 0)
            {
                switch (p.orientation)
                {
                case Orientation::Horizontal:
                    sizeHint.w += p.size.spacing * (visible - 1);
                    break;
                case Orientation::Vertical:
                    sizeHint.h += p.size.spacing * (visible - 1);
                    break;
                default: break;
                }
            }
            sizeHint.w += p.size.margin * 2;
            sizeHint.h += p.size.margin * 2;
            _setSizeHint(sizeHint);
        }

        void RowLayout::childAddedEvent(const ChildEvent&)
        {
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void RowLayout::childRemovedEvent(const ChildEvent&)
        {
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void HorizontalLayout::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            RowLayout::_init(
                context,
                Orientation::Horizontal,
                "tg::ui::HorizontalLayout",
                parent);
        }

        HorizontalLayout::HorizontalLayout()
        {}

        HorizontalLayout::~HorizontalLayout()
        {}

        std::shared_ptr<HorizontalLayout> HorizontalLayout::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<HorizontalLayout>(new HorizontalLayout);
            out->_init(context, parent);
            return out;
        }

        void VerticalLayout::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            RowLayout::_init(
                context,
                Orientation::Vertical,
                "tg::ui::VerticalLayout",
                parent);
        }

        VerticalLayout::VerticalLayout()
        {}

        VerticalLayout::~VerticalLayout()
        {}

        std::shared_ptr<VerticalLayout> VerticalLayout::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<VerticalLayout>(new VerticalLayout);
            out->_init(context, parent);
            return out;
        }
    }
}
