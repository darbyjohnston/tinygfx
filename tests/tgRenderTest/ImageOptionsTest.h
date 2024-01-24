// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace render_test
    {
        class ImageOptionsTest : public test::ITest
        {
        protected:
            ImageOptionsTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ImageOptionsTest();

            static std::shared_ptr<ImageOptionsTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _enums();
            void _operators();
        };
    }
}

