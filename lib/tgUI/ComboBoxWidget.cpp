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
        struct ComboBoxWidget::Private
        {
            std::vector<ComboBoxItem> items;
            std::function<void(int)> callback;
            std::shared_ptr<ObservableValue<int> > current;
            int radio = -1;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int margin = 0;
                int spacing = 0;
                int border = 0;
                FontInfo fontInfo;
                FontMetrics fontMetrics;
                Size2I itemsSize;
                std::vector<int> itemHeights;
            };
            SizeData size;

            struct DrawData
            {
                float iconScale = 1.F;
                bool iconInit = false;
                std::vector<std::future<std::shared_ptr<Image> > > iconFutures;
                std::vector<std::shared_ptr<Image> > iconImages;
            };
            DrawData draw;

            struct MouseData
            {
                int hover = -1;
                int pressed = -1;
            };
            MouseData mouse;
        };

        void ComboBoxWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::vector<ComboBoxItem>& items,
            int currentIndex,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::ComboBoxWidget", parent);
            TG_P();
            setAcceptsKeyFocus(true);
            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);
            p.items = items;
            p.current = ObservableValue<int>::create(currentIndex);
            p.radio = currentIndex;
        }

        ComboBoxWidget::ComboBoxWidget() :
            _p(new Private)
        {}

        ComboBoxWidget::~ComboBoxWidget()
        {}

        std::shared_ptr<ComboBoxWidget> ComboBoxWidget::create(
            const std::shared_ptr<Context>& context,
            const std::vector<ComboBoxItem>& items,
            int currentIndex,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ComboBoxWidget>(new ComboBoxWidget);
            out->_init(context, items, currentIndex, parent);
            return out;
        }

        void ComboBoxWidget::setCallback(const std::function<void(int)>& value)
        {
            _p->callback = value;
        }

        int ComboBoxWidget::getCurrent() const
        {
            return _p->current->get();
        }

        void ComboBoxWidget::setCurrent(int value)
        {
            TG_P();
            const int tmp = clamp(value, 0, static_cast<int>(p.items.size()) - 1);
            if (p.current->setIfChanged(tmp))
            {
                _setDrawUpdate();
            }
        }

        std::shared_ptr<IObservableValue<int> > ComboBoxWidget::observeCurrent() const
        {
            return _p->current;
        }

        Box2I ComboBoxWidget::getRect(int index) const
        {
            TG_P();
            const Box2I& g = getGeometry();
            int y = 0;
            for (int i = 0; i < index && i < p.size.itemHeights.size(); ++i)
            {
                y += p.size.itemHeights[i];
            }
            int h = 0;
            if (index >= 0 && index < p.size.itemHeights.size())
            {
                h = p.size.itemHeights[index];
            }
            return Box2I(0, y, g.w(), h);
        }

        void ComboBoxWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
        }

        void ComboBoxWidget::tickEvent(
            bool parentsVisible,
            bool parentsEnabled,
            const TickEvent& event)
        {
            IWidget::tickEvent(parentsVisible, parentsEnabled, event);
            TG_P();
            if (event.displayScale != p.draw.iconScale)
            {
                p.draw.iconScale = event.displayScale;
                p.draw.iconInit = true;
                p.draw.iconFutures.clear();
                p.draw.iconImages.clear();
            }
            if (p.draw.iconInit)
            {
                p.draw.iconInit = false;
                p.draw.iconFutures.resize(p.items.size());
                p.draw.iconImages.resize(p.items.size());
                for (size_t i = 0; i < p.items.size(); ++i)
                {
                    if (!p.items[i].icon.empty())
                    {
                        p.draw.iconFutures[i] = event.iconLibrary->request(
                            p.items[i].icon,
                            event.displayScale);
                    }
                }
            }
            for (size_t i = 0; i < p.items.size(); ++i)
            {
                if (p.draw.iconFutures[i].valid() &&
                    p.draw.iconFutures[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready)
                {
                    p.size.init = true;
                    p.draw.iconImages[i] = p.draw.iconFutures[i].get();
                    _setSizeUpdate();
                    _setDrawUpdate();
                }
            }
        }

        void ComboBoxWidget::sizeHintEvent(const SizeHintEvent& event)
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

                p.size.fontInfo = event.style->getFontRole(FontRole::Label, event.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);

                p.size.itemsSize = Size2I();
                p.size.itemHeights.clear();
                for (size_t i = 0; i < p.items.size(); ++i)
                {
                    const Size2I size = event.fontSystem->getSize(p.items[i].text, p.size.fontInfo);
                    int h = p.size.fontMetrics.lineHeight;
                    if (p.draw.iconImages[i])
                    {
                        size.w += p.draw.iconImages[i]->getWidth() + p.size.spacing;
                        h = std::max(h, p.draw.iconImages[i]->getHeight());
                    }
                    h += p.size.margin * 2 + p.size.border * 4;
                    p.size.itemsSize.w = std::max(p.size.itemsSize.w, size.w);
                    p.size.itemsSize.h += h;
                    p.size.itemHeights.push_back(h);
                }
                p.size.itemsSize.w +=
                    p.size.margin * 4 +
                    p.size.border * 4;
            }
            _setSizeHint(p.size.itemsSize);
        }

        void ComboBoxWidget::drawEvent(const Box2I& drawRect, const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();

            const Box2I& g = getGeometry();

            if (p.radio != -1)
            {
                const Box2I r = move(getRect(p.radio), g.min);
                event.render->drawRect(
                    Box2F(r.x(), r.y(), r.w(), r.h()),
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
                    int x = r.min.x + p.size.margin + p.size.border * 2;
                    if (auto icon = p.draw.iconImages[i])
                    {
                        const Size2I& iconSize = icon->getSize();
                        event.render->drawImage(
                            icon,
                            Box2F(
                                x,
                                r.y() + r.h() / 2 - iconSize.h / 2,
                                iconSize.w,
                                iconSize.h),
                            event.style->getColorRole(ColorRole::Text));
                        x += iconSize.w + p.size.spacing;
                    }
                    const auto glyphs = event.fontSystem->getGlyphs(p.items[i].text, p.size.fontInfo);
                    event.render->drawText(
                        glyphs,
                        p.size.fontMetrics,
                        V2F(
                            x + p.size.margin,
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

        void ComboBoxWidget::mouseLeaveEvent()
        {
            IWidget::mouseLeaveEvent();
            TG_P();
            if (p.mouse.hover != -1)
            {
                p.mouse.hover = -1;
                _setDrawUpdate();
            }
        }

        void ComboBoxWidget::mouseMoveEvent(MouseMoveEvent& event)
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

        void ComboBoxWidget::mousePressEvent(MouseClickEvent& event)
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

        void ComboBoxWidget::mouseReleaseEvent(MouseClickEvent& event)
        {
            IWidget::mouseReleaseEvent(event);
            TG_P();
            event.accept = true;
            const Box2I& g = getGeometry();
            const int index = _posToIndex(event.pos.y - g.min.y);
            if (index == p.mouse.pressed)
            {
                if (p.callback)
                {
                    p.callback(p.mouse.pressed);
                }
                _setDrawUpdate();
            }
            p.mouse.pressed = -1;
            _setDrawUpdate();
        }

        void ComboBoxWidget::keyPressEvent(KeyEvent& event)
        {
            TG_P();
            if (0 == event.modifiers)
            {
                switch (event.key)
                {
                case Key::Enter:
                    event.accept = true;
                    takeKeyFocus();
                    if (p.callback)
                    {
                        p.callback(p.current->get());
                    }
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
                default: break;
                }
            }
            if (!event.accept)
            {
                IWidget::keyPressEvent(event);
            }
        }

        void ComboBoxWidget::keyReleaseEvent(KeyEvent& event)
        {
            IWidget::keyReleaseEvent(event);
            event.accept = true;
        }

        int ComboBoxWidget::_posToIndex(int value) const
        {
            TG_P();
            int out = -1;
            for (int i = 0, y = 0; i < p.size.itemHeights.size(); ++i)
            {
                const int h = p.size.itemHeights[i];
                if (value >= y && value < y + h)
                {
                    out = i;
                    break;
                }
                y += h;
            }
            return out;
        }
    }
}
