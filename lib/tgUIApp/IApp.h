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
        class IApp : public base_app::IApp
        {
            TG_NON_COPYABLE(IApp);

        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& name,
                std::vector<std::string>& args);

            IApp();

        public:
            virtual ~IApp() = 0;

            //! Add a window.
            void addWindow(const std::shared_ptr<IWindow>&);

            //! Remove a window.
            void removeWindow(const std::shared_ptr<IWindow>&);

            //! Run the application.
            int run();

        private:
            TG_PRIVATE();
        };
    }
}

