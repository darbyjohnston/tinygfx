// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/CheckBox.h>

#include <tgUI/DrawUtil.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct CheckBox::Private
        {
            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int margin = 0;
                int spacing = 0;
                int border = 0;

                bool textInit = true;
                FontInfo fontInfo;
                FontMetrics fontMetrics;
                Size2I textSize;
                int checkBox = 0;
            };
            SizeData size;

            struct DrawData
            {
                std::vector<std::shared_ptr<Glyph> > glyphs;
            };
            DrawData draw;
        };

        void CheckBox::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IButton::_init(context, "tg::ui::CheckBox", parent);
            setCheckable(true);
            setAcceptsKeyFocus(true);
            _buttonRole = ColorRole::None;
        }

        CheckBox::CheckBox() :
            _p(new Private)
        {}

        CheckBox::~CheckBox()
        {}

        std::shared_ptr<CheckBox> CheckBox::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<CheckBox>(new CheckBox);
            out->_init(context, parent);
            return out;
        }

        std::shared_ptr<CheckBox> CheckBox::create(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = create(context, parent);
            out->setText(text);
            return out;
        }

        void CheckBox::setText(const std::string& value)
        {
            const bool changed = value != _text;
            IButton::setText(value);
            TG_P();
            if (changed)
            {
                p.size.textInit = true;
                _setSizeUpdate();
                _setDrawUpdate();
            }
        }

        void CheckBox::setFontRole(FontRole value)
        {
            const bool changed = value != _fontRole;
            IButton::setFontRole(value);
            TG_P();
            if (changed)
            {
                p.size.textInit = true;
                _setSizeUpdate();
                _setDrawUpdate();
            }
        }

        void CheckBox::sizeHintEvent(const SizeHintEvent& event)
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
            }
            if (p.size.textInit || displayScaleChanged)
            {
                p.size.textInit = false;
                p.size.fontInfo = event.style->getFontRole(_fontRole, p.size.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
                p.size.textSize = event.fontSystem->getSize(_text, p.size.fontInfo);
                p.size.checkBox = p.size.fontMetrics.lineHeight * .8F;
                p.draw.glyphs.clear();
            }

            _setSizeHint(Size2I(
                p.size.checkBox +
                p.size.spacing +
                p.size.textSize.w + p.size.margin * 2 +
                p.size.margin * 2 +
                p.size.border * 4,
                p.size.fontMetrics.lineHeight +
                p.size.margin * 2 +
                p.size.border * 4));
        }

        void CheckBox::clipEvent(const Box2I& clipRect, bool clipped)
        {
            IButton::clipEvent(clipRect, clipped);
            TG_P();
            if (clipped)
            {
                p.draw.glyphs.clear();
            }
        }

        void CheckBox::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IButton::drawEvent(drawRect, event);
            TG_P();

            const Box2I& g = getGeometry();
            const bool enabled = isEnabled();

            if (hasKeyFocus())
            {
                event.render->drawMesh(
                    border(g, p.size.border * 2),
                    event.style->getColorRole(ColorRole::KeyFocus));
            }

            const Box2I g2 = margin(g, -p.size.border * 2);
            if (_isMousePressed() && contains(g, _getMousePos()))
            {
                event.render->drawRect(
                    Box2F(g2.x(), g2.y(), g2.w(), g2.h()),
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (_isMouseInside())
            {
                event.render->drawRect(
                    Box2F(g2.x(), g2.y(), g2.w(), g2.h()),
                    event.style->getColorRole(ColorRole::Hover));
            }

            const Box2I g3 = margin(g2, -p.size.margin);
            const Box2I checkBox(
                g3.x(),
                g3.y() + g3.h() / 2 - p.size.checkBox / 2,
                p.size.checkBox,
                p.size.checkBox);
            event.render->drawMesh(
                border(checkBox, p.size.border),
                event.style->getColorRole(ColorRole::Border));
            const Box2I g4 = margin(checkBox, -p.size.border);
            event.render->drawRect(
                Box2F(g4.x(), g4.y(), g4.w(), g4.h()),
                event.style->getColorRole(_checked ? ColorRole::Checked : ColorRole::Base ));

            if (!_text.empty())
            {
                if (p.draw.glyphs.empty())
                {
                    p.draw.glyphs = event.fontSystem->getGlyphs(_text, p.size.fontInfo);
                }
                const V2F pos(
                    g3.x() + p.size.checkBox + p.size.spacing + p.size.margin,
                    g3.y() + g3.h() / 2 - p.size.textSize.h / 2);
                event.render->drawText(
                    p.draw.glyphs,
                    p.size.fontMetrics,
                    pos,
                    event.style->getColorRole(enabled ?
                        ColorRole::Text :
                        ColorRole::TextDisabled));
            }
        }

        void CheckBox::keyPressEvent(KeyEvent& event)
        {
            TG_P();
            if (0 == event.modifiers)
            {
                switch (event.key)
                {
                case Key::Enter:
                    event.accept = true;
                    _click();
                    break;
                case Key::Escape:
                    if (hasKeyFocus())
                    {
                        event.accept = true;
                        releaseKeyFocus();
                    }
                    break;
                default: break;
                }
            }
        }

        void CheckBox::keyReleaseEvent(KeyEvent& event)
        {
            event.accept = true;
        }
    }
}
