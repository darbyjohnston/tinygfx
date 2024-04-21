// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWindow.h>

namespace tg
{
    namespace ui_test
    {
        class Window : public ui::IWindow
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& name,
                const core::Size2I&);

            Window();

        public:
            virtual ~Window();

            static std::shared_ptr<Window> create(
                const std::shared_ptr<core::Context>&,
                const std::string& name,
                const core::Size2I&);

            void setGeometry(const core::Box2I&) override;
            void tickEvent(
                bool parentsVisible,
                bool parentsEnabled,
                const ui::TickEvent&) override;
            void sizeHintEvent(const ui::SizeHintEvent&) override;

        private:
            TG_PRIVATE();
        };
    }
}

