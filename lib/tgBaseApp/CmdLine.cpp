// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgBaseApp/CmdLine.h>

namespace tg
{
    namespace app
    {
        ICmdLineOption::ICmdLineOption(
            const std::vector<std::string>& names,
            const std::string& help) :
            _names(names),
            _help(help)
        {}

        ICmdLineOption::~ICmdLineOption()
        {}

        CmdLineFlagOption::CmdLineFlagOption(
            bool& value,
            const std::vector<std::string>&names,
            const std::string & help) :
            ICmdLineOption(names, help),
            _value(value)
        {}

        std::shared_ptr<CmdLineFlagOption> CmdLineFlagOption::create(
            bool& value,
            const std::vector<std::string>& names,
            const std::string& help)
        {
            return std::shared_ptr<CmdLineFlagOption>(new CmdLineFlagOption(value, names, help));
        }

        void CmdLineFlagOption::parse(std::vector<std::string>&args)
        {
            for (const auto& name : _names)
            {
                auto i = std::find(args.begin(), args.end(), name);
                if (i != args.end())
                {
                    _matchedName = name;
                    _value = true;
                    i = args.erase(i);
                }
            }
        }

        std::vector<std::string> CmdLineFlagOption::getHelp() const
        {
            std::vector<std::string> out;
            out.push_back(core::join(_names, ", "));
            out.push_back(_help);
            return out;
        }
    }
}
