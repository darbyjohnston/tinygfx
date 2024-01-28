// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_test
    {
        class ImageIOTest : public test::ITest
        {
        protected:
            ImageIOTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ImageIOTest();

            static std::shared_ptr<ImageIOTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
            
        private:
            void _members();
            void _functions();
        };
    }
}

