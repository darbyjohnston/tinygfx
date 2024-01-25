// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ToolTip.h>

#include <tgUI/DrawUtil.h>
#include <tgUI/IWindow.h>
#include <tgUI/Label.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct ToolTip::Private
        {
            V2I pos;

            std::shared_ptr<Label> label;

            struct SizeData
            {
                bool sizeInit = true;
                int border = 0;
                int handle = 0;
                int shadow = 0;
            };
            SizeData size;
        };

        void ToolTip::_init(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const V2I& pos,
            const std::shared_ptr<IWidget>& window)
        {
            IPopup::_init(context, "tg::ui::ToolTip", nullptr);
            TG_P();

            p.pos = pos;

            p.label = Label::create(context, shared_from_this());
            p.label->setText(text);
            p.label->setTextRole(ColorRole::ToolTipText);
            p.label->setMarginRole(SizeRole::MarginSmall);

            setParent(window);
        }

        ToolTip::ToolTip() :
            _p(new Private)
        {}

        ToolTip::~ToolTip()
        {}

        std::shared_ptr<ToolTip> ToolTip::create(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const V2I& pos,
            const std::shared_ptr<IWidget>& window)
        {
            auto out = std::shared_ptr<ToolTip>(new ToolTip);
            out->_init(context, text, pos, window);
            return out;
        }

        void ToolTip::close()
        {
            setParent(nullptr);
        }

        void ToolTip::setGeometry(const Box2I& value)
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
        }

        void ToolTip::sizeHintEvent(const SizeHintEvent& event)
        {
            const bool displayScaleChanged = event.displayScale != _displayScale;
            IPopup::sizeHintEvent(event);
            TG_P();

            if (displayScaleChanged || p.size.sizeInit)
            {
                p.size.border = event.style->getSizeRole(SizeRole::Border, _displayScale);
                p.size.handle = event.style->getSizeRole(SizeRole::Handle, _displayScale);
                p.size.shadow = event.style->getSizeRole(SizeRole::Shadow, _displayScale);
            }
            p.size.sizeInit = false;
        }

        void ToolTip::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IPopup::drawEvent(drawRect, event);
            TG_P();
            //event.render->drawRect(
            //    _geometry,
            //    Color4F(0.F, 0.F, 0.F, .2F));
            const Box2I g = p.label->getGeometry();
            const Box2I g2(
                g.min.x - p.size.shadow,
                g.min.y,
                g.w() + p.size.shadow * 2,
                g.h() + p.size.shadow);
            event.render->drawColorMesh(
                shadow(g2, p.size.shadow),
                Color4F(1.F, 1.F, 1.F));

            event.render->drawMesh(
                border(margin(g, p.size.border), p.size.border),
                event.style->getColorRole(ColorRole::Border));
                
            event.render->drawRect(
                Box2F(g.x(), g.y(), g.w(), g.h()),
                event.style->getColorRole(ColorRole::ToolTipWindow));
        }
    }
}
