// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidget.h>

namespace tg
{
    namespace ui
    {
        //! \name Buttons
        ///@{
        
        //! Base class for buttons.
        class IButton : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& objectName,
                const std::shared_ptr<IWidget>& parent = nullptr);

            IButton();

        public:
            virtual ~IButton();

            //! Get whether the button is checkable.
            bool isCheckable() const;

            //! Set whether the button is checkable.
            void setCheckable(bool);

            //! Get whether the button is checked.
            bool isChecked() const;

            //! Set whether the button is checked.
            void setChecked(bool);

            //! Get the text.
            const std::string& getText() const;

            //! Set the text.
            virtual void setText(const std::string&);

            //! Get the font role.
            FontRole getFontRole() const;

            //! Set the font role.
            virtual void setFontRole(FontRole);

            //! Get the icon.
            const std::string& getIcon() const;

            //! Set the icon.
            void setIcon(const std::string&);

            //! Get the checked icon.
            const std::string& getCheckedIcon() const;

            //! Set the checked icon.
            void setCheckedIcon(const std::string&);

            //! Get the button color role.
            ColorRole getButtonRole() const;

            //! Set the button color role.
            void setButtonRole(ColorRole);

            //! Get the checked color role.
            ColorRole getCheckedRole() const;

            //! Set the checked color role.
            void setCheckedRole(ColorRole);

            //! Set the hovered callback.
            void setHoveredCallback(const std::function<void(bool)>&);

            //! Set the pressed callback.
            void setPressedCallback(const std::function<void(void)>&);

            //! Set whether the button repeats clicks when pressed.
            void setRepeatClick(bool);

            //! Set the clicked callback.
            void setClickedCallback(const std::function<void(void)>&);

            //! Set the checked callback.
            void setCheckedCallback(const std::function<void(bool)>&);

            void tickEvent(
                bool,
                bool,
                const TickEvent&) override;
            void mouseEnterEvent() override;
            void mouseLeaveEvent() override;
            void mousePressEvent(MouseClickEvent&) override;
            void mouseReleaseEvent(MouseClickEvent&) override;

        protected:
            void _click();

            void _releaseMouse() override;

            std::string _text;
            FontRole _fontRole = FontRole::Label;
            std::string _icon;
            std::shared_ptr<core::Image> _iconImage;
            std::string _checkedIcon;
            std::shared_ptr<core::Image> _checkedIconImage;
            ColorRole _buttonRole = ColorRole::Button;
            ColorRole _checkedRole = ColorRole::Checked;
            bool _checked = false;
            std::function<void(bool)> _hoveredCallback;
            std::function<void(void)> _pressedCallback;
            std::function<void(void)> _clickedCallback;
            std::function<void(bool)> _checkedCallback;

        private:
            TG_PRIVATE();
        };
        
        ///@}
    }
}
