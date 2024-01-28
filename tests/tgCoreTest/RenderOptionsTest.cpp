// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/RenderOptionsTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>
#include <tgCore/RenderOptions.h>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        RenderOptionsTest::RenderOptionsTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::RenderOptionsTest")
        {}

        RenderOptionsTest::~RenderOptionsTest()
        {}

        std::shared_ptr<RenderOptionsTest> RenderOptionsTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<RenderOptionsTest>(new RenderOptionsTest(context));
        }
        
        void RenderOptionsTest::run()
        {
            _enums();
            _operators();
        }
        
        void RenderOptionsTest::_enums()
        {
            TINYGFX_TEST_ENUM(InputVideoLevels);
            TINYGFX_TEST_ENUM(AlphaBlend);
            TINYGFX_TEST_ENUM(ImageFilter);
        }
        
        void RenderOptionsTest::_operators()
        {
            {
                const ImageFilters a;
                ImageFilters b;
                TG_ASSERT(a == b);
                b.minify = ImageFilter::Nearest;
                TG_ASSERT(a != b);
            }
            {
                const ImageOptions a;
                ImageOptions b;
                TG_ASSERT(a == b);
                b.cache = false;
                TG_ASSERT(a != b);
            }
        }
    }
}

