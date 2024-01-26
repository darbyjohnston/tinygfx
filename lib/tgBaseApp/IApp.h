// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/LogSystem.h>

#include <memory>
#include <string>
#include <vector>

#if defined(_WINDOWS)
#define TG_MAIN() \
    int wmain(int argc, wchar_t* argv[])
#else // _WINDOWS
#define TG_MAIN() \
    int main(int argc, char* argv[])
#endif // _WINDOWS

namespace tg
{
    namespace core
    {
        class Context;
    }

    //! Applications
    namespace app
    {
        class ICmdLineArg;
        class ICmdLineOption;

        //! Application options.
        struct Options
        {
            bool log = false;
            bool help = false;
        };
        
        //! Convert command line arguments.
        std::vector<std::string> convert(int argc, char** argv);

        //! Convert command line arguments.
        std::vector<std::string> convert(int argc, wchar_t* argv[]);

        //! Base application class.
        class IApp : public std::enable_shared_from_this<IApp>
        {
            TG_NON_COPYABLE(IApp);

        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>& argv,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<ICmdLineArg> >& = {},
                const std::vector<std::shared_ptr<ICmdLineOption> >& = {});

            IApp();

        public:
            virtual ~IApp() = 0;

            //! Get the exit code.
            int getExit() const;

            //! Run the application.
            virtual int run() = 0;

        protected:
            void _print(const std::string&);
            void _printError(const std::string&);

            std::shared_ptr<core::Context> _context;
        
        private:
            int _parseCmdLine();
            void _printCmdLineHelp();

            void _print(const std::vector<core::LogItem>&);

            TG_PRIVATE();
        };
    }
}

