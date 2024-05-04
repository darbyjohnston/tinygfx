// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ListWidgetPrivate.h>

#include <tgUI/DrawUtil.h>
#include <tgUI/ScrollWidget.h>

#include <tgCore/String.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct ItemsWidget::Private
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

        void ItemsWidget::_init(
            const std::shared_ptr<Context>& context,
            ButtonGroupType type,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::ItemsWidget", parent);
            TG_P();
            setAcceptsKeyFocus(true);
            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);
            p.type = type;
            p.current = ObservableValue<int>::create(-1);
        }

        ItemsWidget::ItemsWidget() :
            _p(new Private)
        {}

        ItemsWidget::~ItemsWidget()
        {}

        std::shared_ptr<ItemsWidget> ItemsWidget::create(
            const std::shared_ptr<Context>& context,
            ButtonGroupType type,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ItemsWidget>(new ItemsWidget);
            out->_init(context, type, parent);
            return out;
        }

        const std::vector<std::string>& ItemsWidget::getItems() const
        {
            return _p->items;
        }

        void ItemsWidget::setItems(const std::vector<std::string>& value)
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

        bool ItemsWidget::getChecked(int index) const
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

        void ItemsWidget::setChecked(int index, bool value)
        {
            TG_P();
            switch (p.type)
            {
            case ButtonGroupType::Radio:
                p.radio = index;
                _setDrawUpdate();
                break;
            case ButtonGroupType::Toggle:
                if (index >= 0 && index < p.items.size())
                {
                    p.toggle[index] = value;
                    _setDrawUpdate();
                }
                break;
            default: break;
            }
        }

        void ItemsWidget::setCallback(const std::function<void(int, bool)>& value)
        {
            _p->callback = value;
        }

        int ItemsWidget::getCurrent() const
        {
            return _p->current->get();
        }

        void ItemsWidget::setCurrent(int value)
        {
            TG_P();
            const int tmp = clamp(value, 0, static_cast<int>(p.items.size()) - 1);
            if (p.current->setIfChanged(tmp))
            {
                _setDrawUpdate();
            }
        }

        std::shared_ptr<IObservableValue<int> > ItemsWidget::observeCurrent() const
        {
            return _p->current;
        }

        const std::string& ItemsWidget::getSearch() const
        {
            return _p->search;
        }

        void ItemsWidget::setSearch(const std::string& value)
        {
            TG_P();
            if (value == p.search)
                return;
            p.search = value;
            p.size.init = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void ItemsWidget::clearSearch()
        {
            TG_P();
            if (!p.search.empty())
            {
                p.search = std::string();
                _setSizeUpdate();
                _setDrawUpdate();
            }
        }

        FontRole ItemsWidget::getFontRole() const
        {
            return _p->fontRole;
        }

        void ItemsWidget::setFontRole(FontRole value)
        {
            TG_P();
            if (value == p.fontRole)
                return;
            p.fontRole = value;
            p.size.init = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        Box2I ItemsWidget::getRect(int index) const
        {
            TG_P();
            const Box2I& g = getGeometry();
            const int m = _getMargin();
            const int h = p.size.fontMetrics.lineHeight + m * 2;
            return Box2I(0, index * h, g.w(), h);
        }

        void ItemsWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
        }

        void ItemsWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();
            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, p.size.displayScale);
                p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);

                p.size.fontInfo = event.style->getFontRole(p.fontRole, event.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);

                const int m = _getMargin();
                p.size.itemsSize = Size2I(
                    0,
                    (p.size.fontMetrics.lineHeight + m * 2) * p.items.size());
                for (const auto& item : p.items)
                {
                    const Size2I size = event.fontSystem->getSize(item, p.size.fontInfo);
                    p.size.itemsSize.w = std::max(p.size.itemsSize.w, size.w + m * 2);
                }
            }
            _setSizeHint(p.size.itemsSize);
        }

        void ItemsWidget::drawEvent(const Box2I& drawRect, const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();

            const Box2I& g = getGeometry();
            const int m = _getMargin();

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
                        V2F(r.min.x + m, r.min.y + m),
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

        void ItemsWidget::mouseLeaveEvent()
        {
            IWidget::mouseLeaveEvent();
            TG_P();
            if (p.mouse.hover != -1)
            {
                p.mouse.hover = -1;
                _setDrawUpdate();
            }
        }

        void ItemsWidget::mouseMoveEvent(MouseMoveEvent& event)
        {
            IWidget::mouseMoveEvent(event);
            TG_P();
            const Box2I& g = getGeometry();
            const int hover = _posToIndex(event.pos.y - g.min.y);
            if (hover != p.mouse.hover)
            {
                p.mouse.hover = hover;
                _setDrawUpdate();
            }
        }

        void ItemsWidget::mousePressEvent(MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
            TG_P();
            event.accept = true;
            const Box2I& g = getGeometry();
            p.mouse.pressed = _posToIndex(event.pos.y - g.min.y);
            _setDrawUpdate();
        }

        void ItemsWidget::mouseReleaseEvent(MouseClickEvent& event)
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

        void ItemsWidget::keyPressEvent(KeyEvent& event)
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

        void ItemsWidget::keyReleaseEvent(KeyEvent& event)
        {
            IWidget::keyReleaseEvent(event);
            event.accept = true;
        }

        int ItemsWidget::_getMargin() const
        {
            return _p->size.border * 3;
        }

        int ItemsWidget::_posToIndex(int value) const
        {
            TG_P();
            const int m = _getMargin();
            return value / (p.size.fontMetrics.lineHeight + m * 2);
        }

        int ItemsWidget::_indexToPos(int value) const
        {
            TG_P();
            const int m = _getMargin();
            return value * (p.size.fontMetrics.lineHeight + m * 2);
        }

        void ItemsWidget::_action(int index)
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

        struct ListWidget::Private
        {
            std::shared_ptr<ItemsWidget> widget;
            std::shared_ptr<ScrollWidget> scrollWidget;
            std::shared_ptr<ValueObserver<int> > currentObserver;
        };

        void ListWidget::_init(
            const std::shared_ptr<Context>& context,
            ButtonGroupType type,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::ListWidget", parent);
            TG_P();

            p.widget = ItemsWidget::create(context, type);

            p.scrollWidget = ScrollWidget::create(context, ScrollType::Both, shared_from_this());
            p.scrollWidget->setWidget(p.widget);

            p.currentObserver = ValueObserver<int>::create(
                p.widget->observeCurrent(),
                [this](int value)
                {
                    if (value >= 0)
                    {
                        const Box2I r = _p->widget->getRect(value);
                        _p->scrollWidget->scrollTo(r);
                    }
                });
        }

        ListWidget::ListWidget() :
            _p(new Private)
        {}

        ListWidget::~ListWidget()
        {}

        std::shared_ptr<ListWidget> ListWidget::create(
            const std::shared_ptr<Context>& context,
            ButtonGroupType type,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ListWidget>(new ListWidget);
            out->_init(context, type, parent);
            return out;
        }

        const std::vector<std::string>& ListWidget::getItems() const
        {
            return _p->widget->getItems();
        }

        void ListWidget::setItems(const std::vector<std::string>& value)
        {
            _p->widget->setItems(value);
        }

        bool ListWidget::getChecked(int index) const
        {
            return _p->widget->getChecked(index);
        }

        void ListWidget::setChecked(int index, bool value)
        {
            _p->widget->setChecked(index, value);
        }

        void ListWidget::setCallback(const std::function<void(int, bool)>& value)
        {
            _p->widget->setCallback(value);
        }

        const std::string& ListWidget::getSearch() const
        {
            return _p->widget->getSearch();
        }

        void ListWidget::setSearch(const std::string& value)
        {
            _p->widget->setSearch(value);
        }

        void ListWidget::clearSearch()
        {
            _p->widget->clearSearch();
        }

        FontRole ListWidget::getFontRole() const
        {
            return _p->widget->getFontRole();
        }

        void ListWidget::setFontRole(FontRole value)
        {
            _p->widget->setFontRole(value);
        }

        void ListWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->scrollWidget->setGeometry(value);
        }

        void ListWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->scrollWidget->getSizeHint());
        }
    }
}
