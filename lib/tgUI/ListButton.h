// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IButton.h>

namespace tg
{
    namespace ui
    {
        //! \name Buttons
        ///@{
        
        //! List button.
        class ListButton : public IButton
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            ListButton();

        public:
            virtual ~ListButton();

            //! Create a new widget.
            static std::shared_ptr<ListButton> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Create a new widget.
            static std::shared_ptr<ListButton> create(
                const std::shared_ptr<core::Context>&,
                const std::string&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the label margin role.
            void setLabelMarginRole(SizeRole);

            void setText(const std::string&) override;
            void setFontRole(FontRole) override;

            void sizeHintEvent(const SizeHintEvent&) override;
            void clipEvent(const core::Box2I&, bool) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            TG_PRIVATE();
        };
        
        ///@}
    }
}
