// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/MenuPrivate.h>

#include <tgUI/DrawUtil.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct MenuButton::Private
        {
            bool current = false;
            Key shortcut = Key::Unknown;
            int shortcutModifiers = 0;
            std::string shortcutText;

            float iconScale = 1.F;
            struct IconData
            {
                std::string name;
                bool init = false;
                std::future<std::shared_ptr<Image> > future;
                std::shared_ptr<Image> image;
            };
            IconData subMenuIcon;

            struct SizeData
            {
                int init = true;
                float displayScale = 0.F;
                int margin = 0;
                int spacing = 0;
                int border = 0;
                FontInfo fontInfo;
                FontMetrics fontMetrics;
                Size2I textSize;
                Size2I shortcutSize;
            };
            SizeData size;

            struct DrawData
            {
                Box2I g;
                Box2I g2;
                std::vector<std::shared_ptr<Glyph> > textGlyphs;
                std::vector<std::shared_ptr<Glyph> > shortcutGlyphs;
            };
            DrawData draw;
        };

        void MenuButton::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IButton::_init(context, "tg::ui::MenuButton", parent);
            TG_P();
            setButtonRole(ColorRole::None);
        }

        MenuButton::MenuButton() :
            _p(new Private)
        {}

        MenuButton::~MenuButton()
        {}

        std::shared_ptr<MenuButton> MenuButton::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<MenuButton>(new MenuButton);
            out->_init(context, parent);
            return out;
        }

        void MenuButton::setCurrent(bool value)
        {
            TG_P();
            if (value == p.current)
                return;
            p.current = value;
            _setDrawUpdate();
        }

        void MenuButton::setShortcut(Key key, int modifiers)
        {
            TG_P();
            if (key == p.shortcut && modifiers == p.shortcutModifiers)
                return;
            p.shortcut = key;
            p.shortcutModifiers = modifiers;
            p.shortcutText = getShortcutLabel(p.shortcut, p.shortcutModifiers);
            p.size.init = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }
        
        void MenuButton::setSubMenuIcon(const std::string& name)
        {
            TG_P();
            p.subMenuIcon.name = name;
            p.subMenuIcon.init = true;
            p.subMenuIcon.image.reset();
        }

        void MenuButton::setText(const std::string& value)
        {
            const bool changed = value != _text;
            IButton::setText(value);
            TG_P();
            if (changed)
            {
                p.size.init = true;
                _setSizeUpdate();
                _setDrawUpdate();
            }
        }

        void MenuButton::setGeometry(const Box2I& value)
        {
            IButton::setGeometry(value);
            TG_P();
            p.draw.g = value;
            p.draw.g2 = margin(p.draw.g, -(p.size.margin + p.size.border));
        }

        void MenuButton::tickEvent(
            bool parentsVisible,
            bool parentsEnabled,
            const TickEvent& event)
        {
            IButton::tickEvent(parentsVisible, parentsEnabled, event);
            TG_P();
            if (event.displayScale != p.iconScale)
            {
                p.iconScale = event.displayScale;
                p.subMenuIcon.init = true;
                p.subMenuIcon.future = std::future<std::shared_ptr<Image> >();
                p.subMenuIcon.image.reset();
            }
            if (!p.subMenuIcon.name.empty() && p.subMenuIcon.init)
            {
                p.subMenuIcon.init = false;
                p.subMenuIcon.future = event.iconLibrary->request(p.subMenuIcon.name, p.iconScale);
            }
            if (p.subMenuIcon.future.valid() &&
                p.subMenuIcon.future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                p.subMenuIcon.image = p.subMenuIcon.future.get();
                _setSizeUpdate();
                _setDrawUpdate();
            }
        }

        void MenuButton::sizeHintEvent(const SizeHintEvent& event)
        {
            IButton::sizeHintEvent(event);
            TG_P();

            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (displayScaleChanged || p.size.init)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, event.displayScale);
                p.size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, event.displayScale);
                p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
                p.size.fontInfo = event.style->getFontRole(_fontRole, event.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
                p.size.textSize = event.fontSystem->getSize(_text, p.size.fontInfo);
                p.size.shortcutSize = event.fontSystem->getSize(p.shortcutText, p.size.fontInfo);
                p.draw.textGlyphs.clear();
                p.draw.shortcutGlyphs.clear();
            }

            Size2I sizeHint;
            if (_iconImage)
            {
                sizeHint.w = _iconImage->getWidth() + p.size.spacing;
                sizeHint.h = _iconImage->getHeight();
            }
            if (!_text.empty())
            {
                sizeHint.w += p.size.textSize.w + p.size.margin * 2;
                sizeHint.h = std::max(sizeHint.h, p.size.fontMetrics.lineHeight);
            }
            if (!p.shortcutText.empty())
            {
                sizeHint.w += p.size.spacing * 4 + p.size.shortcutSize.w;
                sizeHint.h = std::max(sizeHint.h, p.size.shortcutSize.h);
            }
            if (p.subMenuIcon.image)
            {
                sizeHint.w += p.size.spacing + p.subMenuIcon.image->getWidth();
                sizeHint.h = std::max(sizeHint.h, p.subMenuIcon.image->getHeight());
            }
            sizeHint = margin(sizeHint, p.size.margin + p.size.border);
            _setSizeHint(sizeHint);
        }

        void MenuButton::clipEvent(const Box2I& clipRect, bool clipped)
        {
            IWidget::clipEvent(clipRect, clipped);
            TG_P();
            if (clipped)
            {
                p.draw.textGlyphs.clear();
                p.draw.shortcutGlyphs.clear();
            }
        }

        void MenuButton::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IButton::drawEvent(drawRect, event);
            TG_P();

            // Draw the background.
            const ColorRole colorRole = _checked ? _checkedRole : _buttonRole;
            if (colorRole != ColorRole::None)
            {
                event.render->drawRect(
                    convert(p.draw.g),
                    event.style->getColorRole(colorRole));
            }
            
            // Draw the mouse state.
            if (_isMousePressed())
            {
                event.render->drawRect(
                    convert(p.draw.g),
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (_isMouseInside())
            {
                event.render->drawRect(
                    convert(p.draw.g),
                    event.style->getColorRole(ColorRole::Hover));
            }

            // Draw the current state.
            if (p.current)
            {
                event.render->drawMesh(
                    border(p.draw.g, p.size.border),
                    event.style->getColorRole(ColorRole::KeyFocus));
            }

            // Draw the icon.
            int x = p.draw.g2.x();
            if (_iconImage)
            {
                const Size2I& iconSize = _iconImage->getSize();
                event.render->drawImage(
                    _iconImage,
                    Box2F(
                        x,
                        p.draw.g2.y() + p.draw.g2.h() / 2 - iconSize.h / 2,
                        iconSize.w,
                        iconSize.h),
                    event.style->getColorRole(isEnabled() ?
                        ColorRole::Text :
                        ColorRole::TextDisabled));
                x += iconSize.w + p.size.spacing;
            }

            // Draw the text.
            if (!_text.empty())
            {
                if (p.draw.textGlyphs.empty())
                {
                    p.draw.textGlyphs = event.fontSystem->getGlyphs(_text, p.size.fontInfo);
                }
                event.render->drawText(
                    p.draw.textGlyphs,
                    p.size.fontMetrics,
                    V2F(
                        x + p.size.margin,
                        p.draw.g2.y() + p.draw.g2.h() / 2 - p.size.textSize.h / 2),
                    event.style->getColorRole(isEnabled() ?
                        ColorRole::Text :
                        ColorRole::TextDisabled));
            }

            // Draw the shortcut.
            if (!p.shortcutText.empty())
            {
                if (p.draw.shortcutGlyphs.empty())
                {
                    p.draw.shortcutGlyphs = event.fontSystem->getGlyphs(p.shortcutText, p.size.fontInfo);
                }
                const V2F pos(
                    p.draw.g2.max.x - p.size.shortcutSize.w,
                    p.draw.g2.y() + p.draw.g2.h() / 2 - p.size.shortcutSize.h / 2);
                event.render->drawText(
                    p.draw.shortcutGlyphs,
                    p.size.fontMetrics,
                    pos,
                    event.style->getColorRole(isEnabled() ?
                        ColorRole::Text :
                        ColorRole::TextDisabled));
            }

            // Draw the sub menu icon.
            if (p.subMenuIcon.image)
            {
                const Size2I& iconSize = p.subMenuIcon.image->getSize();
                event.render->drawImage(
                    p.subMenuIcon.image,
                    Box2F(
                        p.draw.g2.max.x - iconSize.w,
                        p.draw.g2.y() + p.draw.g2.h() / 2 - iconSize.h / 2,
                        iconSize.w,
                        iconSize.h),
                    event.style->getColorRole(isEnabled() ?
                        ColorRole::Text :
                        ColorRole::TextDisabled));
            }
        }

        void MenuButton::keyPressEvent(KeyEvent& event)
        {
            if (0 == event.modifiers)
            {
                switch (event.key)
                {
                case Key::Enter:
                    event.accept = true;
                    takeKeyFocus();
                    if (_pressedCallback)
                    {
                        _pressedCallback();
                    }
                    click();
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

        void MenuButton::keyReleaseEvent(KeyEvent& event)
        {
            event.accept = true;
        }
    }
}
