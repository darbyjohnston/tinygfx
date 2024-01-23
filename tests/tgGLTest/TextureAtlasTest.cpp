// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGLTest/TextureAtlasTest.h>

#include <tgGL/TextureAtlas.h>
#include <tgGL/Window.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::gl;

namespace tg
{
    namespace gl_test
    {
        TextureAtlasTest::TextureAtlasTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::gl_test::TextureAtlasTest")
        {}

        TextureAtlasTest::~TextureAtlasTest()
        {}

        std::shared_ptr<TextureAtlasTest> TextureAtlasTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<TextureAtlasTest>(new TextureAtlasTest(context));
        }
        
        namespace
        {
            std::shared_ptr<Window> createWindow(
                const std::shared_ptr<Context>& context)
            {
                return Window::create(
                    context,
                    "TextureAtlasTest",
                    Size2I(100, 100),
                    static_cast<int>(WindowOptions::MakeCurrent));
            }
            
            std::string format(const TextureAtlasItem& item)
            {
                return Format(
                    "Item: w={0}, h={1}, textureIndex={2}, textureU={3}-{4}, textureV={5}-{6}").
                    arg(item.w).
                    arg(item.h).
                    arg(item.textureIndex).
                    arg(item.textureU.min()).
                    arg(item.textureU.max()).
                    arg(item.textureV.min()).
                    arg(item.textureV.max());
            }
        }
        
        void TextureAtlasTest::run()
        {
            if (auto context = _context.lock())
            {
                auto window = createWindow(context);
                
                auto atlas = TextureAtlas::create(
                    1,
                    1024,
                    PixelType::L_U8,
                    TextureFilter::Linear,
                    0);
                TG_ASSERT(1 == atlas->getTextureCount());
                TG_ASSERT(1024 == atlas->getTextureSize());
                TG_ASSERT(PixelType::L_U8 == atlas->getTextureType());
                TG_ASSERT(!atlas->getTextures().empty());
                
                for (size_t i = 0; i < 10; ++i)
                {
                    auto image = Image::create(512, 512, PixelType::L_U8);
                    TextureAtlasItem item;
                    TextureAtlasID id = atlas->addItem(image, item);
                    TG_ASSERT(atlas->getItem(id, item));
                    _print(format(item));
                    _print(Format("Percentage: {0}").arg(atlas->getPercentageUsed()));
                }
            }
        }
    }
}

