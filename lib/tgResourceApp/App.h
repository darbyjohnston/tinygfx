// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgBaseApp/IApp.h>

namespace tg
{
    //! Resource application
    namespace resource
    {
        //! Resource application.
        class App : public app::IApp
        {
            TG_NON_COPYABLE(App);

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

            void run() override;

        private:
            std::string _input;
            std::string _output;
            std::string _varName;
            std::chrono::steady_clock::time_point _startTime;
        };
    }
}

