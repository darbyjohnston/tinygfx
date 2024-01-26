// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgBaseApp/IApp.h>

namespace tg
{
    namespace ui
    {
        class Window;

        //! Base user interface application class.
        class App : public app::IApp
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>& argv,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<app::ICmdLineArg> >& = {},
                const std::vector<std::shared_ptr<app::ICmdLineOption> >& = {});

            App();

        public:
            virtual ~App();

            //! Create a new application.
            static std::shared_ptr<App> create(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>& argv,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<app::ICmdLineArg> >& = {},
                const std::vector<std::shared_ptr<app::ICmdLineOption> >& = {});

            //! Add a window.
            void addWindow(const std::shared_ptr<Window>&);

            //! Remove a window.
            void removeWindow(const std::shared_ptr<Window>&);

            int run() override;

        private:
            TG_PRIVATE();
        };
    }
}

