// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_test
    {
        class ImageTest : public test::ITest
        {
        protected:
            ImageTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ImageTest();

            static std::shared_ptr<ImageTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
            
        private:
            void _enums();
            void _info();
            void _members();
        };
    }
}

