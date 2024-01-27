// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGL/TextureAtlas.h>

#include <tgGL/Texture.h>

#include <tgCore/Assert.h>
#include <tgCore/BoxPack.h>

#include <map>

using namespace tg::core;

namespace tg
{
    namespace gl
    {
        struct TextureAtlas::Private
        {
            int textureSize = 0;
            PixelType textureType = PixelType::None;
            int border = 0;
            std::shared_ptr<Texture> texture;
            std::shared_ptr<BoxPack> boxPack;
        };

        void TextureAtlas::_init(
            int textureSize,
            PixelType textureType,
            TextureFilter filter,
            int border)
        {
            TG_P();

            p.textureSize = textureSize;
            p.textureType = textureType;
            p.border = border;
            TextureOptions textureOptions;
            textureOptions.filters.minify = filter;
            textureOptions.filters.magnify = filter;
            p.texture = Texture::create(
                ImageInfo(textureSize, textureSize, textureType),
                textureOptions);
            p.boxPack = BoxPack::create(
                Size2I(textureSize, textureSize),
                border);
        }

        TextureAtlas::TextureAtlas() :
            _p(new Private)
        {}

        TextureAtlas::~TextureAtlas()
        {}

        std::shared_ptr<TextureAtlas> TextureAtlas::create(
            int textureSize,
            PixelType textureType,
            TextureFilter filter,
            int border)
        {
            auto out = std::shared_ptr<TextureAtlas>(new TextureAtlas);
            out->_init(textureSize, textureType, filter, border);
            return out;
        }

        int TextureAtlas::getTextureSize() const
        {
            return _p->textureSize;
        }

        PixelType TextureAtlas::getTextureType() const
        {
            return _p->textureType;
        }

        unsigned int TextureAtlas::getTexture() const
        {
            return _p->texture->getID();
        }

        bool TextureAtlas::getItem(BoxPackID id, TextureAtlasItem& item)
        {
            TG_P();
            bool out = false;
            if (auto node = p.boxPack->getNode(id))
            {
                _toTextureAtlasItem(node, item);
                out = true;
            }
            return out;
        }

        bool TextureAtlas::addItem(
            const std::shared_ptr<Image>& image,
            TextureAtlasItem& item)
        {
            TG_P();
            bool out = false;
            if (auto node = p.boxPack->insert(image->getSize()))
            {
                out = true;

                auto zero = Image::create(node->box.size(), PixelType::L_U8);
                zero->zero();
                p.texture->copy(
                    zero,
                    node->box.min.x,
                    node->box.min.y);

                p.texture->copy(
                    image,
                    node->box.min.x + p.border,
                    node->box.min.y + p.border);

                _toTextureAtlasItem(node, item);
            }
            return out;
        }

        float TextureAtlas::getPercentageUsed() const
        {
            TG_P();
            float area = 0.F;
            for (const auto node : p.boxPack->getNodes())
            {
                if (node->id != boxPackIDInvalid)
                {
                    area += core::area(node->box.size());
                }
            }
            return area / static_cast<float>(p.textureSize * p.textureSize);
        }

        void TextureAtlas::_toTextureAtlasItem(
            const std::shared_ptr<BoxPackNode>& node,
            TextureAtlasItem& out)
        {
            TG_P();
            out.id = node->id;
            const Size2I size = node->box.size() - p.border * 2;
            out.textureU = RangeF(
                (node->box.min.x + p.border) / static_cast<float>(p.textureSize),
                (node->box.min.x + p.border + size.w + 0) / static_cast<float>(p.textureSize));
            out.textureV = RangeF(
                (node->box.min.y + p.border) / static_cast<float>(p.textureSize),
                (node->box.min.y + p.border + size.h + 0) / static_cast<float>(p.textureSize));
        }
    }
}
