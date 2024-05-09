// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/ComboBox.h>
#include <tgUI/IMenuPopup.h>

namespace tg
{
    namespace ui
    {
        class ComboBoxWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::vector<ComboBoxItem>&,
                int currentIndex,
                const std::shared_ptr<IWidget>& parent);

            ComboBoxWidget();

        public:
            virtual ~ComboBoxWidget();

            static std::shared_ptr<ComboBoxWidget> create(
                const std::shared_ptr<core::Context>&,
                const std::vector<ComboBoxItem>&,
                int currentIndex,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void setCallback(const std::function<void(int)>&);

            int getCurrent() const;
            void setCurrent(int);
            std::shared_ptr<core::IObservableValue<int> > observeCurrent() const;

            core::Box2I getRect(int) const;

            void setGeometry(const core::Box2I&) override;
            void tickEvent(bool, bool, const TickEvent&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void mouseLeaveEvent() override;
            void mouseMoveEvent(MouseMoveEvent&) override;
            void mousePressEvent(MouseClickEvent&) override;
            void mouseReleaseEvent(MouseClickEvent&) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            int _posToIndex(int) const;

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

        private:
            TG_PRIVATE();
        };
    }
}
