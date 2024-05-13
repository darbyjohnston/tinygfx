// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ComboBoxPrivate.h>

#include <tgUI/DrawUtil.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct ComboBoxButton::Private
        {
            bool current = false;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int margin = 0;
                int spacing = 0;
                int border = 0;
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

        void ComboBoxButton::_init(
            const std::shared_ptr<Context>& context,
            const ComboBoxItem& item,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::ComboBoxButton", parent);
            TG_P();
            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);
            setText(item.text);
            setIcon(item.icon);
            setButtonRole(ColorRole::None);
        }

        ComboBoxButton::ComboBoxButton() :
            _p(new Private)
        {}

        ComboBoxButton::~ComboBoxButton()
        {}

        std::shared_ptr<ComboBoxButton> ComboBoxButton::create(
            const std::shared_ptr<Context>& context,
            const ComboBoxItem& item,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ComboBoxButton>(new ComboBoxButton);
            out->_init(context, item, parent);
            return out;
        }

        void ComboBoxButton::setCurrent(bool value)
        {
            TG_P();
            if (p.current == value)
                return;
            p.current = value;
            _setDrawUpdate();
        }

        void ComboBoxButton::sizeHintEvent(const SizeHintEvent& event)
        {
            IButton::sizeHintEvent(event);
            TG_P();
            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, p.size.displayScale);
                p.size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, p.size.displayScale);
                p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);

                p.size.fontInfo = event.style->getFontRole(FontRole::Label, event.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
                p.size.textSize = event.fontSystem->getSize(_text, p.size.fontInfo);
                p.draw.glyphs.clear();
            }

            Size2I sizeHint;
            if (!_text.empty())
            {
                sizeHint.w = p.size.textSize.w + p.size.margin * 2;
                sizeHint.h = p.size.fontMetrics.lineHeight;
            }
            if (_iconImage)
            {
                if (!_text.empty())
                {
                    sizeHint.w += p.size.spacing;
                }
                V2I size;
                if (_iconImage)
                {
                    size.x = std::max(size.x, _iconImage->getWidth());
                    size.y = std::max(size.y, _iconImage->getHeight());
                }
                sizeHint.w += size.x;
                sizeHint.h = std::max(sizeHint.h, size.y);
            }
            sizeHint = margin(sizeHint, p.size.margin + p.size.border);
            _setSizeHint(sizeHint);
        }

        void ComboBoxButton::clipEvent(const Box2I& clipRect, bool clipped)
        {
            IButton::clipEvent(clipRect, clipped);
            TG_P();
            if (clipped)
            {
                p.draw.glyphs.clear();
            }
        }

        void ComboBoxButton::drawEvent(const Box2I& drawRect, const DrawEvent& event)
        {
            IButton::drawEvent(drawRect, event);
            TG_P();

            const Box2I& g = getGeometry();

            // Draw the background.
            const ColorRole colorRole = _checked ? _checkedRole : _buttonRole;
            if (colorRole != ColorRole::None)
            {
                event.render->drawRect(
                    Box2F(g.x(), g.y(), g.w(), g.h()),
                    event.style->getColorRole(colorRole));
            }

            // Draw the mouse state.
            if (_isMousePressed())
            {
                event.render->drawRect(
                    Box2F(g.x(), g.y(), g.w(), g.h()),
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (_isMouseInside())
            {
                event.render->drawRect(
                    Box2F(g.x(), g.y(), g.w(), g.h()),
                    event.style->getColorRole(ColorRole::Hover));
            }

            // Draw the current state.
            if (p.current)
            {
                event.render->drawMesh(
                    border(g, p.size.border),
                    event.style->getColorRole(ColorRole::KeyFocus));
            }

            // Draw the icon.
            const Box2I g2 = margin(g, -(p.size.margin + p.size.border));
            int x = g2.x();
            if (_iconImage)
            {
                const Size2I& iconSize = _iconImage->getSize();
                event.render->drawImage(
                    _iconImage,
                    Box2F(
                        x,
                        g2.y() + g2.h() / 2 - iconSize.h / 2,
                        iconSize.w,
                        iconSize.h),
                    event.style->getColorRole(ColorRole::Text));
                x += iconSize.w + p.size.spacing;
            }

            // Draw the text.
            if (!_text.empty())
            {
                if (p.draw.glyphs.empty())
                {
                    p.draw.glyphs = event.fontSystem->getGlyphs(_text, p.size.fontInfo);
                }
                const V2F pos(
                    x + p.size.margin,
                    g2.y() + g2.h() / 2 - p.size.textSize.h / 2);
                event.render->drawText(
                    p.draw.glyphs,
                    p.size.fontMetrics,
                    pos,
                    event.style->getColorRole(ColorRole::Text));
            }
        }
    }
}
