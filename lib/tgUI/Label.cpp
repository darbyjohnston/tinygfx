// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Label.h>

#include <tgUI/LayoutUtil.h>

#include <tgCore/String.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct Label::Private
        {
            std::string text;
            ColorRole textRole = ColorRole::Text;
            SizeRole marginRole = SizeRole::None;
            FontRole fontRole = FontRole::Label;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int margin = 0;

                bool textInit = true;
                FontInfo fontInfo;
                FontMetrics fontMetrics;
                Size2I textSize;
            };
            SizeData size;

            struct DrawData
            {
                std::vector<std::shared_ptr<Glyph> > glyphs;
            };
            DrawData draw;
        };

        void Label::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::Label", parent);
            setHAlign(HAlign::Left);
        }

        Label::Label() :
            _p(new Private)
        {}

        Label::~Label()
        {}

        std::shared_ptr<Label> Label::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<Label>(new Label);
            out->_init(context, parent);
            return out;
        }

        std::shared_ptr<Label> Label::create(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = create(context, parent);
            out->setText(text);
            return out;
        }

        const std::string& Label::getText() const
        {
            return _p->text;
        }

        void Label::setText(const std::string& value)
        {
            TG_P();
            if (value == p.text)
                return;
            p.text = value;
            p.size.textInit = true;
            p.draw.glyphs.clear();
            _setSizeUpdate();
            _setDrawUpdate();
        }
        
        ColorRole Label::getTextRole() const
        {
            return _p->textRole;
        }

        void Label::setTextRole(ColorRole value)
        {
            TG_P();
            if (value == p.textRole)
                return;
            p.textRole = value;
            _setDrawUpdate();
        }

        SizeRole Label::getMarginRole() const
        {
            return _p->marginRole;
        }

        void Label::setMarginRole(SizeRole value)
        {
            TG_P();
            if (value == p.marginRole)
                return;
            p.marginRole = value;
            p.size.init = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        FontRole Label::getFontRole() const
        {
            return _p->fontRole;
        }

        void Label::setFontRole(FontRole value)
        {
            TG_P();
            if (value == p.fontRole)
                return;
            p.fontRole = value;
            p.size.textInit = true;
            p.draw.glyphs.clear();
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void Label::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();
            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.margin = event.style->getSizeRole(p.marginRole, event.displayScale);
            }
            if (p.size.textInit || displayScaleChanged)
            {
                p.size.textInit = false;
                p.size.fontInfo = event.style->getFontRole(p.fontRole, event.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
                p.size.textSize = event.fontSystem->getSize(p.text, p.size.fontInfo);
                p.draw.glyphs.clear();
            }
            _setSizeHint(Size2I(
                p.size.textSize.w +
                p.size.margin * 2,
                p.size.textSize.h +
                p.size.margin * 2));
        }

        void Label::clipEvent(const Box2I& clipRect, bool clipped)
        {
            IWidget::clipEvent(clipRect, clipped);
            TG_P();
            if (clipped)
            {
                p.draw.glyphs.clear();
            }
        }

        void Label::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();

            //event.render->drawRect(_geometry, Color4F(.5F, .3F, .3F));

            const Box2I g = margin(align(
                getGeometry(),
                getSizeHint(),
                Stretch::Fixed,
                Stretch::Fixed,
                getHAlign(),
                getVAlign()),
                -p.size.margin);

            if (!p.text.empty() && p.draw.glyphs.empty())
            {
                p.draw.glyphs = event.fontSystem->getGlyphs(p.text, p.size.fontInfo);
            }
            event.render->drawText(
                p.draw.glyphs,
                p.size.fontMetrics,
                V2F(g.min.x, g.min.y),
                event.style->getColorRole(p.textRole));
        }
    }
}
