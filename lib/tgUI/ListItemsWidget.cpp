// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ListWidgetPrivate.h>

#include <tgUI/DrawUtil.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct ListItemsWidget::Private
        {
            ui::ButtonGroupType type = ui::ButtonGroupType::Click;
            std::vector<std::string> items;
            std::function<void(int, bool)> callback;
            std::shared_ptr<ObservableValue<int> > current;
            int radio = -1;
            std::vector<bool> toggle;
            std::string search;
            ui::FontRole fontRole = ui::FontRole::Label;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int margin = 0;
                int spacing = 0;
                int border = 0;
                core::FontInfo fontInfo;
                core::FontMetrics fontMetrics;
                core::Size2I itemsSize;
            };
            SizeData size;

            struct MouseData
            {
                int hover = -1;
                int pressed = -1;
            };
            MouseData mouse;
        };

        void ListItemsWidget::_init(
            const std::shared_ptr<Context>& context,
            ButtonGroupType type,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::ListItemsWidget", parent);
            TG_P();
            setAcceptsKeyFocus(true);
            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);
            p.type = type;
            p.current = ObservableValue<int>::create(-1);
        }

        ListItemsWidget::ListItemsWidget() :
            _p(new Private)
        {}

        ListItemsWidget::~ListItemsWidget()
        {}

        std::shared_ptr<ListItemsWidget> ListItemsWidget::create(
            const std::shared_ptr<Context>& context,
            ButtonGroupType type,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ListItemsWidget>(new ListItemsWidget);
            out->_init(context, type, parent);
            return out;
        }

        const std::vector<std::string>& ListItemsWidget::getItems() const
        {
            return _p->items;
        }

        void ListItemsWidget::setItems(const std::vector<std::string>& value)
        {
            TG_P();
            if (value == p.items)
                return;
            p.items = value;
            p.current->setIfChanged(clamp(p.current->get(), 0, static_cast<int>(p.items.size()) - 1));
            if (ButtonGroupType::Toggle == p.type)
            {
                p.toggle.resize(value.size());
            }
            p.size.init = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        bool ListItemsWidget::getChecked(int index) const
        {
            TG_P();
            bool out = false;
            switch (p.type)
            {
            case ButtonGroupType::Radio:
                out = index == p.current->get();
                break;
            case ButtonGroupType::Toggle:
                if (index >= 0 && index < p.items.size())
                {
                    out = p.toggle[index];
                }
                break;
            default: break;
            }
            return out;
        }

        void ListItemsWidget::setChecked(int index, bool value)
        {
            TG_P();
            switch (p.type)
            {
            case ButtonGroupType::Radio:
                if (index != p.radio)
                {
                    p.radio = index;
                    _setDrawUpdate();
                }
                break;
            case ButtonGroupType::Toggle:
                if (index >= 0 && index < p.items.size())
                {
                    if (p.toggle[index] != value)
                    {
                        p.toggle[index] = value;
                        _setDrawUpdate();
                    }
                }
                break;
            default: break;
            }
        }

        void ListItemsWidget::setCallback(const std::function<void(int, bool)>& value)
        {
            _p->callback = value;
        }

        int ListItemsWidget::getCurrent() const
        {
            return _p->current->get();
        }

        void ListItemsWidget::setCurrent(int value)
        {
            TG_P();
            const int tmp = clamp(value, 0, static_cast<int>(p.items.size()) - 1);
            if (p.current->setIfChanged(tmp))
            {
                _setDrawUpdate();
            }
        }

        std::shared_ptr<IObservableValue<int> > ListItemsWidget::observeCurrent() const
        {
            return _p->current;
        }

        const std::string& ListItemsWidget::getSearch() const
        {
            return _p->search;
        }

        void ListItemsWidget::setSearch(const std::string& value)
        {
            TG_P();
            if (value == p.search)
                return;
            p.search = value;
            p.size.init = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void ListItemsWidget::clearSearch()
        {
            TG_P();
            if (!p.search.empty())
            {
                p.search = std::string();
                _setSizeUpdate();
                _setDrawUpdate();
            }
        }

        FontRole ListItemsWidget::getFontRole() const
        {
            return _p->fontRole;
        }

        void ListItemsWidget::setFontRole(FontRole value)
        {
            TG_P();
            if (value == p.fontRole)
                return;
            p.fontRole = value;
            p.size.init = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        Box2I ListItemsWidget::getRect(int index) const
        {
            TG_P();
            const Box2I& g = getGeometry();
            const int h = _getItemHeight();
            return Box2I(0, index * h, g.w(), h);
        }

        void ListItemsWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
        }

        void ListItemsWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();
            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, p.size.displayScale);
                p.size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, p.size.displayScale);
                p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);

                p.size.fontInfo = event.style->getFontRole(p.fontRole, event.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);

                const int h = _getItemHeight();
                p.size.itemsSize = Size2I(0, h * p.items.size());
                for (const auto& item : p.items)
                {
                    const Size2I size = event.fontSystem->getSize(item, p.size.fontInfo);
                    p.size.itemsSize.w = std::max(p.size.itemsSize.w, size.w);
                }
                p.size.itemsSize.w +=
                    p.size.margin * 4 +
                    p.size.border * 4;
            }
            _setSizeHint(p.size.itemsSize);
        }

        void ListItemsWidget::drawEvent(const Box2I& drawRect, const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();

            const Box2I& g = getGeometry();

            std::vector<Box2F> checked;
            switch (p.type)
            {
            case ButtonGroupType::Radio:
                if (p.radio != -1)
                {
                    const Box2I r = move(getRect(p.radio), g.min);
                    checked.push_back(Box2F(r.x(), r.y(), r.w(), r.h()));
                }
                break;
            case ButtonGroupType::Toggle:
            {
                for (size_t i = 0; i < p.toggle.size(); ++i)
                {
                    if (p.toggle[i])
                    {
                        const Box2I r = move(getRect(i), g.min);
                        checked.push_back(Box2F(r.x(), r.y(), r.w(), r.h()));
                    }
                }
                break;
            }
            default: break;
            }
            if (!checked.empty())
            {
                event.render->drawRects(
                    checked,
                    event.style->getColorRole(ColorRole::Checked));
            }

            if (p.mouse.pressed != -1)
            {
                const Box2I r = move(getRect(p.mouse.pressed), g.min);
                event.render->drawRect(
                    Box2F(r.x(), r.y(), r.w(), r.h()),
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (p.mouse.hover != -1)
            {
                const Box2I r = move(getRect(p.mouse.hover), g.min);
                event.render->drawRect(
                    Box2F(r.x(), r.y(), r.w(), r.h()),
                    event.style->getColorRole(ColorRole::Hover));
            }

            for (size_t i = 0; i < p.items.size(); ++i)
            {
                const Box2I r = move(getRect(i), g.min);
                if (intersects(r, drawRect))
                {
                    const auto glyphs = event.fontSystem->getGlyphs(p.items[i], p.size.fontInfo);
                    event.render->drawText(
                        glyphs,
                        p.size.fontMetrics,
                        V2F(
                            r.min.x + p.size.margin * 2 + p.size.border * 2,
                            r.min.y + p.size.margin + p.size.border * 2),
                        event.style->getColorRole(ColorRole::Text));
                }
            }

            if (hasKeyFocus() && p.current->get() != -1)
            {
                const Box2I r = move(getRect(p.current->get()), g.min);
                if (intersects(r, drawRect))
                {
                    event.render->drawMesh(
                        border(r, p.size.border * 2),
                        event.style->getColorRole(ColorRole::KeyFocus));
                }
            }
        }

        void ListItemsWidget::mouseLeaveEvent()
        {
            IWidget::mouseLeaveEvent();
            TG_P();
            if (p.mouse.hover != -1)
            {
                p.mouse.hover = -1;
                _setDrawUpdate();
            }
        }

        void ListItemsWidget::mouseMoveEvent(MouseMoveEvent& event)
        {
            IWidget::mouseMoveEvent(event);
            TG_P();
            const Box2I& g = getGeometry();
            const int hover = _posToIndex(event.pos.y - g.min.y);
            if (hover >= 0 &&
                hover < p.items.size() &&
                hover != p.mouse.hover)
            {
                p.mouse.hover = hover;
                _setDrawUpdate();
            }
        }

        void ListItemsWidget::mousePressEvent(MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
            TG_P();
            event.accept = true;
            takeKeyFocus();
            const Box2I& g = getGeometry();
            const int pressed = _posToIndex(event.pos.y - g.min.y);
            if (pressed >= 0 &&
                pressed < p.items.size())
            {
                p.mouse.pressed = pressed;
                setCurrent(pressed);
                _setDrawUpdate();
            }
        }

        void ListItemsWidget::mouseReleaseEvent(MouseClickEvent& event)
        {
            IWidget::mouseReleaseEvent(event);
            TG_P();
            event.accept = true;
            const Box2I& g = getGeometry();
            const int index = _posToIndex(event.pos.y - g.min.y);
            if (index == p.mouse.pressed)
            {
                _action(p.mouse.pressed);
                _setDrawUpdate();
            }
            p.mouse.pressed = -1;
            _setDrawUpdate();
        }

        void ListItemsWidget::keyPressEvent(KeyEvent& event)
        {
            IWidget::keyPressEvent(event);
            TG_P();
            if (0 == event.modifiers)
            {
                switch (event.key)
                {
                case Key::Enter:
                    event.accept = true;
                    takeKeyFocus();
                    _action(p.current->get());
                    break;
                case Key::Up:
                    event.accept = true;
                    takeKeyFocus();
                    setCurrent(getCurrent() - 1);
                    break;
                case Key::Down:
                    event.accept = true;
                    takeKeyFocus();
                    setCurrent(getCurrent() + 1);
                    break;
                case Key::PageUp:
                    event.accept = true;
                    takeKeyFocus();
                    setCurrent(getCurrent() - 10);
                    break;
                case Key::PageDown:
                    event.accept = true;
                    takeKeyFocus();
                    setCurrent(getCurrent() + 10);
                    break;
                case Key::Home:
                    event.accept = true;
                    takeKeyFocus();
                    setCurrent(0);
                    break;
                case Key::End:
                    event.accept = true;
                    takeKeyFocus();
                    setCurrent(static_cast<int>(p.items.size()) - 1);
                    break;
                case Key::Escape:
                    event.accept = true;
                    releaseKeyFocus();
                    break;
                default: break;
                }
            }
        }

        void ListItemsWidget::keyReleaseEvent(KeyEvent& event)
        {
            IWidget::keyReleaseEvent(event);
            event.accept = true;
        }

        int ListItemsWidget::_getItemHeight() const
        {
            TG_P();
            return
                p.size.fontMetrics.lineHeight +
                p.size.margin * 2 +
                p.size.border * 4;
        }

        int ListItemsWidget::_posToIndex(int value) const
        {
            const int h = _getItemHeight();
            return h > 0 ? (value / h) : 0;
        }

        void ListItemsWidget::_action(int index)
        {
            TG_P();
            switch (p.type)
            {
            case ButtonGroupType::Click:
                if (index >= 0 &&
                    index < p.items.size() &&
                    p.callback)
                {
                    p.callback(index, true);
                }
                break;
            case ButtonGroupType::Radio:
                if (index != p.radio &&
                    index >= 0 &&
                    index < p.items.size())
                {
                    p.radio = index;
                    if (p.callback)
                    {
                        p.callback(p.radio, true);
                    }
                    _setDrawUpdate();
                }
                break;
            case ButtonGroupType::Toggle:
                if (index >= 0 &&
                    index < p.items.size())
                {
                    p.toggle[index] = !p.toggle[index];
                    if (p.callback)
                    {
                        p.callback(index, p.toggle[index]);
                    }
                    _setDrawUpdate();
                }
                break;
            default: break;
            }
        }
    }
}
