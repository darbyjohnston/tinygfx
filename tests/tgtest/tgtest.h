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
        class App : public app::IApp
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>& argv);

            App();

        public:
            virtual ~App();
            
            static std::shared_ptr<App> create(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>& argv);

            int run() override;
            
        private:
            TG_PRIVATE();
        };
    }
}

