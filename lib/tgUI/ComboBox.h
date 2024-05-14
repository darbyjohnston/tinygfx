// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidget.h>

namespace tg
{
    namespace ui
    {
        //! \name Menu Widgets
        ///@{
        
        //! Combo box item.
        struct ComboBoxItem
        {
            ComboBoxItem() = default;
            explicit ComboBoxItem(
                const std::string& text,
                const std::string& icon = std::string());

            std::string text;
            std::string icon;

            bool operator == (const ComboBoxItem&) const;
            bool operator != (const ComboBoxItem&) const;
        };

        //! Combo box.
        class ComboBox : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            ComboBox();

        public:
            virtual ~ComboBox();

            //! Create a new widget.
            static std::shared_ptr<ComboBox> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Create a new widget.
            static std::shared_ptr<ComboBox> create(
                const std::shared_ptr<core::Context>&,
                const std::vector<ComboBoxItem>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Create a new widget.
            static std::shared_ptr<ComboBox> create(
                const std::shared_ptr<core::Context>&,
                const std::vector<std::string>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the items.
            const std::vector<ComboBoxItem>& getItems() const;

            //! Set the items.
            void setItems(const std::vector<ComboBoxItem>&);

            //! Set the items.
            void setItems(const std::vector<std::string>&);

            //! Get the current index.
            int getCurrentIndex() const;

            //! Set the current index.
            void setCurrentIndex(int);

            //! Set the current index callback.
            void setIndexCallback(const std::function<void(int)>&);

            //! Set the current item callback.
            void setItemCallback(const std::function<void(const ComboBoxItem&)>&);

            //! Get the font role.
            FontRole getFontRole() const;

            //! Set the font role.
            void setFontRole(FontRole);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void mouseEnterEvent() override;
            void mouseLeaveEvent() override;
            void mousePressEvent(MouseClickEvent&) override;
            void mouseReleaseEvent(MouseClickEvent&) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            ComboBoxItem _getItem(int) const;

            void _click();
            void _commit(int);

            TG_PRIVATE();
        };
        
        ///@}
    }
}
