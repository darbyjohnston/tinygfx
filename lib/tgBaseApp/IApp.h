// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/LogSystem.h>

#include <memory>
#include <string>
#include <vector>

namespace tg
{
    namespace core
    {
        class Context;
    }

    namespace base_app
    {
        //! Convert command line arguments.
        std::vector<std::string> convert(int argc, char** argv);

        //! Base application class.
        class IApp : public std::enable_shared_from_this<IApp>
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

        protected:
            std::shared_ptr<core::Context> _context;
        
        private:
            void _print(const std::vector<core::LogItem>&);

            TG_PRIVATE();
        };
    }
}

