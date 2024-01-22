// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgBaseApp/IApp.h>

#include <tgCore/Context.h>
#include <tgCore/Init.h>
#include <tgCore/Format.h>
#include <tgCore/OS.h>

#include <iostream>

namespace tg
{
    namespace base_app
    {
        std::vector<std::string> convert(int argc, char** argv)
        {
            std::vector<std::string> out;
            for (int i = 0; i < argc; ++i)
            {
                out.push_back(argv[i]);
            }
            return out;
        }

        struct IApp::Private
        {
            std::string name;
            std::shared_ptr<core::ListObserver<core::LogItem> > logObserver;
        };
        
        void IApp::_init(
            const std::shared_ptr<core::Context>& context,
            const std::string& name,
            std::vector<std::string>& args)
        {
            TG_P();

            core::init(context);

            _context = context;
            p.name = name;

            auto logSystem = context->getSystem<core::LogSystem>();            
            p.logObserver = core::ListObserver<core::LogItem>::create(
                logSystem->observeLogItems(),
                [this](const std::vector<core::LogItem>& value)
                {
                    _print(value);
                });
            logSystem->print(name, "Starting...");
            const auto systemInfo = core::getSystemInfo();
            logSystem->print(name, core::Format(
                "System information:\n"
                "    Name:  {0}\n"
                "    Cores: {1}\n"
                "    RAM:   {2}GB").
                arg(systemInfo.name).
                arg(systemInfo.cores).
                arg(systemInfo.ramGB));
            _print(logSystem->getLogItems());
        }

        IApp::IApp() :
            _p(new Private)
        {}

        IApp::~IApp()
        {
            TG_P();
            auto logSystem = _context->getSystem<core::LogSystem>();
            logSystem->print(p.name, "Exiting...");
            _print(logSystem->getLogItems());
        }

        void IApp::_print(const std::vector<core::LogItem>& value)
        {
            for (const auto& item : value)
            {
                std::cout << "LOG: " << core::toString(item) << std::endl;
            }
        }
    }
}

