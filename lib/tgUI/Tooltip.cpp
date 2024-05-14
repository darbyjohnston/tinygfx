// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Tooltip.h>

#include <tgUI/DrawUtil.h>
#include <tgUI/IWindow.h>
#include <tgUI/Label.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct Tooltip::Private
        {
            V2I pos;

            std::shared_ptr<Label> label;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int border = 0;
                int handle = 0;
                int shadow = 0;
            };
            SizeData size;

            struct DrawData
            {
                Box2I g;
                Box2I g2;
            };
            DrawData draw;
        };

        void Tooltip::_init(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const V2I& pos,
            const std::shared_ptr<IWidget>& window)
        {
            IPopup::_init(context, "tg::ui::Tooltip", nullptr);
            TG_P();

            p.pos = pos;

            p.label = Label::create(context, shared_from_this());
            p.label->setText(text);
            p.label->setTextRole(ColorRole::TooltipText);
            p.label->setMarginRole(SizeRole::MarginSmall);

            setParent(window);
        }

        Tooltip::Tooltip() :
            _p(new Private)
        {}

        Tooltip::~Tooltip()
        {}

        std::shared_ptr<Tooltip> Tooltip::create(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const V2I& pos,
            const std::shared_ptr<IWidget>& window)
        {
            auto out = std::shared_ptr<Tooltip>(new Tooltip);
            out->_init(context, text, pos, window);
            return out;
        }

        void Tooltip::close()
        {
            setParent(nullptr);
        }

        void Tooltip::setGeometry(const Box2I& value)
        {
            IPopup::setGeometry(value);
            TG_P();
            Size2I sizeHint = p.label->getSizeHint();
            std::list<Box2I> boxes;
            boxes.push_back(Box2I(
                p.pos.x + p.size.handle,
                p.pos.y + p.size.handle,
                sizeHint.w,
                sizeHint.h));
            boxes.push_back(Box2I(
                p.pos.x - p.size.handle - sizeHint.w,
                p.pos.y + p.size.handle,
                sizeHint.w,
                sizeHint.h));
            boxes.push_back(Box2I(
                p.pos.x + p.size.handle,
                p.pos.y - p.size.handle - sizeHint.h,
                sizeHint.w,
                sizeHint.h));
            boxes.push_back(Box2I(
                p.pos.x - p.size.handle - sizeHint.w,
                p.pos.y - p.size.handle - sizeHint.h,
                sizeHint.w,
                sizeHint.h));
            struct Intersect
            {
                Box2I original;
                Box2I intersected;
            };
            std::vector<Intersect> intersect;
            for (const auto& box : boxes)
            {
                intersect.push_back({ box, core::intersect(box, value) });
            }
            std::stable_sort(
                intersect.begin(),
                intersect.end(),
                [](const Intersect& a, const Intersect& b)
                {
                    return
                        area(a.intersected.size()) >
                        area(b.intersected.size());
                });
            Box2I g = intersect.front().intersected;
            p.label->setGeometry(g);

            p.draw.g = g;
            p.draw.g2 = Box2I(
                g.min.x - p.size.shadow,
                g.min.y,
                g.w() + p.size.shadow * 2,
                g.h() + p.size.shadow);
        }

        void Tooltip::sizeHintEvent(const SizeHintEvent& event)
        {
            IPopup::sizeHintEvent(event);
            TG_P();
            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
                p.size.handle = event.style->getSizeRole(SizeRole::Handle, p.size.displayScale);
                p.size.shadow = event.style->getSizeRole(SizeRole::Shadow, p.size.displayScale);
            }
        }

        void Tooltip::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IPopup::drawEvent(drawRect, event);
            TG_P();
            event.render->drawColorMesh(
                shadow(p.draw.g2, p.size.shadow),
                Color4F(1.F, 1.F, 1.F));
            event.render->drawMesh(
                border(margin(p.draw.g, p.size.border), p.size.border),
                event.style->getColorRole(ColorRole::Border));
            event.render->drawRect(
                convert(p.draw.g),
                event.style->getColorRole(ColorRole::TooltipWindow));
        }
    }
}
