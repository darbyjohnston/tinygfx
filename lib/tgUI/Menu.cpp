// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Menu.h>

#include <tgUI/Divider.h>
#include <tgUI/DrawUtil.h>
#include <tgUI/ListButton.h>
#include <tgUI/RowLayout.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        namespace
        {
            class MenuButton : public IButton
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>& parent);

                MenuButton();

            public:
                virtual ~MenuButton();

                static std::shared_ptr<MenuButton> create(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>& parent = nullptr);

                void setShortcut(Key, int modifiers = 0);
                
                void setSubMenuIcon(const std::string&);

                void setText(const std::string&) override;

                void tickEvent(
                    bool,
                    bool,
                    const TickEvent&) override;
                void sizeHintEvent(const SizeHintEvent&) override;
                void clipEvent(const Box2I&, bool) override;
                void drawEvent(
                    const Box2I&,
                    const DrawEvent&) override;
                void keyPressEvent(KeyEvent&) override;
                void keyReleaseEvent(KeyEvent&) override;

            private:
                Key _shortcut = Key::Unknown;
                int _shortcutModifiers = 0;
                std::string _shortcutText;

                float _iconScale = 1.F;
                struct IconData
                {
                    std::string name;
                    bool init = false;
                    std::future<std::shared_ptr<Image> > future;
                    std::shared_ptr<Image> image;
                };
                IconData _checkedIcon;
                IconData _uncheckedIcon;
                IconData _subMenuIcon;

                struct SizeData
                {
                    int init = true;
                    float displayScale = 0.F;
                    int margin = 0;
                    int spacing = 0;
                    int border = 0;

                    bool textInit = true;
                    FontInfo fontInfo;
                    FontMetrics fontMetrics;
                    Size2I textSize;
                    Size2I shortcutSize;
                };
                SizeData _size;

                struct DrawData
                {
                    std::vector<std::shared_ptr<Glyph> > textGlyphs;
                    std::vector<std::shared_ptr<Glyph> > shortcutGlyphs;
                };
                DrawData _draw;
            };

            void MenuButton::_init(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<IWidget>& parent)
            {
                IButton::_init(context, "tg::ui::MenuButton", parent);
                
                setButtonRole(ColorRole::None);
                setAcceptsKeyFocus(true);
                
                _checkedIcon.name = "MenuChecked";
                _checkedIcon.init = true;
                _uncheckedIcon.name = "MenuUnchecked";
                _uncheckedIcon.init = true;
            }

            MenuButton::MenuButton()
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

            void MenuButton::setShortcut(Key key, int modifiers)
            {
                if (key == _shortcut && modifiers == _shortcutModifiers)
                    return;
                _shortcut = key;
                _shortcutModifiers = modifiers;
                _shortcutText = getShortcutLabel(_shortcut, _shortcutModifiers);
                _size.textInit = true;
                _setSizeUpdate();
                _setDrawUpdate();
            }
        
            void MenuButton::setSubMenuIcon(const std::string& name)
            {
                _subMenuIcon.name = name;
                _subMenuIcon.init = true;
                _subMenuIcon.image.reset();
            }

            void MenuButton::setText(const std::string& value)
            {
                const bool changed = value != _text;
                IButton::setText(value);
                if (changed)
                {
                    _size.textInit = true;
                    _setSizeUpdate();
                    _setDrawUpdate();
                }
            }

            void MenuButton::tickEvent(
                bool parentsVisible,
                bool parentsEnabled,
                const TickEvent& event)
            {
                IButton::tickEvent(parentsVisible, parentsEnabled, event);
                if (event.displayScale != _iconScale)
                {
                    _iconScale = event.displayScale;
                    _checkedIcon.init = true;
                    _checkedIcon.future = std::future<std::shared_ptr<Image> >();
                    _checkedIcon.image.reset();
                    _uncheckedIcon.init = true;
                    _uncheckedIcon.future = std::future<std::shared_ptr<Image> >();
                    _uncheckedIcon.image.reset();
                    _subMenuIcon.init = true;
                    _subMenuIcon.future = std::future<std::shared_ptr<Image> >();
                    _subMenuIcon.image.reset();
                }
                if (!_checkedIcon.name.empty() && _checkedIcon.init)
                {
                    _checkedIcon.init = false;
                    _checkedIcon.future = event.iconLibrary->request(_checkedIcon.name, _iconScale);
                }
                if (_checkedIcon.future.valid() &&
                    _checkedIcon.future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
                {
                    _checkedIcon.image = _checkedIcon.future.get();
                    _setSizeUpdate();
                    _setDrawUpdate();
                }
                if (!_uncheckedIcon.name.empty() && _uncheckedIcon.init)
                {
                    _uncheckedIcon.init = false;
                    _uncheckedIcon.future = event.iconLibrary->request(_uncheckedIcon.name, _iconScale);
                }
                if (_uncheckedIcon.future.valid() &&
                    _uncheckedIcon.future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
                {
                    _uncheckedIcon.image = _uncheckedIcon.future.get();
                    _setSizeUpdate();
                    _setDrawUpdate();
                }
                if (!_subMenuIcon.name.empty() && _subMenuIcon.init)
                {
                    _subMenuIcon.init = false;
                    _subMenuIcon.future = event.iconLibrary->request(_subMenuIcon.name, _iconScale);
                }
                if (_subMenuIcon.future.valid() &&
                    _subMenuIcon.future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
                {
                    _subMenuIcon.image = _subMenuIcon.future.get();
                    _setSizeUpdate();
                    _setDrawUpdate();
                }
            }

            void MenuButton::sizeHintEvent(const SizeHintEvent& event)
            {
                IButton::sizeHintEvent(event);

                const bool displayScaleChanged = event.displayScale != _size.displayScale;
                if (displayScaleChanged || _size.init)
                {
                    _size.init = false;
                    _size.displayScale = event.displayScale;
                    _size.margin = event.style->getSizeRole(SizeRole::MarginInside, event.displayScale);
                    _size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, event.displayScale);
                    _size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
                }
                if (displayScaleChanged || _size.textInit)
                {
                    _size.textInit = false;
                    _size.fontInfo = event.style->getFontRole(_fontRole, event.displayScale);
                    _size.fontMetrics = event.fontSystem->getMetrics(_size.fontInfo);
                    _size.textSize = event.fontSystem->getSize(_text, _size.fontInfo);
                    _size.shortcutSize = event.fontSystem->getSize(_shortcutText, _size.fontInfo);
                    _draw.textGlyphs.clear();
                    _draw.shortcutGlyphs.clear();
                }

                Size2I sizeHint;
                if (_iconImage)
                {
                    sizeHint.w = _iconImage->getWidth() + _size.spacing;
                    sizeHint.h = _iconImage->getHeight();
                }
                else if (_checked && _checkedIcon.image)
                {
                    sizeHint.w = _checkedIcon.image->getWidth() + _size.spacing;
                    sizeHint.h = _checkedIcon.image->getHeight();
                }
                else if (!_checked && _uncheckedIcon.image)
                {
                    sizeHint.w = _uncheckedIcon.image->getWidth() + _size.spacing;
                    sizeHint.h = _uncheckedIcon.image->getHeight();
                }
                if (!_text.empty())
                {
                    sizeHint.w += _size.textSize.w + _size.margin * 2;
                    sizeHint.h = std::max(sizeHint.h, _size.fontMetrics.lineHeight);
                }
                if (!_shortcutText.empty())
                {
                    sizeHint.w += _size.spacing * 4 + _size.shortcutSize.w;
                    sizeHint.h = std::max(sizeHint.h, _size.shortcutSize.h);
                }
                if (_subMenuIcon.image)
                {
                    sizeHint.w += _size.spacing + _subMenuIcon.image->getWidth();
                    sizeHint.h = std::max(sizeHint.h, _subMenuIcon.image->getHeight());
                }
                sizeHint.w +=
                    _size.margin * 2 +
                    _size.border * 4;
                sizeHint.h +=
                    _size.margin * 2 +
                    _size.border * 4;
                _setSizeHint(sizeHint);
            }

            void MenuButton::clipEvent(const Box2I& clipRect, bool clipped)
            {
                IWidget::clipEvent(clipRect, clipped);
                if (clipped)
                {
                    _draw.textGlyphs.clear();
                    _draw.shortcutGlyphs.clear();
                }
            }

            void MenuButton::drawEvent(
                const Box2I& drawRect,
                const DrawEvent& event)
            {
                IButton::drawEvent(drawRect, event);

                const Box2I& g = getGeometry();
                const bool enabled = isEnabled();

                // Draw the key focus.
                if (hasKeyFocus())
                {
                    event.render->drawMesh(
                        border(g, _size.border * 2),
                        event.style->getColorRole(ColorRole::KeyFocus));
                }

                // Draw the background.
                if (_buttonRole != ColorRole::None)
                {
                    event.render->drawRect(
                        Box2F(g.x(), g.y(), g.w(), g.h()),
                        event.style->getColorRole(_buttonRole));
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
                const Box2I g2 = margin(g, -_size.border * 2);
                int x = g2.x() + _size.margin;
                if (_iconImage)
                {
                    if (_checked)
                    {
                        event.render->drawRect(
                            Box2F(g2.x(), g2.y(), g2.h(), g2.h()),
                            event.style->getColorRole(ColorRole::Checked));
                    }
                    const Size2I& iconSize = _iconImage->getSize();
                    event.render->drawImage(
                        _iconImage,
                        Box2F(
                            x,
                            g2.y() + g2.h() / 2 - iconSize.h / 2,
                            iconSize.w,
                            iconSize.h),
                        event.style->getColorRole(enabled ?
                            ColorRole::Text :
                            ColorRole::TextDisabled));
                    x += iconSize.w + _size.spacing;
                }
                else if (_checked && _checkedIcon.image)
                {
                    event.render->drawRect(
                        Box2F(g2.x(), g2.y(), g2.h(), g2.h()),
                        event.style->getColorRole(ColorRole::Checked));
                    const Size2I& iconSize = _checkedIcon.image->getSize();
                    event.render->drawImage(
                        _checkedIcon.image,
                        Box2F(
                            x,
                            g2.y() + g2.h() / 2 - iconSize.h / 2,
                            iconSize.w,
                            iconSize.h),
                        event.style->getColorRole(enabled ?
                            ColorRole::Text :
                            ColorRole::TextDisabled));
                    x += iconSize.w + _size.spacing;
                }
                else if (!_checked && _uncheckedIcon.image)
                {
                    const Size2I& iconSize = _uncheckedIcon.image->getSize();
                    event.render->drawImage(
                        _uncheckedIcon.image,
                        Box2F(
                            x,
                            g2.y() + g2.h() / 2 - iconSize.h / 2,
                            iconSize.w,
                            iconSize.h),
                        event.style->getColorRole(enabled ?
                            ColorRole::Text :
                            ColorRole::TextDisabled));
                    x += iconSize.w + _size.spacing;
                }

                // Draw the text.
                if (!_text.empty())
                {
                    if (_draw.textGlyphs.empty())
                    {
                        _draw.textGlyphs = event.fontSystem->getGlyphs(_text, _size.fontInfo);
                    }
                    const V2F pos(
                        x + _size.margin,
                        g2.y() + g2.h() / 2 - _size.textSize.h / 2);
                    event.render->drawText(
                        _draw.textGlyphs,
                        _size.fontMetrics,
                        pos,
                        event.style->getColorRole(enabled ?
                            ColorRole::Text :
                            ColorRole::TextDisabled));
                }

                // Draw the shortcut.
                if (!_shortcutText.empty())
                {
                    if (_draw.shortcutGlyphs.empty())
                    {
                        _draw.shortcutGlyphs = event.fontSystem->getGlyphs(_shortcutText, _size.fontInfo);
                    }
                    const V2F pos(
                        g2.max.x - _size.margin - _size.shortcutSize.w,
                        g2.y() + g2.h() / 2 - _size.shortcutSize.h / 2);
                    event.render->drawText(
                        _draw.shortcutGlyphs,
                        _size.fontMetrics,
                        pos,
                        event.style->getColorRole(enabled ?
                            ColorRole::Text :
                            ColorRole::TextDisabled));
                }

                // Draw the sub menu icon.
                if (_subMenuIcon.image)
                {
                    const Size2I& iconSize = _subMenuIcon.image->getSize();
                    event.render->drawImage(
                      _subMenuIcon.image,
                      Box2F(
                          g2.max.x - _size.margin - iconSize.w,
                          g2.y() + g2.h() / 2 - iconSize.h / 2,
                          iconSize.w,
                          iconSize.h),
                      event.style->getColorRole(enabled ?
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

            void MenuButton::keyReleaseEvent(KeyEvent& event)
            {
                event.accept = true;
            }
        }

        struct Menu::Private
        {
            std::list<std::shared_ptr<Action> > items;
            std::map<std::shared_ptr<Action>, std::shared_ptr<MenuButton> > buttons;
            std::weak_ptr<Menu> parentMenu;
            std::vector<std::shared_ptr<Menu> > subMenus;
            std::shared_ptr<Menu> openSubMenu;
            std::shared_ptr<VerticalLayout> layout;
        };

        void Menu::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IMenuPopup::_init(context, "tg::ui::Menu", parent);
            TG_P();
            p.layout = VerticalLayout::create(context);
            p.layout->setSpacingRole(SizeRole::None);
            setWidget(p.layout);
        }

        Menu::Menu() :
            _p(new Private)
        {}

        Menu::~Menu()
        {}

        std::shared_ptr<Menu> Menu::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<Menu>(new Menu);
            out->_init(context, parent);
            return out;
        }

        void Menu::addItem(const std::shared_ptr<Action>& item)
        {
            TG_P();
            p.items.push_back(item);
            if (auto context = _getContext().lock())
            {
                auto button = MenuButton::create(context);
                button->setText(item->text);
                button->setIcon(item->icon);
                button->setShortcut(item->shortcut, item->shortcutModifiers);
                button->setHoveredCallback(
                    [this, button](bool value)
                    {
                        if (value)
                        {
                            if (_p->openSubMenu)
                            {
                                _p->openSubMenu->close();
                            }
                            button->takeKeyFocus();
                        }
                    });
                button->setClickedCallback(
                    [this, item]
                    {
                        _accept();
                        if (item->callback)
                        {
                            item->callback();
                        }
                    });
                button->setCheckable(item->checkable);
                button->setChecked(item->checked);
                button->setCheckedCallback(
                    [this, item](bool value)
                    {
                        item->checked = value;
                        _accept();
                        if (item->checkedCallback)
                        {
                            item->checkedCallback(value);
                        }
                    });
                button->setParent(p.layout);
                p.buttons[item] = button;
            }
        }

        void Menu::setItemChecked(const std::shared_ptr<Action>& item, bool value)
        {
            TG_P();
            const auto i = std::find(p.items.begin(), p.items.end(), item);
            if (i != p.items.end())
            {
                (*i)->checked = value;
            }
            const auto j = p.buttons.find(item);
            if (j != p.buttons.end())
            {
                j->second->setChecked(value);
            }
        }

        void Menu::setItemEnabled(const std::shared_ptr<Action>& item, bool value)
        {
            TG_P();
            const auto i = p.buttons.find(item);
            if (i != p.buttons.end())
            {
                i->second->setEnabled(value);
            }
        }

        std::shared_ptr<Menu> Menu::addSubMenu(const std::string& text)
        {
            TG_P();
            std::shared_ptr<Menu> out;
            if (auto context = _getContext().lock())
            {
                out = Menu::create(context);
                out->setPopup(MenuPopup::SubMenu);
                out->_p->parentMenu = std::dynamic_pointer_cast<Menu>(shared_from_this());
                p.subMenus.push_back(out);

                auto button = MenuButton::create(context);
                button->setText(text);
                button->setSubMenuIcon("SubMenuArrow");
                button->setHoveredCallback(
                    [this, out, button](bool value)
                    {
                        if (value)
                        {
                            button->takeKeyFocus();
                            if (!out->isOpen())
                            {
                                if (_p->openSubMenu)
                                {
                                    _p->openSubMenu->close();
                                }
                                _p->openSubMenu = out;
                                out->open(getWindow(), button->getGeometry());
                            }
                        }
                    });
                button->setPressedCallback(
                    [this, out, button]
                    {
                        if (!out->isOpen())
                        {
                            if (_p->openSubMenu)
                            {
                                _p->openSubMenu->close();
                            }
                            _p->openSubMenu = out;
                            out->open(getWindow(), button->getGeometry());
                        }
                    });
                button->setParent(p.layout);

                out->setCloseCallback(
                    [this, button]
                    {
                        _p->openSubMenu.reset();
                    });
            }
            return out;
        }

        void Menu::addDivider()
        {
            TG_P();
            if (auto context = _getContext().lock())
            {
                auto divider = Divider::create(context, Orientation::Horizontal);
                divider->setParent(p.layout);
            }
        }

        void Menu::clear()
        {
            TG_P();
            p.items.clear();
            for (auto button : p.buttons)
            {
                button.second->setParent(nullptr);
            }
            p.buttons.clear();
        }

        bool Menu::shortcut(Key shortcut, int modifiers)
        {
            TG_P();
            bool out = false;
            for (const auto& item : p.items)
            {
                if (shortcut == item->shortcut &&
                    modifiers == item->shortcutModifiers)
                {
                    if (item->callback)
                    {
                        item->callback();
                        out = true;
                    }
                    if (item->checkedCallback)
                    {
                        setItemChecked(item, !item->checked);
                        item->checkedCallback(item->checked);
                        out = true;
                    }
                }
            }
            return out;
        }

        void Menu::close()
        {
            TG_P();
            for (const auto& subMenu : p.subMenus)
            {
                subMenu->close();
            }
            IMenuPopup::close();
        }

        void Menu::_accept()
        {
            TG_P();
            close();
            if (auto parentMenu = p.parentMenu.lock())
            {
                parentMenu->_accept();
            }
        }
    }
}
