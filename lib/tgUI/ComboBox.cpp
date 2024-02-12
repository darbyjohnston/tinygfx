// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ComboBox.h>

#include <tgUI/ButtonGroup.h>
#include <tgUI/DrawUtil.h>
#include <tgUI/IMenuPopup.h>
#include <tgUI/ListButton.h>
#include <tgUI/RowLayout.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        namespace
        {
            class ComboBoxMenu : public IMenuPopup
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    const std::vector<ComboBoxItem>&,
                    const std::shared_ptr<IWidget>& parent);

                ComboBoxMenu();

            public:
                virtual ~ComboBoxMenu();

                static std::shared_ptr<ComboBoxMenu> create(
                    const std::shared_ptr<Context>&,
                    const std::vector<ComboBoxItem>&,
                    const std::shared_ptr<IWidget>& parent = nullptr);

                void setCallback(const std::function<void(int)>&);

            private:
                std::shared_ptr<ButtonGroup> _buttonGroup;
                std::shared_ptr<VerticalLayout> _layout;
                std::function<void(int)> _callback;
            };

            void ComboBoxMenu::_init(
                const std::shared_ptr<Context>& context,
                const std::vector<ComboBoxItem>& items,
                const std::shared_ptr<IWidget>& parent)
            {
                IMenuPopup::_init(context, "tg::ui::ComboBoxMenu", parent);

                std::vector<std::shared_ptr<ListButton> > buttons;
                _buttonGroup = ButtonGroup::create(context, ButtonGroupType::Click);
                for (const auto& item : items)
                {
                    auto button = ListButton::create(context, shared_from_this());
                    button->setText(item.text);
                    button->setIcon(item.icon);
                    buttons.push_back(button);
                    _buttonGroup->addButton(button);
                }

                _layout = VerticalLayout::create(context);
                _layout->setSpacingRole(SizeRole::None);
                for (const auto& button : buttons)
                {
                    button->setParent(_layout);
                }
                setWidget(_layout);
                
                auto weak = std::weak_ptr<ComboBoxMenu>(std::dynamic_pointer_cast<ComboBoxMenu>(shared_from_this()));
                _buttonGroup->setClickedCallback(
                    [weak](int value)
                    {
                        if (auto widget = weak.lock())
                        {
                            if (widget->_callback)
                            {
                                widget->_callback(value);
                            }
                        }
                    });
            }

            ComboBoxMenu::ComboBoxMenu()
            {}

            ComboBoxMenu::~ComboBoxMenu()
            {}

            std::shared_ptr<ComboBoxMenu> ComboBoxMenu::create(
                const std::shared_ptr<Context>& context,
                const std::vector<ComboBoxItem>& items,
                const std::shared_ptr<IWidget>& parent)
            {
                auto out = std::shared_ptr<ComboBoxMenu>(new ComboBoxMenu);
                out->_init(context, items, parent);
                return out;
            }

            void ComboBoxMenu::setCallback(const std::function<void(int)>& value)
            {
                _callback = value;
            }
        }

        bool ComboBoxItem::operator == (const ComboBoxItem& other) const
        {
            return text == other.text && icon == other.icon;
        }

        bool ComboBoxItem::operator != (const ComboBoxItem& other) const
        {
            return !(*this == other);
        }

        struct ComboBox::Private
        {
            std::vector<ComboBoxItem> items;
            int currentIndex = -1;
            std::function<void(int)> indexCallback;
            std::function<void(const ComboBoxItem&)> itemCallback;
            FontRole fontRole = FontRole::Label;

            std::string text;
            std::string icon;
            float iconScale = 1.F;
            bool iconInit = false;
            std::future<std::shared_ptr<Image> > iconFuture;
            std::shared_ptr<Image> iconImage;
            bool arrowIconInit = false;
            std::future<std::shared_ptr<Image> > arrowIconFuture;
            std::shared_ptr<Image> arrowIconImage;

            std::shared_ptr<ComboBoxMenu> menu;

            struct SizeData
            {
                float displayScale = 0.F;
                int margin = 0;
                int spacing = 0;
                int border = 0;

                bool textInit = true;
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

        void ComboBox::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::ComboBox", parent);
            setAcceptsKeyFocus(true);
            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);
        }

        ComboBox::ComboBox() :
            _p(new Private)
        {}

        ComboBox::~ComboBox()
        {}

        std::shared_ptr<ComboBox> ComboBox::create(
            const std::shared_ptr<Context>&context,
            const std::shared_ptr<IWidget>&parent)
        {
            auto out = std::shared_ptr<ComboBox>(new ComboBox);
            out->_init(context, parent);
            return out;
        }

        std::shared_ptr<ComboBox> ComboBox::create(
            const std::shared_ptr<Context>& context,
            const std::vector<std::string>& items,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ComboBox>(new ComboBox);
            out->_init(context, parent);
            out->setItems(items);
            return out;
        }

        void ComboBox::setItems(const std::vector<ComboBoxItem>& value)
        {
            TG_P();
            if (value == p.items)
                return;
            p.items = value;
            p.currentIndex = clamp(
                p.currentIndex,
                0,
                static_cast<int>(p.items.size()) - 1);
            const ComboBoxItem item = _getItem(p.currentIndex);
            p.text = item.text;
            p.icon = item.icon;
            p.iconInit = true;
            p.iconFuture = std::future<std::shared_ptr<Image> >();
            p.iconImage.reset();
            p.size.textInit = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void ComboBox::setItems(const std::vector<std::string>& value)
        {
            TG_P();
            std::vector<ComboBoxItem> items;
            for (const auto& s : value)
            {
                items.push_back({ s, std::string()});
            }
            setItems(items);
        }

        void ComboBox::setCurrentIndex(int value)
        {
            TG_P();
            const int tmp = clamp(
                value,
                0,
                static_cast<int>(p.items.size()) - 1);
            if (tmp == p.currentIndex)
                return;
            p.currentIndex = tmp;
            const ComboBoxItem item = _getItem(p.currentIndex);
            p.text = item.text;
            p.icon = item.icon;
            p.iconInit = true;
            p.iconFuture = std::future<std::shared_ptr<Image> >();
            p.iconImage.reset();
            p.size.textInit = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void ComboBox::setIndexCallback(const std::function<void(int)>& value)
        {
            _p->indexCallback = value;
        }

        void ComboBox::setItemCallback(const std::function<void(const ComboBoxItem&)>& value)
        {
            _p->itemCallback = value;
        }

        void ComboBox::setFontRole(FontRole value)
        {
            TG_P();
            if (value == p.fontRole)
                return;
            p.fontRole = value;
            p.size.textInit = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void ComboBox::tickEvent(
            bool parentsVisible,
            bool parentsEnabled,
            const TickEvent& event)
        {
            IWidget::tickEvent(parentsVisible, parentsEnabled, event);
            TG_P();
            if (event.displayScale != p.iconScale)
            {
                p.iconScale = event.displayScale;
                p.iconInit = true;
                p.iconFuture = std::future<std::shared_ptr<Image> >();
                p.iconImage.reset();
                p.arrowIconInit = true;
                p.arrowIconFuture = std::future<std::shared_ptr<Image> >();
                p.arrowIconImage.reset();
            }
            if (!p.icon.empty() && p.iconInit)
            {
                p.iconInit = false;
                p.iconFuture = event.iconLibrary->request(p.icon, event.displayScale);
            }
            if (p.arrowIconInit)
            {
                p.arrowIconInit = false;
                p.arrowIconFuture = event.iconLibrary->request("MenuArrow", event.displayScale);
            }
            if (p.iconFuture.valid() &&
                p.iconFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                p.iconImage = p.iconFuture.get();
                _setSizeUpdate();
                _setDrawUpdate();
            }
            if (p.arrowIconFuture.valid() &&
                p.arrowIconFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                p.arrowIconImage = p.arrowIconFuture.get();
                _setSizeUpdate();
                _setDrawUpdate();
            }
        }

        void ComboBox::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();

            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (displayScaleChanged)
            {
                p.size.displayScale = event.displayScale;
                p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, p.size.displayScale);
                p.size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, p.size.displayScale);
                p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
            }
            if (displayScaleChanged || p.size.textInit)
            {
                p.size.textInit = false;
                p.size.fontInfo = event.style->getFontRole(p.fontRole, p.size.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
                p.size.textSize = Size2I();
                for (const auto& i : p.items)
                {
                    if (!i.text.empty())
                    {
                        const Size2I textSize = event.fontSystem->getSize(i.text, p.size.fontInfo);
                        p.size.textSize.w = std::max(p.size.textSize.w, textSize.w);
                        p.size.textSize.h = std::max(p.size.textSize.h, textSize.h);
                    }
                }
                p.draw.glyphs.clear();
            }

            Size2I sizeHint;
            sizeHint.w = p.size.textSize.w + p.size.margin * 2;
            sizeHint.h = p.size.fontMetrics.lineHeight;
            if (p.iconImage)
            {
                sizeHint.w += p.iconImage->getWidth();
                if (!p.text.empty())
                {
                    sizeHint.w += p.size.spacing;
                }
                sizeHint.h = std::max(
                    sizeHint.h,
                    static_cast<int>(p.iconImage->getHeight()));
            }
            if (p.arrowIconImage)
            {
                sizeHint.w += p.arrowIconImage->getWidth();
                sizeHint.w += p.size.spacing;
                sizeHint.h = std::max(
                    sizeHint.h,
                    static_cast<int>(p.arrowIconImage->getHeight()));
            }
            sizeHint.w +=
                p.size.margin * 2 +
                p.size.border * 4;
            sizeHint.h +=
                p.size.margin * 2 +
                p.size.border * 4;
            _setSizeHint(sizeHint);
        }

        void ComboBox::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();

            const Box2I& g = getGeometry();
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
                event.style->getColorRole(ColorRole::Button));

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
            int x = g3.x();
            if (p.iconImage)
            {
                const Size2I& iconSize = p.iconImage->getSize();
                event.render->drawImage(
                    p.iconImage,
                    Box2F(
                        x,
                        g3.y() + g3.h() / 2 - iconSize.h / 2,
                        iconSize.w,
                        iconSize.h),
                    event.style->getColorRole(enabled ?
                        ColorRole::Text :
                        ColorRole::TextDisabled));
                x += iconSize.w + p.size.spacing;
            }

            if (!p.text.empty())
            {
                if (p.draw.glyphs.empty())
                {
                    p.draw.glyphs = event.fontSystem->getGlyphs(p.text, p.size.fontInfo);
                }
                const V2F pos(
                    x + p.size.margin,
                    g3.y() + g3.h() / 2 - p.size.textSize.h / 2 +
                    p.size.fontMetrics.ascender);
                event.render->drawText(
                    p.draw.glyphs,
                    pos,
                    event.style->getColorRole(enabled ?
                        ColorRole::Text :
                        ColorRole::TextDisabled));
            }

            if (p.arrowIconImage)
            {
                const Size2I& iconSize = p.arrowIconImage->getSize();
                event.render->drawImage(
                    p.arrowIconImage,
                    Box2F(
                        g3.x() + g3.w() - iconSize.w,
                        g3.y() + g3.h() / 2 - iconSize.h / 2,
                        iconSize.w,
                        iconSize.h),
                    event.style->getColorRole(enabled ?
                        ColorRole::Text :
                        ColorRole::TextDisabled));
            }
        }

        void ComboBox::mouseEnterEvent()
        {
            IWidget::mouseEnterEvent();
            _setDrawUpdate();
        }

        void ComboBox::mouseLeaveEvent()
        {
            IWidget::mouseLeaveEvent();
            _setDrawUpdate();
        }

        void ComboBox::mousePressEvent(MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
            TG_P();
            _click();
            _setDrawUpdate();
        }

        void ComboBox::mouseReleaseEvent(MouseClickEvent& event)
        {
            IWidget::mouseReleaseEvent(event);
            _setDrawUpdate();
        }

        void ComboBox::keyPressEvent(KeyEvent& event)
        {
            TG_P();
            if (0 == event.modifiers)
            {
                switch (event.key)
                {
                case Key::Up:
                    event.accept = true;
                    _commitIndex(p.currentIndex - 1);
                    break;
                case Key::Down:
                    event.accept = true;
                    _commitIndex(p.currentIndex + 1);
                    break;
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

        void ComboBox::keyReleaseEvent(KeyEvent& event)
        {
            event.accept = true;
        }

        ComboBoxItem ComboBox::_getItem(int value) const
        {
            TG_P();
            ComboBoxItem out;
            if (value >= 0 && value < static_cast<int>(p.items.size()))
            {
                out = p.items[value];
            }
            return out;
        }

        void ComboBox::_click()
        {
            TG_P();
            takeKeyFocus();
            if (auto context = _getContext().lock())
            {
                if (!p.menu)
                {
                    p.menu = ComboBoxMenu::create(context, p.items);
                    p.menu->open(getWindow(), getGeometry());
                    auto weak = std::weak_ptr<ComboBox>(std::dynamic_pointer_cast<ComboBox>(shared_from_this()));
                    p.menu->setCallback(
                        [weak](int index)
                        {
                            if (auto widget = weak.lock())
                            {
                                widget->_p->menu->close();
                                widget->_p->menu.reset();
                                widget->takeKeyFocus();
                                if (index != -1)
                                {
                                    widget->_commitIndex(index);
                                }
                            }
                        });
                    p.menu->setCloseCallback(
                        [weak]
                        {
                            if (auto widget = weak.lock())
                            {
                                widget->_p->menu.reset();
                                widget->takeKeyFocus();
                            }
                        });
                }
                else
                {
                    p.menu->close();
                    p.menu.reset();
                }
            }
        }

        void ComboBox::_commitIndex(int value)
        {
            TG_P();
            const int currentIndex = p.currentIndex;
            setCurrentIndex(value);
            if (p.currentIndex != currentIndex)
            {
                if (p.indexCallback)
                {
                    p.indexCallback(p.currentIndex);
                }
                if (p.itemCallback)
                {
                    p.itemCallback(_getItem(p.currentIndex));
                }
            }
        }
    }
}
