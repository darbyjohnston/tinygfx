// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ListWidget.h>

#include <tgUI/DrawUtil.h>
#include <tgUI/ScrollWidget.h>

#include <tgCore/String.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        namespace
        {
            class ItemsWidget : public IWidget
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    ButtonGroupType,
                    const std::shared_ptr<IWidget>& parent);

                ItemsWidget() = default;

            public:
                virtual ~ItemsWidget() = default;

                static std::shared_ptr<ItemsWidget> create(
                    const std::shared_ptr<Context>&,
                    ButtonGroupType,
                    const std::shared_ptr<IWidget>& parent = nullptr);

                const std::vector<std::string>& getItems() const;
                void setItems(const std::vector<std::string>&);
                void setCallback(const std::function<void(int, bool)>&);

                int getCurrent() const;
                void setCurrent(int);
                std::shared_ptr<IObservableValue<int> > observeCurrent() const;

                const std::string& getSearch() const;
                void setSearch(const std::string&);
                void clearSearch();

                FontRole getFontRole() const;
                void setFontRole(FontRole);

                Box2I getRect(int) const;

                void setGeometry(const Box2I&) override;
                void sizeHintEvent(const SizeHintEvent&) override;
                void drawEvent(const Box2I&, const DrawEvent&) override;
                void keyPressEvent(KeyEvent&) override;
                void keyReleaseEvent(KeyEvent&) override;

            private:
                int _getMargin() const;
                int _posToIndex(int) const;
                int _indexToPos(int) const;

                ButtonGroupType _type = ButtonGroupType::Click;
                std::vector<std::string> _items;
                std::function<void(int, bool)> _callback;
                std::shared_ptr<ObservableValue<int> > _current;
                std::string _search;
                FontRole _fontRole = FontRole::Label;

                struct SizeData
                {
                    bool init = true;
                    float displayScale = 0.F;
                    int spacing = 0;
                    int border = 0;
                    FontInfo fontInfo;
                    FontMetrics fontMetrics;
                    Size2I itemsSize;
                };
                SizeData _size;
            };

            void ItemsWidget::_init(
                const std::shared_ptr<Context>& context,
                ButtonGroupType type,
                const std::shared_ptr<IWidget>& parent)
            {
                IWidget::_init(context, "tg::ui::ItemsWidget", parent);

                setAcceptsKeyFocus(true);

                _current = ObservableValue<int>::create(-1);
            }

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
                return _items;
            }

            void ItemsWidget::setItems(const std::vector<std::string>& value)
            {
                if (value == _items)
                    return;
                _items = value;
                _current->setIfChanged(clamp(_current->get(), 0, static_cast<int>(_items.size()) - 1));
                _size.init = true;
                _setSizeUpdate();
                _setDrawUpdate();
            }

            void ItemsWidget::setCallback(const std::function<void(int, bool)>& value)
            {
                _callback = value;
            }

            int ItemsWidget::getCurrent() const
            {
                return _current->get();
            }

            void ItemsWidget::setCurrent(int value)
            {
                const int tmp = clamp(value, 0, static_cast<int>(_items.size()) - 1);
                if (_current->setIfChanged(tmp))
                {
                    _setDrawUpdate();
                }
            }

            std::shared_ptr<IObservableValue<int> > ItemsWidget::observeCurrent() const
            {
                return _current;
            }

            const std::string& ItemsWidget::getSearch() const
            {
                return _search;
            }

            void ItemsWidget::setSearch(const std::string& value)
            {
                if (value == _search)
                    return;
                _search = value;
                _size.init = true;
                _setSizeUpdate();
                _setDrawUpdate();
            }

            void ItemsWidget::clearSearch()
            {
                if (!_search.empty())
                {
                    _search = std::string();
                    _setSizeUpdate();
                    _setDrawUpdate();
                }
            }

            FontRole ItemsWidget::getFontRole() const
            {
                return _fontRole;
            }

            void ItemsWidget::setFontRole(FontRole value)
            {
                if (value == _fontRole)
                    return;
                _fontRole = value;
                _size.init = true;
                _setSizeUpdate();
                _setDrawUpdate();
            }

            Box2I ItemsWidget::getRect(int index) const
            {
                const Box2I& g = getGeometry();
                const int m = _getMargin();
                const int h = _size.fontMetrics.lineHeight + m * 2;
                return Box2I(0, index * h, g.w(), h);
            }

            void ItemsWidget::setGeometry(const Box2I& value)
            {
                IWidget::setGeometry(value);
            }

            void ItemsWidget::sizeHintEvent(const SizeHintEvent& event)
            {
                IWidget::sizeHintEvent(event);
                const bool displayScaleChanged = event.displayScale != _size.displayScale;
                if (_size.init || displayScaleChanged)
                {
                    _size.init = false;
                    _size.displayScale = event.displayScale;
                    _size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, _size.displayScale);
                    _size.border = event.style->getSizeRole(SizeRole::Border, _size.displayScale);

                    _size.fontInfo = event.style->getFontRole(_fontRole, event.displayScale);
                    _size.fontMetrics = event.fontSystem->getMetrics(_size.fontInfo);

                    const int m = _getMargin();
                    _size.itemsSize = Size2I(
                        0,
                        (_size.fontMetrics.lineHeight + m * 2) * _items.size());
                    for (const auto& item : _items)
                    {
                        const Size2I size = event.fontSystem->getSize(item, _size.fontInfo);
                        _size.itemsSize.w = std::max(_size.itemsSize.w, size.w + m * 2);
                    }
                }
                _setSizeHint(_size.itemsSize);
            }

            void ItemsWidget::drawEvent(const Box2I& drawRect, const DrawEvent& event)
            {
                IWidget::drawEvent(drawRect, event);
                const Box2I& g = getGeometry();
                const int m = _getMargin();
                for (size_t i = 0; i < _items.size(); ++i)
                {
                    const Box2I r = getRect(i);
                    const Box2I r2(g.min + r.min, r.size());
                    if (intersects(r2, drawRect))
                    {
                        const auto glyphs = event.fontSystem->getGlyphs(_items[i], _size.fontInfo);
                        event.render->drawText(
                            glyphs,
                            _size.fontMetrics,
                            V2F(r2.min.x + m, r2.min.y + m),
                            event.style->getColorRole(ColorRole::Text));
                    }
                }
                if (hasKeyFocus() && _current->get() != -1)
                {
                    const Box2I r = getRect(_current->get());
                    const Box2I r2(g.min + r.min, r.size());
                    if (intersects(r2, drawRect))
                    {
                        event.render->drawMesh(
                            border(r2, _size.border * 2),
                            event.style->getColorRole(ColorRole::KeyFocus));
                    }
                }
            }

            void ItemsWidget::keyPressEvent(KeyEvent& event)
            {
                IWidget::keyPressEvent(event);
                if (0 == event.modifiers)
                {
                    switch (event.key)
                    {
                    case Key::Enter:
                    {
                        event.accept = true;
                        const int current = _current->get();
                        switch (_type)
                        {
                        case ButtonGroupType::Click:
                            if (current >= 0 && _callback)
                            {
                                _callback(current, true);
                            }
                            break;
                        }
                        break;
                    }
                    case Key::Up:
                        event.accept = true;
                        setCurrent(getCurrent() - 1);
                        break;
                    case Key::Down:
                        event.accept = true;
                        setCurrent(getCurrent() + 1);
                        break;
                    case Key::PageUp:
                        event.accept = true;
                        setCurrent(getCurrent() - 10);
                        break;
                    case Key::PageDown:
                        event.accept = true;
                        setCurrent(getCurrent() + 10);
                        break;
                    case Key::Home:
                        event.accept = true;
                        setCurrent(0);
                        break;
                    case Key::End:
                        event.accept = true;
                        setCurrent(static_cast<int>(_items.size()) - 1);
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
                return _size.border * 3;
            }

            int ItemsWidget::_posToIndex(int value) const
            {
                const int m = _getMargin();
                return value / (_size.fontMetrics.lineHeight + m * 2);
            }

            int ItemsWidget::_indexToPos(int value) const
            {
                const int m = _getMargin();
                return value * (_size.fontMetrics.lineHeight + m * 2);
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
