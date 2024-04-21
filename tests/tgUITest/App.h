// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgBaseApp/IApp.h>

namespace tg
{
    namespace ui
    {
        class IWidget;
        class TickEvent;
    }

    namespace ui_test
    {
        class Window;

        class App : public app::IApp
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>&,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<app::ICmdLineArg> >& = {},
                const std::vector<std::shared_ptr<app::ICmdLineOption> >& = {});

            App();

        public:
            virtual ~App();

            static std::shared_ptr<App> create(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>&,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<app::ICmdLineArg> >& = {},
                const std::vector<std::shared_ptr<app::ICmdLineOption> >& = {});

            void addWindow(const std::shared_ptr<Window>&);
            void removeWindow(const std::shared_ptr<Window>&);

            void exit();

            int run() override;

        private:
            void _tickRecursive(
                const std::shared_ptr<ui::IWidget>&,
                bool visible,
                bool enabled,
                const ui::TickEvent&);
            
            void _log();

            TG_PRIVATE();
        };
    }
}
