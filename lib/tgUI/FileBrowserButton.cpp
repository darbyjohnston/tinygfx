// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/FileBrowserWidgets.h>

#include <tgUI/DrawUtil.h>

#include <tgCore/Format.h>

#include <ctime>
#include <filesystem>
//#include <format>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct FileBrowserButton::Private
        {
            std::vector<std::string> labels;
            std::vector<int> columns;

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
                std::vector<int> textWidths;
            };
            SizeData size;

            struct DrawData
            {
                std::vector< std::vector<std::shared_ptr<Glyph> > > glyphs;
            };
            DrawData draw;
        };

        void FileBrowserButton::_init(
            const std::shared_ptr<Context>& context,
            const FileBrowserInfo& info,
            const std::shared_ptr<IWidget>& parent)
        {
            IButton::_init(context, "tg::ui::FileBrowser", parent);
            TG_P();

            setButtonRole(ColorRole::None);
            setAcceptsKeyFocus(true);

            // Icon.
            setIcon(info.isDir ? "Directory" : "File");

            // File name.
            p.labels.push_back(info.path.filename().string());

            // File extension.
            p.labels.push_back(!info.isDir ?
                info.path.extension().string() :
                std::string());

            // File size.
            std::string label;
            if (!info.isDir)
            {
                if (info.size < megabyte)
                {
                    label = Format("{0}KB").
                        arg(info.size / static_cast<float>(kilobyte), 2);
                }
                else if (info.size < gigabyte)
                {
                    label = Format("{0}MB").
                        arg(info.size / static_cast<float>(megabyte), 2);
                }
                else
                {
                    label = Format("{0}GB").
                        arg(info.size / static_cast<float>(gigabyte), 2);
                }
            }
            p.labels.push_back(label);

            // File last modification time.
            // \todo std::format is available in C++20.
            //p.labels.push_back(std::format("{}", info.time));
        }

        FileBrowserButton::FileBrowserButton() :
            _p(new Private)
        {}

        FileBrowserButton::~FileBrowserButton()
        {}

        std::shared_ptr<FileBrowserButton> FileBrowserButton::create(
            const std::shared_ptr<Context>& context,
            const FileBrowserInfo& info,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<FileBrowserButton>(new FileBrowserButton);
            out->_init(context, info, parent);
            return out;
        }

        const std::vector<int>& FileBrowserButton::getTextWidths() const
        {
            return _p->size.textWidths;
        }

        void FileBrowserButton::setColumns(const std::vector<int>& value)
        {
            _p->columns = value;
        }

        void FileBrowserButton::sizeHintEvent(const SizeHintEvent& event)
        {
            IButton::sizeHintEvent(event);
            TG_P();

            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, p.size.displayScale);
                p.size.spacing = event.style->getSizeRole(SizeRole::Spacing, p.size.displayScale);
                p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
            }
            if (p.size.textInit || displayScaleChanged)
            {
                p.size.textInit = false;
                p.size.fontInfo = event.style->getFontRole(_fontRole, p.size.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
                p.size.textWidths.clear();
                for (const auto& label : p.labels)
                {
                    p.size.textWidths.push_back(
                        event.fontSystem->getSize(label, p.size.fontInfo).w);
                }
                p.draw.glyphs.clear();
            }

            Size2I sizeHint;
            if (!p.labels.empty())
            {
                sizeHint.h = p.size.fontMetrics.lineHeight;
            }
            if (_iconImage)
            {
                sizeHint.w += _iconImage->getWidth();
                if (!p.labels.empty())
                {
                    sizeHint.w += p.size.spacing;
                }
                sizeHint.h = std::max(sizeHint.h, _iconImage->getHeight());
            }
            sizeHint.w +=
                p.size.margin * 2 +
                p.size.border * 4;
            sizeHint.h +=
                p.size.margin * 2 +
                p.size.border * 4;
            _setSizeHint(sizeHint);
        }

        void FileBrowserButton::clipEvent(const Box2I& clipRect, bool clipped)
        {
            IWidget::clipEvent(clipRect, clipped);
            TG_P();
            if (clipped)
            {
                p.draw.glyphs.clear();
            }
        }

        void FileBrowserButton::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IButton::drawEvent(drawRect, event);
            TG_P();

            const Box2I& g = getGeometry();
            const bool enabled = isEnabled();

            // Draw the key focus.
            if (hasKeyFocus())
            {
                event.render->drawMesh(
                    border(g, p.size.border * 2),
                    event.style->getColorRole(ColorRole::KeyFocus));
            }

            // Draw the background and checked state.
            const ColorRole colorRole = _checked ?
                ColorRole::Checked :
                _buttonRole;
            if (colorRole != ColorRole::None)
            {
                event.render->drawRect(
                    Box2F(g.x(), g.y(), g.w(), g.h()),
                    event.style->getColorRole(colorRole));
            }

            // Draw the pressed and hover states.
            if (_isMousePressed() && contains(g, _getMousePos()))
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

            // Draw the icon.
            const Box2I g2 = margin(g, -p.size.border * 2);
            int x = g2.x() + p.size.margin;
            if (_iconImage)
            {
                const Size2I& size = _iconImage->getSize();
                event.render->drawImage(
                    _iconImage,
                    Box2F(
                        x,
                        g2.y() + g2.h() / 2 - size.h / 2,
                        size.w,
                        size.h),
                    event.style->getColorRole(enabled ?
                        ColorRole::Text :
                        ColorRole::TextDisabled));
                x += size.w + p.size.spacing;
            }

            // Draw the text.
            int rightColumnsWidth = 0;
            for (size_t i = 1; i < p.columns.size(); ++i)
            {
                rightColumnsWidth += p.columns[i];
            }
            const bool glyphsInit = p.draw.glyphs.empty();
            for (size_t i = 0; i < p.labels.size() && i < p.columns.size(); ++i)
            {
                if (glyphsInit)
                {
                    p.draw.glyphs.push_back(
                        event.fontSystem->getGlyphs(p.labels[i], p.size.fontInfo));
                }
                const V2F pos(
                    x,
                    g2.y() + g2.h() / 2 - p.size.fontMetrics.lineHeight / 2);
                event.render->drawText(
                    p.draw.glyphs[i],
                    p.size.fontMetrics,
                    pos,
                    event.style->getColorRole(enabled ?
                        ColorRole::Text :
                        ColorRole::TextDisabled));
                if (0 == i)
                {
                    x = g2.max.x - p.size.margin - rightColumnsWidth;
                }
                else
                {
                    x += p.columns[i];
                }
            }
        }

        void FileBrowserButton::keyPressEvent(KeyEvent& event)
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

        void FileBrowserButton::keyReleaseEvent(KeyEvent& event)
        {
            event.accept = true;
        }
    }
}
