// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/ComboBox.h>
#include <tgUI/IButton.h>
#include <tgUI/IMenuPopup.h>

namespace tg
{
    namespace ui
    {
        class ComboBoxButton : public IButton
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const ComboBoxItem&,
                const std::shared_ptr<IWidget>& parent);

            ComboBoxButton();

        public:
            virtual ~ComboBoxButton();

            static std::shared_ptr<ComboBoxButton> create(
                const std::shared_ptr<core::Context>&,
                const ComboBoxItem&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            bool getCurrent() const;
            void setCurrent(bool);

            void sizeHintEvent(const SizeHintEvent&) override;
            void clipEvent(const core::Box2I&, bool) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;

        private:
            TG_PRIVATE();
        };

        class ComboBoxMenu : public IMenuPopup
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::vector<ComboBoxItem>&,
                int currentIndex,
                const std::shared_ptr<IWidget>& parent);

            ComboBoxMenu();

        public:
            virtual ~ComboBoxMenu();

            static std::shared_ptr<ComboBoxMenu> create(
                const std::shared_ptr<core::Context>&,
                const std::vector<ComboBoxItem>&,
                int currentIndex,
                const std::shared_ptr<IWidget>& parent = nullptr);

            int getCurrent() const;
            void setCurrent(int);
            void setCallback(const std::function<void(int)>&);

            void setGeometry(const core::Box2I&) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            void _scrollToCurrent();

            TG_PRIVATE();
        };
    }
}
