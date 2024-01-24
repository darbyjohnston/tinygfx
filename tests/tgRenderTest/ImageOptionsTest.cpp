// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgRenderTest/ImageOptionsTest.h>

#include <tgRender/ImageOptions.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::render;

namespace tg
{
    namespace render_test
    {
        ImageOptionsTest::ImageOptionsTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::render_test::ImageOptionsTest")
        {}

        ImageOptionsTest::~ImageOptionsTest()
        {}

        std::shared_ptr<ImageOptionsTest> ImageOptionsTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ImageOptionsTest>(new ImageOptionsTest(context));
        }
        
        void ImageOptionsTest::run()
        {
            _enums();
            _operators();
        }
        
        void ImageOptionsTest::_enums()
        {
            TINYGFX_TEST_ENUM(InputVideoLevels);
            TINYGFX_TEST_ENUM(AlphaBlend);
            TINYGFX_TEST_ENUM(ImageFilter);
        }
        
        void ImageOptionsTest::_operators()
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

