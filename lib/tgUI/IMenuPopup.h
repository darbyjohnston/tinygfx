// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IPopup.h>

namespace tg
{
    namespace ui
    {
        class IWindow;

        //! \name Menu Widgets
        ///@{

        //! Popup style.
        enum class MenuPopupStyle
        {
            Menu,
            SubMenu
        };

        //! Base class for popup menus.
        class IMenuPopup : public IPopup
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& objectName,
                const std::shared_ptr<IWidget>& parent = nullptr);

            IMenuPopup();

        public:
            virtual ~IMenuPopup() = 0;

            //! Open the popup.
            void open(
                const std::shared_ptr<IWindow>&,
                const core::Box2I& buttonGeometry);

            //! Get whether the popup is open.
            bool isOpen() const;

            //! Close the popup.
            void close() override;

            //! Set the close callback.
            void setCloseCallback(const std::function<void(void)>&);

            //! Set the popup style.
            void setPopupStyle(MenuPopupStyle);

            //! Set the popup color role.
            void setPopupRole(ColorRole);

            //! Set the widget.
            void setWidget(const std::shared_ptr<IWidget>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;

        private:
            TG_PRIVATE();
        };
        
        ///@}
    }
}
