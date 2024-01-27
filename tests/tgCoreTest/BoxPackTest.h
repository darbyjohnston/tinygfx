// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

#include <tgCore/BoxPack.h>

namespace tg
{
    namespace core_test
    {
        class BoxPackTest : public test::ITest
        {
        protected:
            BoxPackTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~BoxPackTest();

            static std::shared_ptr<BoxPackTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _printPack(const std::shared_ptr<core::BoxPack>&);
            void _printNode(
                const std::shared_ptr<core::BoxPackNode>&,
                int indent = 0,
                char pad = ' ');
        };
    }
}

