// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/LineEdit.h>

#include <tgUI/DrawUtil.h>
#include <tgUI/IClipboard.h>
#include <tgUI/IWindow.h>
#include <tgUI/LayoutUtil.h>

#include <tgCore/RenderUtil.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        namespace
        {
            typedef std::pair<int, int> SelectionPair;

            class Selection
            {
            public:
                const SelectionPair& get() const;
                SelectionPair getSorted() const;
                bool isValid() const;
                void set(const SelectionPair&);
                void setFirst(int);
                void setSecond(int);

                void select(int first, int second);
                void clear();

            private:
                SelectionPair _pair = std::make_pair(-1, -1);
            };

            const SelectionPair& Selection::get() const
            {
                return _pair;
            }

            SelectionPair Selection::getSorted() const
            {
                return std::make_pair(
                    std::min(_pair.first, _pair.second),
                    std::max(_pair.first, _pair.second));
            }

            bool Selection::isValid() const
            {
                return
                    _pair.first != -1 &&
                    _pair.second != -1 &&
                    _pair.first != _pair.second;
            }

            void Selection::set(const SelectionPair& value)
            {
                _pair = value;
            }

            void Selection::setFirst(int value)
            {
                _pair.first = value;
            }

            void Selection::setSecond(int value)
            {
                _pair.second = value;
            }

            void Selection::select(int first, int second)
            {
                if (-1 == _pair.first)
                {
                    _pair.first = first;
                    _pair.second = second;
                }
                else
                {
                    _pair.second = second;
                }
            }

            void Selection::clear()
            {
                _pair = std::make_pair(-1, -1);
            }
        }

        struct LineEdit::Private
        {
            std::string text;
            std::function<void(const std::string&)> textCallback;
            std::function<void(const std::string&)> textChangedCallback;
            std::string format = "                    ";
            std::function<void(bool)> focusCallback;
            FontRole fontRole = FontRole::Label;
            int cursorPos = 0;
            bool cursorVisible = false;
            std::chrono::steady_clock::time_point cursorTimer;
            Selection selection;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int margin = 0;
                int border = 0;

                bool textInit = true;
                FontInfo fontInfo;
                FontMetrics fontMetrics;
                Size2I textSize;
                Size2I formatSize;
            };
            SizeData size;

            struct DrawData
            {
                std::vector<std::shared_ptr<Glyph> > glyphs;
                std::vector<Box2I> glyphsBox;
            };
            DrawData draw;
        };

        void LineEdit::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::LineEdit", parent);
            TG_P();
            setAcceptsKeyFocus(true);
            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);
            _textUpdate();
        }

        LineEdit::LineEdit() :
            _p(new Private)
        {}

        LineEdit::~LineEdit()
        {}

        std::shared_ptr<LineEdit> LineEdit::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<LineEdit>(new LineEdit);
            out->_init(context, parent);
            return out;
        }

        const std::string& LineEdit::getText() const
        {
            return _p->text;
        }

        void LineEdit::setText(const std::string& value)
        {
            TG_P();
            if (value == p.text)
                return;
            p.text = value;
            p.cursorPos = p.text.size();
            _textUpdate();
        }

        void LineEdit::clearText()
        {
            setText(std::string());
        }

        void LineEdit::setTextCallback(const std::function<void(const std::string&)>& value)
        {
            _p->textCallback = value;
        }

        void LineEdit::setTextChangedCallback(const std::function<void(const std::string&)>& value)
        {
            _p->textChangedCallback = value;
        }

        void LineEdit::setFormat(const std::string& value)
        {
            TG_P();
            if (value == p.format)
                return;
            p.format = value;
            _textUpdate();
        }

        void LineEdit::setFocusCallback(const std::function<void(bool)>& value)
        {
            _p->focusCallback = value;
        }

        void LineEdit::setFontRole(FontRole value)
        {
            TG_P();
            if (value == p.fontRole)
                return;
            p.fontRole = value;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void LineEdit::setVisible(bool value)
        {
            TG_P();
            const bool changed = value != isVisible(false);
            IWidget::setVisible(value);
            if (changed && !isVisible(false))
            {
                if (p.cursorVisible)
                {
                    p.cursorVisible = false;
                    _setDrawUpdate();
                }
            }
        }

        void LineEdit::setEnabled(bool value)
        {
            TG_P();
            const bool changed = value != isEnabled(false);
            IWidget::setEnabled(value);
            if (changed && !isEnabled(false))
            {
                if (p.cursorVisible)
                {
                    p.cursorVisible = false;
                    _setDrawUpdate();
                }
            }
        }

        void LineEdit::tickEvent(
            bool parentsVisible,
            bool parentsEnabled,
            const TickEvent& event)
        {
            IWidget::tickEvent(parentsVisible, parentsEnabled, event);
            TG_P();
            if (hasKeyFocus())
            {
                const auto now = std::chrono::steady_clock::now();
                const std::chrono::duration<float> diff = now - p.cursorTimer;
                if (diff.count() > .5F)
                {
                    p.cursorVisible = !p.cursorVisible;
                    _setDrawUpdate();
                    p.cursorTimer = now;
                }
            }
            else if (p.cursorVisible)
            {
                p.cursorVisible = false;
                _setDrawUpdate();
            }
        }

        void LineEdit::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();

            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, p.size.displayScale);
                p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
            }
            if (displayScaleChanged || p.size.textInit)
            {
                p.size.textInit = false;
                p.size.fontInfo = event.style->getFontRole(p.fontRole, p.size.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
                p.size.textSize = event.fontSystem->getSize(p.text, p.size.fontInfo);
                p.size.formatSize = event.fontSystem->getSize(p.format, p.size.fontInfo);
                p.draw.glyphs.clear();
                p.draw.glyphsBox.clear();
            }

            _setSizeHint(Size2I(
                p.size.formatSize.w +
                p.size.margin * 2 +
                p.size.border * 4,
                p.size.fontMetrics.lineHeight +
                p.size.margin * 2 +
                p.size.border * 4));
        }

        void LineEdit::clipEvent(const Box2I& clipRect, bool clipped)
        {
            IWidget::clipEvent(clipRect, clipped);
            TG_P();
            if (clipped)
            {
                p.draw.glyphs.clear();
                p.draw.glyphsBox.clear();
            }
        }

        void LineEdit::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();

            const Box2I g = _getAlignGeometry();
            const bool enabled = isEnabled();

            if (hasKeyFocus())
            {
                event.render->drawMesh(
                    border(g, p.size.border * 2),
                    event.style->getColorRole(ColorRole::KeyFocus));
            }
            else
            {
                event.render->drawMesh(
                    border(margin(g, -p.size.border), p.size.border),
                    event.style->getColorRole(ColorRole::Border));
            }

            const Box2I g2 = margin(g, -p.size.border * 2);
            event.render->drawRect(
                Box2F(g2.x(), g2.y(), g2.w(), g2.h()),
                event.style->getColorRole(ColorRole::Base));

            const ClipRectEnabledState clipRectEnabledState(event.render);
            const ClipRectState clipRectState(event.render);
            event.render->setClipRectEnabled(true);
            event.render->setClipRect(intersect(margin(g, -p.size.border * 2), drawRect));

            const Box2I g3 = margin(g, -(p.size.border * 2 + p.size.margin));
            if (p.selection.isValid())
            {
                const auto selection = p.selection.getSorted();
                const std::string text0 = p.text.substr(0, selection.first);
                const int x0 = event.fontSystem->getSize(text0, p.size.fontInfo).w;
                const std::string text1 = p.text.substr(0, selection.second);
                const int x1 = event.fontSystem->getSize(text1, p.size.fontInfo).w;
                event.render->drawRect(
                    Box2F(g3.x() + x0, g3.y(), x1 - x0, g3.h()),
                    event.style->getColorRole(ColorRole::Checked));
            }

            V2F pos(
                g3.x(),
                g3.y() + g3.h() / 2 - p.size.fontMetrics.lineHeight / 2 +
                p.size.fontMetrics.ascender);
            if (!p.text.empty() && p.draw.glyphs.empty())
            {
                p.draw.glyphs = event.fontSystem->getGlyphs(p.text, p.size.fontInfo);
                p.draw.glyphsBox = event.fontSystem->getBox(p.text, p.size.fontInfo);
            }
            event.render->drawText(
                p.draw.glyphs,
                pos,
                event.style->getColorRole(enabled ?
                    ColorRole::Text :
                    ColorRole::TextDisabled));

            if (p.cursorVisible)
            {
                const std::string text = p.text.substr(0, p.cursorPos);
                const int x = event.fontSystem->getSize(text, p.size.fontInfo).w;
                event.render->drawRect(
                    Box2F(
                        g3.x() + x,
                        g3.y(),
                        p.size.border,
                        g3.h()),
                    event.style->getColorRole(ColorRole::Text));
            }
        }

        void LineEdit::mouseMoveEvent(MouseMoveEvent& event)
        {
            IWidget::mouseMoveEvent(event);
            TG_P();
            if (_isMousePressed())
            {
                const int cursorPos = _getCursorPos(event.pos);
                if (cursorPos != p.cursorPos)
                {
                    p.cursorPos = cursorPos;
                    p.cursorVisible = true;
                    p.cursorTimer = std::chrono::steady_clock::now();
                    _setDrawUpdate();
                }
                if (cursorPos != p.selection.get().second)
                {
                    p.selection.setSecond(cursorPos);
                    _setDrawUpdate();
                }
            }
        }

        void LineEdit::mousePressEvent(MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
            TG_P();
            const int cursorPos = _getCursorPos(event.pos);
            if (cursorPos != p.cursorPos)
            {
                p.cursorPos = cursorPos;
                p.cursorVisible = true;
                p.cursorTimer = std::chrono::steady_clock::now();
                _setDrawUpdate();
            }
            const SelectionPair selection(cursorPos, cursorPos);
            if (selection != p.selection.get())
            {
                p.selection.set(selection);
                _setDrawUpdate();
            }
            takeKeyFocus();
        }

        void LineEdit::keyFocusEvent(bool value)
        {
            IWidget::keyFocusEvent(value);
            TG_P();
            if (!value)
            {
                p.selection.clear();
                if (p.textCallback)
                {
                    p.textCallback(p.text);
                }
                _setDrawUpdate();
            }
            if (p.focusCallback)
            {
                p.focusCallback(value);
            }
        }

        void LineEdit::keyPressEvent(KeyEvent& event)
        {
            TG_P();
            if (hasKeyFocus())
            {
                switch (event.key)
                {
                case Key::A:
                    event.accept = true;
                    if (event.modifiers & static_cast<int>(ui::KeyModifier::Control))
                    {
                        p.selection.clear();
                        p.selection.select(0, p.text.size());
                        _setDrawUpdate();
                    }
                    break;
                case Key::C:
                    event.accept = true;
                    if (event.modifiers & static_cast<int>(ui::KeyModifier::Control))
                    {
                        if (p.selection.isValid())
                        {
                            if (auto window = getWindow())
                            {
                                if (auto clipboard = window->getClipboard())
                                {
                                    const auto selection = p.selection.getSorted();
                                    const std::string text = p.text.substr(
                                        selection.first,
                                        selection.second - selection.first);
                                    clipboard->setText(text);
                                }
                            }
                        }
                    }
                    break;
                case Key::V:
                    event.accept = true;
                    if (event.modifiers & static_cast<int>(ui::KeyModifier::Control))
                    {
                        if (auto window = getWindow())
                        {
                            if (auto clipboard = window->getClipboard())
                            {
                                const std::string text = clipboard->getText();
                                if (p.selection.isValid())
                                {
                                    const auto selection = p.selection.getSorted();
                                    p.text.replace(
                                        selection.first,
                                        selection.second - selection.first,
                                        text);
                                    p.selection.clear();
                                    p.cursorPos = selection.first + text.size();
                                }
                                else
                                {
                                    p.text.insert(p.cursorPos, text);
                                    p.cursorPos += text.size();
                                }
                                if (p.textChangedCallback)
                                {
                                    p.textChangedCallback(p.text);
                                }
                                _textUpdate();
                            }
                        }
                    }
                    break;
                case Key::X:
                    event.accept = true;
                    if (event.modifiers & static_cast<int>(ui::KeyModifier::Control))
                    {
                        if (p.selection.isValid())
                        {
                            if (auto window = getWindow())
                            {
                                if (auto clipboard = window->getClipboard())
                                {
                                    const auto selection = p.selection.getSorted();
                                    const std::string text = p.text.substr(
                                        selection.first,
                                        selection.second - selection.first);
                                    clipboard->setText(text);
                                    p.text.replace(
                                        selection.first,
                                        selection.second - selection.first,
                                        "");
                                    p.selection.clear();
                                    p.cursorPos = selection.first;
                                    if (p.textChangedCallback)
                                    {
                                        p.textChangedCallback(p.text);
                                    }
                                    _textUpdate();
                                }
                            }
                        }
                    }
                    break;
                case Key::Left:
                    event.accept = true;
                    if (p.cursorPos > 0)
                    {
                        if (event.modifiers & static_cast<int>(ui::KeyModifier::Shift))
                        {
                            p.selection.select(p.cursorPos, p.cursorPos - 1);
                        }
                        else
                        {
                            p.selection.clear();
                        }

                        p.cursorPos--;
                        p.cursorVisible = true;
                        p.cursorTimer = std::chrono::steady_clock::now();

                        _setDrawUpdate();
                    }
                    break;
                case Key::Right:
                    event.accept = true;
                    if (p.cursorPos < p.text.size())
                    {
                        if (event.modifiers & static_cast<int>(ui::KeyModifier::Shift))
                        {
                            p.selection.select(p.cursorPos, p.cursorPos + 1);
                        }
                        else
                        {
                            p.selection.clear();
                        }

                        p.cursorPos++;
                        p.cursorVisible = true;
                        p.cursorTimer = std::chrono::steady_clock::now();

                        _setDrawUpdate();
                    }
                    break;
                case Key::Home:
                    event.accept = true;
                    if (p.cursorPos > 0)
                    {
                        if (event.modifiers & static_cast<int>(ui::KeyModifier::Shift))
                        {
                            p.selection.select(p.cursorPos, 0);
                        }
                        else
                        {
                            p.selection.clear();
                        }

                        p.cursorPos = 0;
                        p.cursorVisible = true;
                        p.cursorTimer = std::chrono::steady_clock::now();

                        _setDrawUpdate();
                    }
                    break;
                case Key::End:
                    event.accept = true;
                    if (p.cursorPos < p.text.size())
                    {
                        if (event.modifiers & static_cast<int>(ui::KeyModifier::Shift))
                        {
                            p.selection.select(p.cursorPos, p.text.size());
                        }
                        else
                        {
                            p.selection.clear();
                        }

                        p.cursorPos = p.text.size();
                        p.cursorVisible = true;
                        p.cursorTimer = std::chrono::steady_clock::now();

                        _setDrawUpdate();
                    }
                    break;
                case Key::Backspace:
                    event.accept = true;
                    if (p.selection.isValid())
                    {
                        const auto selection = p.selection.getSorted();
                        p.text.erase(
                            selection.first,
                            selection.second - selection.first);
                        p.selection.clear();
                        p.cursorPos = selection.first;
                        if (p.textChangedCallback)
                        {
                            p.textChangedCallback(p.text);
                        }
                        _textUpdate();
                    }
                    else if (p.cursorPos > 0)
                    {
                        const auto i = p.text.begin() + p.cursorPos - 1;
                        p.text.erase(i);
                        p.cursorPos--;
                        if (p.textChangedCallback)
                        {
                            p.textChangedCallback(p.text);
                        }
                        _textUpdate();
                    }
                    break;
                case Key::Delete:
                    event.accept = true;
                    if (p.selection.isValid())
                    {
                        const auto selection = p.selection.getSorted();
                        p.text.erase(
                            selection.first,
                            selection.second - selection.first);
                        p.selection.clear();
                        p.cursorPos = selection.first;
                        if (p.textChangedCallback)
                        {
                            p.textChangedCallback(p.text);
                        }
                        _textUpdate();
                    }
                    else if (p.cursorPos < p.text.size())
                    {
                        const auto i = p.text.begin() + p.cursorPos;
                        p.text.erase(i);
                        if (p.textChangedCallback)
                        {
                            p.textChangedCallback(p.text);
                        }
                        _textUpdate();
                    }
                    break;
                case Key::Enter:
                    event.accept = true;
                    if (p.textCallback)
                    {
                        p.textCallback(p.text);
                    }
                    break;
                case Key::Escape:
                    event.accept = true;
                    releaseKeyFocus();
                    break;
                default: break;
                }
            }
        }

        void LineEdit::keyReleaseEvent(KeyEvent& event)
        {
            event.accept = true;
        }

        void LineEdit::textEvent(TextEvent& event)
        {
            TG_P();
            event.accept = true;
            if (p.selection.isValid())
            {
                const auto selection = p.selection.getSorted();
                p.text.replace(
                    selection.first,
                    selection.second - selection.first,
                    event.text);
                p.selection.clear();
                p.cursorPos = selection.first + event.text.size();
            }
            else
            {
                p.text.insert(p.cursorPos, event.text);
                p.cursorPos += event.text.size();
            }
            if (p.textChangedCallback)
            {
                p.textChangedCallback(p.text);
            }
            _textUpdate();
        }

        Box2I LineEdit::_getAlignGeometry() const
        {
            return align(
                getGeometry(),
                getSizeHint(),
                Stretch::Expanding,
                Stretch::Expanding,
                getHAlign(),
                getVAlign());
        }

        int LineEdit::_getCursorPos(const V2I& value)
        {
            TG_P();
            int out = 0;
            const Box2I g = _getAlignGeometry();
            const Box2I g2 = margin(g, -p.size.border * 2);
            const V2I pos(
                clamp(value.x, g2.min.x, g2.max.x - 1),
                clamp(value.y, g2.min.y, g2.max.y - 1));
            Box2I box(
                g2.x(),
                g2.y(),
                0,
                g2.h());
            for (const auto& glyphBox : p.draw.glyphsBox)
            {
                box.max.x = g2.x() + glyphBox.x() + glyphBox.w();
                if (contains(box, pos))
                {
                    break;
                }
                ++out;
            }
            return out;
        }

        void LineEdit::_textUpdate()
        {
            TG_P();
            p.size.textInit = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }
    }
}
