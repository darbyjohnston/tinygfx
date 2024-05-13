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

            void setCurrent(bool);

            void setGeometry(const core::Box2I&) override;
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

            void setCallback(const std::function<void(int)>&);

            void setGeometry(const core::Box2I&) override;
            void keyFocusEvent(bool) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            void _setCurrent(int);
            void _currentUpdate();
            void _scrollToCurrent();

            TG_PRIVATE();
        };
    }
}
