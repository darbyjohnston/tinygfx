// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/ImageTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>
#include <tgCore/Image.h>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        ImageTest::ImageTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::ImageTest")
        {}

        ImageTest::~ImageTest()
        {}

        std::shared_ptr<ImageTest> ImageTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ImageTest>(new ImageTest(context));
        }
        
        void ImageTest::run()
        {
            _enums();
            _info();
            _members();
        }
        
        void ImageTest::_enums()
        {
            TINYGFX_TEST_ENUM(PixelType);
            for (auto i : getPixelTypeEnums())
            {
                _print(Format("{0} byte count: {1}").arg(i).arg(getByteCount(i)));
            }
        }
        
        void ImageTest::_info()
        {
            {
                const ImageInfo info;
                TG_ASSERT(!info.isValid());
                TG_ASSERT(0 == info.getByteCount());
            }
            {
                const ImageInfo info(Size2I(1920, 1080), PixelType::RGB_U8);
                TG_ASSERT(info.isValid());
                TG_ASSERT(1920 * 1080 * 3 == info.getByteCount());
            }
            {
                const ImageInfo info(1920, 1080, PixelType::RGB_U8);
                TG_ASSERT(info.isValid());
                TG_ASSERT(1920 * 1080 * 3 == info.getByteCount());
            }
            {
                const ImageInfo a;
                ImageInfo b;
                TG_ASSERT(a == b);
                b.size.w() = 1920;
                b.size.h() = 1080;
                TG_ASSERT(a != b);                
            }
        }
        
        void ImageTest::_members()
        {
            {
                auto image = Image::create(ImageInfo());
                TG_ASSERT(!image->isValid());
            }
            {
                auto image = Image::create(Size2I(1920, 1080), PixelType::RGB_U8);
                TG_ASSERT(image->isValid());                
            }
            {
                auto image = Image::create(1920, 1080, PixelType::RGB_U8);
                TG_ASSERT(image->isValid());
            }
            {
                const ImageInfo info(Size2I(1920, 1080), PixelType::RGB_U8);
                auto image = Image::create(info);
                image->zero();
                TG_ASSERT(info == image->getInfo());
                TG_ASSERT(info.size == image->getSize());
                TG_ASSERT(info.size.w() == image->getWidth());
                TG_ASSERT(info.size.h() == image->getHeight());
                const float aspect = image->getAspect();
                TG_ASSERT(info.pixelType == image->getPixelType());
                TG_ASSERT(image->isValid());
                TG_ASSERT(1920 * 1080 * 3 == image->getByteCount());
                TG_ASSERT(image->getData());
                const std::shared_ptr<const Image> image2 = image;
                TG_ASSERT(image2->getData());
            }
        }
    }
}

