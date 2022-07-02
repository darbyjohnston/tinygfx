// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgTestLib/ITest.h>

#include <iostream>

namespace tg
{
    namespace tests
    {
        ITest::ITest(const std::string& name) :
            _name(name)
        {}

        ITest::~ITest()
        {}

        const std::string& ITest::getName() const
        {
            return _name;
        }

        void ITest::_print(const std::string& value)
        {
            std::cout << "    " << value << std::endl;
        }

        void ITest::_printError(const std::string& value)
        {
            std::cout << "    ERROR: " << value << std::endl;
        }
    }
}
