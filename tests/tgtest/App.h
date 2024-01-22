// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgBaseApp/IApp.h>

namespace tg
{
    namespace tests
    {
        //! Test application.
        class App : public base_app::IApp
        {
            TG_NON_COPYABLE(App);

        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& name,
                std::vector<std::string>& args);

            App();

        public:
            virtual ~App();
            
            static std::shared_ptr<App> create(
                const std::shared_ptr<core::Context>&,
                const std::string& name,
                std::vector<std::string>& args);

            int run();
            
        private:
            TG_PRIVATE();
        };
    }
}

