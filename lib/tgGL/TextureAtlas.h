// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgGL/Texture.h>

#include <tgCore/Image.h>
#include <tgCore/Range.h>

namespace tg
{
    namespace gl
    {
        //! Texture atlas item.
        struct TextureAtlasItem
        {
            int w = 0;
            int h = 0;
            size_t textureIndex = 0;
            core::RangeF textureU;
            core::RangeF textureV;
        };

        //! Texture atlas item ID.
        typedef uint64_t TextureAtlasID;

        //! OpenGL texture atlas.
        class TextureAtlas : public std::enable_shared_from_this<TextureAtlas>
        {
            TG_NON_COPYABLE(TextureAtlas);

        protected:
            void _init(
                size_t textureCount,
                int textureSize,
                core::PixelType textureType,
                TextureFilter filter,
                int border);

            TextureAtlas();

        public:
            ~TextureAtlas();

            //! Create a new texture atlas.
            static std::shared_ptr<TextureAtlas> create(
                size_t textureCount,
                int textureSize,
                core::PixelType textureType,
                TextureFilter filter = TextureFilter::Linear,
                int border = 1);

            size_t getTextureCount() const;
            int getTextureSize() const;
            core::PixelType getTextureType() const;
            std::vector<unsigned int> getTextures() const;

            bool getItem(TextureAtlasID, TextureAtlasItem&);

            TextureAtlasID addItem(
                const std::shared_ptr<core::Image>&,
                TextureAtlasItem&);

            float getPercentageUsed() const;

        private:
            TG_PRIVATE();
        };
    }
}
