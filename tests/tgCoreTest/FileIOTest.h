// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class FileIOTest : public tests::ITest
        {
        protected:
            FileIOTest();

        public:
            static std::shared_ptr<FileIOTest> create();

            void run() override;

        private:
            std::string _fileName;
            std::string _text;
            std::string _text2;
        };
    }
}
