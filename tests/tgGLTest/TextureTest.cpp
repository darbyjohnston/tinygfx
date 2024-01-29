// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGLTest/TextureTest.h>

#include <tgGL/Texture.h>
#include <tgGL/Window.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::gl;

namespace tg
{
    namespace gl_test
    {
        TextureTest::TextureTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::gl_test::TextureTest")
        {}

        TextureTest::~TextureTest()
        {}

        std::shared_ptr<TextureTest> TextureTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<TextureTest>(new TextureTest(context));
        }
        
        namespace
        {
            std::shared_ptr<Window> createWindow(
                const std::shared_ptr<Context>& context)
            {
                return Window::create(
                    context,
                    "TextureTest",
                    Size2I(100, 100),
                    static_cast<int>(WindowOptions::MakeCurrent));
            }
        }
        
        void TextureTest::run()
        {
            _enums();
            _members();
            _functions();
            _operators();
        }
        
        void TextureTest::_enums()
        {
            TINYGFX_TEST_ENUM(TextureFilter);
        }
        
        void TextureTest::_members()
        {
            if (auto context = _context.lock())
            {
                auto window = createWindow(context);
                
                struct Data
                {
                    ImageInfo info;
                    TextureOptions options;
                };
                std::vector<Data> dataList;
                for (auto imageType : getImageTypeEnums())
                {
                    dataList.push_back({
                        ImageInfo(1920, 1080, imageType),
                        TextureOptions() });
                }
                {
                    TextureOptions options;
                    options.filters.minify = TextureFilter::Nearest;
                    options.filters.magnify = TextureFilter::Nearest;
                    dataList.push_back({
                        ImageInfo(1920, 1080, ImageType::RGBA_U8),
                        options });
                }
                {
                    TextureOptions options;
                    options.pbo = true;
                    dataList.push_back({
                        ImageInfo(1920, 1080, ImageType::RGBA_U8),
                        options });
                }
                for (const auto& data : dataList)
                {
                    try
                    {
                        _print(Format("Texture: size={0} type={1}, minify={2}, magnify={3}, pbo={4}").
                            arg(data.info.size).
                            arg(data.info.type).
                            arg(data.options.filters.minify).
                            arg(data.options.filters.magnify).
                            arg(data.options.pbo));
                        auto texture = Texture::create(data.info, data.options);
                        TG_ASSERT(data.info == texture->getInfo());
                        TG_ASSERT(data.info.size == texture->getSize());
                        TG_ASSERT(data.info.size.w == texture->getWidth());
                        TG_ASSERT(data.info.size.h == texture->getHeight());
                        TG_ASSERT(data.info.type == texture->getType());
                        if (data.info.type != ImageType::None)
                        {
                            TG_ASSERT(texture->getID());
                            auto image = Image::create(data.info);
                            texture->copy(image);
                            texture->copy(image, 0, 0);
                            texture->copy(image->getData(), image->getInfo());
                            texture->bind();
                        }
                    }
                    catch (const std::exception& e)
                    {
                        _error(e.what());
                    }
                }
            }
        }
        
        void TextureTest::_functions()
        {
            if (auto context = _context.lock())
            {
                auto window = createWindow(context);
            }
        }
        
        void TextureTest::_operators()
        {
            {
                const TextureFilters a;
                TextureFilters b;
                TG_ASSERT(a == b);
                b.minify = TextureFilter::Nearest;
                TG_ASSERT(a != b);
            }
            {
                const TextureOptions a;
                TextureOptions b;
                TG_ASSERT(a == b);
                b.pbo = true;
                TG_ASSERT(a != b);
            }
        }
    }
}

