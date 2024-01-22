// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_test
    {
        class MeshTest : public test::ITest
        {
        protected:
            MeshTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~MeshTest();

            static std::shared_ptr<MeshTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _members();
            void _functions();
        };
    }
}

