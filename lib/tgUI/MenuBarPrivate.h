// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/MenuBar.h>

#include <tgUI/IButton.h>

namespace tg
{
    namespace ui
    {
        class MenuBarButton : public IButton
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string&,
                const std::shared_ptr<Menu>&,
                const std::shared_ptr<IWidget>& parent);

            MenuBarButton();

        public:
            virtual ~MenuBarButton();

            static std::shared_ptr<MenuBarButton> create(
                const std::shared_ptr<core::Context>&,
                const std::string&,
                const std::shared_ptr<Menu>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            bool getCurrent() const;
            void setCurrent(bool);

            void sizeHintEvent(const SizeHintEvent&) override;
            void clipEvent(const core::Box2I&, bool) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;

        private:
            TG_PRIVATE();
        };
    }
}
