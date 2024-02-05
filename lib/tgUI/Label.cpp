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
            std::vector<std::string> lines;
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
                std::vector<std::vector<std::shared_ptr<Glyph> > > glyphs;
            };
            DrawData draw;
        };

        void Label::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::Label", parent);
            _hAlign = HAlign::Left;
        }

        Label::Label() :
            _p(new Private)
        {}

        Label::~Label()
        {}

        std::shared_ptr<Label> Label::create(
            const std::shared_ptr<Context>&context,
            const std::shared_ptr<IWidget>&parent)
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
            auto out = std::shared_ptr<Label>(new Label);
            out->_init(context, parent);
            out->setText(text);
            return out;
        }

        void Label::setText(const std::string& value)
        {
            TG_P();
            if (value == p.text)
                return;
            p.text = value;
            p.size.textInit = true;
            p.draw.glyphs.clear();
            _textUpdate();
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        void Label::setTextRole(ColorRole value)
        {
            TG_P();
            if (value == p.textRole)
                return;
            p.textRole = value;
            _updates |= Update::Draw;
        }

        void Label::setMarginRole(SizeRole value)
        {
            TG_P();
            if (value == p.marginRole)
                return;
            p.marginRole = value;
            p.size.init = true;
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        void Label::setFontRole(FontRole value)
        {
            TG_P();
            if (value == p.fontRole)
                return;
            p.fontRole = value;
            p.size.textInit = true;
            p.draw.glyphs.clear();
            _updates |= Update::Size;
            _updates |= Update::Draw;
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
            _sizeHint.w =
                p.size.textSize.w +
                p.size.margin * 2;
            _sizeHint.h =
                p.size.textSize.h +
                p.size.margin * 2;
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
                _geometry,
                _sizeHint,
                Stretch::Fixed,
                Stretch::Fixed,
                _hAlign,
                _vAlign),
                -p.size.margin);

            if (!p.text.empty() && p.draw.glyphs.empty())
            {
                for (const auto& line : p.lines)
                {
                    p.draw.glyphs.push_back(event.fontSystem->getGlyphs(line, p.size.fontInfo));
                }
            }
            V2I pos = g.min;
            for (const auto& glyphs : p.draw.glyphs)
            {
                event.render->drawText(
                    glyphs,
                    V2F(pos.x, pos.y + p.size.fontMetrics.ascender),
                    event.style->getColorRole(p.textRole));
                pos.y += p.size.fontMetrics.lineHeight;
            }
        }
        
        void Label::_textUpdate()
        {
            TG_P();
            const auto lines = split(
                p.text,
                { '\n', '\r' },
                SplitOptions::KeepEmpty);
            p.lines.clear();
            for (const auto& line : lines)
            {
                p.lines.push_back(line);
            }
        }
    }
}
