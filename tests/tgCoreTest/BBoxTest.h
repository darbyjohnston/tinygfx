// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgTestLib/ITest.h>

namespace tg
{
    namespace core_tests
    {
        class BBoxTest : public tests::ITest
        {
        protected:
            BBoxTest();

        public:
            static std::shared_ptr<BBoxTest> create();

            void run() override;

        private:
            void _ctors();
            void _components();
            void _dimensions();
            void _intersections();
            void _expand();
            void _margin();
            void _operators();
        };
    }
}
