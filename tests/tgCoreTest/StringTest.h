// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class StringTest : public tests::ITest
        {
        protected:
            StringTest();

        public:
            static std::shared_ptr<StringTest> create();

            void run() override;

        private:
            void _split();
            void _case();
            void _util();
            void _convert();
        };
    }
}
