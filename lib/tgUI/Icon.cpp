// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Icon.h>

#include <tgUI/LayoutUtil.h>

#include <tgCore/String.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct Icon::Private
        {
            std::string icon;
            std::shared_ptr<Image> iconImage;
            float iconScale = 1.F;
            bool iconInit = false;
            std::future<std::shared_ptr<Image> > iconFuture;
            SizeRole marginRole = SizeRole::None;

            struct SizeData
            {
                bool sizeInit = true;
                int margin = 0;
            };
            SizeData size;
        };

        void Icon::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::Icon", parent);
            _hAlign = HAlign::Left;
        }

        Icon::Icon() :
            _p(new Private)
        {}

        Icon::~Icon()
        {}

        std::shared_ptr<Icon> Icon::create(
            const std::shared_ptr<Context>&context,
            const std::shared_ptr<IWidget>&parent)
        {
            auto out = std::shared_ptr<Icon>(new Icon);
            out->_init(context, parent);
            return out;
        }

        std::shared_ptr<Icon> Icon::create(
            const std::string& icon,
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<Icon>(new Icon);
            out->_init(context, parent);
            out->setIcon(icon);
            return out;
        }

        void Icon::setIcon(const std::string& value)
        {
            TG_P();
            if (value == p.icon)
                return;
            p.icon = value;
            p.iconImage.reset();
            p.iconInit = true;
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        void Icon::setMarginRole(SizeRole value)
        {
            TG_P();
            if (value == p.marginRole)
                return;
            p.marginRole = value;
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        void Icon::tickEvent(
            bool parentsVisible,
            bool parentsEnabled,
            const TickEvent& event)
        {
            IWidget::tickEvent(parentsVisible, parentsEnabled, event);
            TG_P();
            if (p.iconFuture.valid() &&
                p.iconFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                p.iconImage = p.iconFuture.get();
                _updates |= Update::Size;
                _updates |= Update::Draw;
            }
        }

        void Icon::sizeHintEvent(const SizeHintEvent& event)
        {
            const bool displayScaleChanged = event.displayScale != _displayScale;
            IWidget::sizeHintEvent(event);
            TG_P();

            if (displayScaleChanged || p.size.sizeInit)
            {
                p.size.margin = event.style->getSizeRole(p.marginRole, _displayScale);
            }
            p.size.sizeInit = false;

            if (_displayScale != p.iconScale)
            {
                p.iconImage.reset();
                p.iconScale = _displayScale;
                p.iconInit = true;
                p.iconFuture = std::future<std::shared_ptr<Image> >();
            }
            if (!p.icon.empty() && p.iconInit)
            {
                p.iconInit = false;
                p.iconFuture = event.iconLibrary->request(p.icon, _displayScale);
            }

            _sizeHint = Size2I();
            if (p.iconImage)
            {
                _sizeHint.w() = p.iconImage->getWidth();
                _sizeHint.h() = p.iconImage->getHeight();
            }
        }

        void Icon::clipEvent(const Box2I& clipRect, bool clipped)
        {
            IWidget::clipEvent(clipRect, clipped);
            TG_P();
            if (clipped)
            {
            }
        }

        void Icon::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();
            const Box2I g = margin(_geometry, -p.size.margin);
            if (p.iconImage)
            {
                const ImageSize& iconSize = p.iconImage->getSize();
                event.render->drawImage(
                    p.iconImage,
                    Box2F(
                        g.x() + g.w() / 2 - iconSize.w / 2,
                        g.y() + g.h() / 2 - iconSize.h / 2,
                        iconSize.w,
                        iconSize.h),
                    event.style->getColorRole(ColorRole::Text));
            }
        }
    }
}

