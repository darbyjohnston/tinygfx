// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IButton.h>

#include <tgUI/DrawUtil.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct IButton::Private
        {
            bool checkable = false;
            float iconScale = 1.F;
            bool iconInit = false;
            std::future<std::shared_ptr<Image> > iconFuture;
            bool checkedIconInit = false;
            std::future<std::shared_ptr<Image> > checkedIconFuture;
            bool repeatClick = false;
            bool repeatClickInit = false;
            std::chrono::steady_clock::time_point repeatClickTimer;
        };

        void IButton::_init(
            const std::shared_ptr<Context>& context,
            const std::string& objectName,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, objectName, parent);
            _setMouseHover(true);
            _setMousePress(true);
        }

        IButton::IButton() :
            _p(new Private)
        {}

        IButton::~IButton()
        {}

        bool IButton::isCheckable() const
        {
            return _p->checkable;
        }

        void IButton::setCheckable(bool value)
        {
            TG_P();
            if (value == p.checkable)
                return;
            p.checkable = value;
            if (!p.checkable && _checked)
            {
                _checked = false;
                _setDrawUpdate();
            }
        }

        bool IButton::isChecked() const
        {
            return _checked;
        }

        void IButton::setChecked(bool value)
        {
            TG_P();
            if (value == _checked)
                return;
            _checked = value;
            _setDrawUpdate();
        }

        void IButton::setText(const std::string& value)
        {
            if (value == _text)
                return;
            _text = value;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void IButton::setFontRole(FontRole value)
        {
            if (value == _fontRole)
                return;
            _fontRole = value;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void IButton::setIcon(const std::string& icon)
        {
            TG_P();
            _icon = icon;
            p.iconInit = true;
            _iconImage.reset();
        }

        void IButton::setCheckedIcon(const std::string& icon)
        {
            TG_P();
            _checkedIcon = icon;
            p.checkedIconInit = true;
            _checkedIconImage.reset();
        }

        void IButton::setButtonRole(ColorRole value)
        {
            if (value == _buttonRole)
                return;
            _buttonRole = value;
            _setDrawUpdate();
        }

        void IButton::setCheckedRole(ColorRole value)
        {
            if (value == _checkedRole)
                return;
            _checkedRole = value;
            _setDrawUpdate();
        }

        void IButton::setRepeatClick(bool value)
        {
            TG_P();
            p.repeatClick = value;
        }

        void IButton::setHoveredCallback(const std::function<void(bool)>& value)
        {
            _hoveredCallback = value;
        }

        void IButton::setPressedCallback(const std::function<void(void)>& value)
        {
            _pressedCallback = value;
        }

        void IButton::setClickedCallback(const std::function<void(void)>& value)
        {
            _clickedCallback = value;
        }

        void IButton::setCheckedCallback(const std::function<void(bool)>& value)
        {
            _checkedCallback = value;
        }

        void IButton::tickEvent(
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
                _iconImage.reset();
                p.checkedIconInit = true;
                p.checkedIconFuture = std::future<std::shared_ptr<Image> >();
                _checkedIconImage.reset();
            }
            if (!_icon.empty() && p.iconInit)
            {
                p.iconInit = false;
                p.iconFuture = event.iconLibrary->request(_icon, event.displayScale);
            }
            if (!_checkedIcon.empty() && p.checkedIconInit)
            {
                p.checkedIconInit = false;
                p.checkedIconFuture = event.iconLibrary->request(_checkedIcon, event.displayScale);
            }
            if (p.iconFuture.valid() &&
                p.iconFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                _iconImage = p.iconFuture.get();
                _setSizeUpdate();
                _setDrawUpdate();
            }
            if (p.checkedIconFuture.valid() &&
                p.checkedIconFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                _checkedIconImage = p.checkedIconFuture.get();
                _setSizeUpdate();
                _setDrawUpdate();
            }
            if (_isMousePressed() && p.repeatClick)
            {
                const float duration = p.repeatClickInit ? .4F : .02F;
                const auto now = std::chrono::steady_clock::now();
                const std::chrono::duration<float> diff = now - p.repeatClickTimer;
                if (diff.count() > duration)
                {
                    _click();
                    p.repeatClickInit = false;
                    p.repeatClickTimer = now;
                }
            }
        }

        void IButton::mouseEnterEvent()
        {
            IWidget::mouseEnterEvent();
            _setDrawUpdate();
            if (_hoveredCallback)
            {
                _hoveredCallback(_isMouseInside());
            }
        }

        void IButton::mouseLeaveEvent()
        {
            IWidget::mouseLeaveEvent();
            _setDrawUpdate();
            if (_hoveredCallback)
            {
                _hoveredCallback(_isMouseInside());
            }
        }

        void IButton::mousePressEvent(MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
            TG_P();
            if (acceptsKeyFocus())
            {
                takeKeyFocus();
            }
            _setDrawUpdate();
            if (_pressedCallback)
            {
                _pressedCallback();
            }
            if (p.repeatClick)
            {
                p.repeatClickInit = true;
                p.repeatClickTimer = std::chrono::steady_clock::now();
            }
        }

        void IButton::mouseReleaseEvent(MouseClickEvent& event)
        {
            IWidget::mouseReleaseEvent(event);
            _setDrawUpdate();
            if (contains(getGeometry(), _getMousePos()))
            {
                _click();
            }
        }

        void IButton::_click()
        {
            TG_P();
            if (_clickedCallback)
            {
                _clickedCallback();
            }
            if (p.checkable)
            {
                _checked = !_checked;
                _setDrawUpdate();
                if (_checkedCallback)
                {
                    _checkedCallback(_checked);
                }
            }
        }

        void IButton::_releaseMouse()
        {
            const bool inside = _isMouseInside();
            IWidget::_releaseMouse();
            if (inside)
            {
                if (_hoveredCallback)
                {
                    _hoveredCallback(false);
                }
            }
        }
    }
}
