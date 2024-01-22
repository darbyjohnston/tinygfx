// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgBaseApp/IApp.h>

namespace tg
{
    namespace ui
    {
        class IWindow;

        //! Base user interface application class.
        class IApp : public app::IApp
        {
            TG_NON_COPYABLE(IApp);

        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>& argv,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<app::ICmdLineArg> >& = {},
                const std::vector<std::shared_ptr<app::ICmdLineOption> >& = {});

            IApp();

        public:
            virtual ~IApp() = 0;

            //! Add a window.
            void addWindow(const std::shared_ptr<IWindow>&);

            //! Remove a window.
            void removeWindow(const std::shared_ptr<IWindow>&);

            int run() override;

        private:
            TG_PRIVATE();
        };
    }
}

