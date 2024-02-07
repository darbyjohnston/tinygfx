// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/Menu.h>

namespace tg
{
    namespace ui
    {
        class Action;

        //! Menu bar.
        class MenuBar : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            MenuBar();

        public:
            virtual ~MenuBar();

            //! Create a new widget.
            static std::shared_ptr<MenuBar> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Add a menu.
            void addMenu(
                const std::string& text,
                const std::shared_ptr<Menu>&);

            //! Handle keyboard shortcuts.
            bool shortcut(Key, int);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            TG_PRIVATE();
        };
    }
}
