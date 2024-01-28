// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGL/RenderPrivate.h>

using namespace tg::core;

namespace tg
{
    namespace gl
    {
        void Render::drawRect(
            const Box2F& box,
            const Color4F& color)
        {
            TG_P();

            p.shaders["rect"]->bind();
            p.shaders["rect"]->setUniform("color", color);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            if (p.vbos["rect"])
            {
                p.vbos["rect"]->copy(convert(mesh(box), p.vbos["rect"]->getType()));
            }
            if (p.vaos["rect"])
            {
                p.vaos["rect"]->bind();
                p.vaos["rect"]->draw(GL_TRIANGLES, 0, p.vbos["rect"]->getSize());
            }
        }
        
        void Render::drawLine(
            const V2F& v0,
            const V2F& v1,
            const Color4F& color,
            const render::LineOptions& options)
        {
            TG_P();

            p.shaders["line"]->bind();
            p.shaders["line"]->setUniform("color", color);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            const V2F v2 = normalize(v1 - v0);
            const float w = options.width / 2.F;
            const V2F v2cw = normalize(perpCW(v2)) * w;
            const V2F v2ccw = normalize(perpCCW(v2)) * w;
            TriMesh2F mesh;
            mesh.v.push_back(v0 + v2ccw);
            mesh.v.push_back(v0 + v2cw);
            mesh.v.push_back(v1 + v2cw);
            mesh.v.push_back(v1 + v2ccw);
            Triangle2 triangle;
            triangle.v[0].v = 1;
            triangle.v[1].v = 2;
            triangle.v[2].v = 3;
            mesh.triangles.push_back(triangle);
            triangle.v[0].v = 3;
            triangle.v[1].v = 4;
            triangle.v[2].v = 1;
            mesh.triangles.push_back(triangle);

            if (p.vbos["line"])
            {
                p.vbos["line"]->copy(convert(mesh, p.vbos["line"]->getType()));
            }
            if (p.vaos["line"])
            {
                p.vaos["line"]->bind();
                p.vaos["line"]->draw(GL_TRIANGLES, 0, p.vbos["line"]->getSize());
            }
        }

        void Render::drawMesh(
            const TriMesh2F& mesh,
            const Color4F& color,
            const V2F& pos)
        {
            TG_P();
            const size_t size = mesh.triangles.size();
            if (size > 0)
            {
                p.shaders["mesh"]->bind();
                const auto transform =
                    p.transform *
                    translate(V3F(pos.x, pos.y, 0.F));
                p.shaders["mesh"]->setUniform("transform.mvp", transform);
                p.shaders["mesh"]->setUniform("color", color);

                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                if (!p.vbos["mesh"] || (p.vbos["mesh"] && p.vbos["mesh"]->getSize() < size * 3))
                {
                    p.vbos["mesh"] = VBO::create(size * 3, VBOType::Pos2_F32);
                    p.vaos["mesh"].reset();
                }
                if (p.vbos["mesh"])
                {
                    p.vbos["mesh"]->copy(convert(mesh, VBOType::Pos2_F32));
                }

                if (!p.vaos["mesh"] && p.vbos["mesh"])
                {
                    p.vaos["mesh"] = VAO::create(p.vbos["mesh"]->getType(), p.vbos["mesh"]->getID());
                }
                if (p.vaos["mesh"] && p.vbos["mesh"])
                {
                    p.vaos["mesh"]->bind();
                    p.vaos["mesh"]->draw(GL_TRIANGLES, 0, size * 3);
                }
            }
        }
        
        void Render::drawColorMesh(
            const TriMesh2F& mesh,
            const Color4F& color,
            const V2F& pos)
        {
            TG_P();
            const size_t size = mesh.triangles.size();
            if (size > 0)
            {
                p.shaders["colorMesh"]->bind();
                const auto transform =
                    p.transform *
                    translate(V3F(pos.x, pos.y, 0.F));
                p.shaders["colorMesh"]->setUniform("transform.mvp", transform);
                p.shaders["colorMesh"]->setUniform("color", color);

                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                if (!p.vbos["colorMesh"] || (p.vbos["colorMesh"] && p.vbos["colorMesh"]->getSize() < size * 3))
                {
                    p.vbos["colorMesh"] = VBO::create(size * 3, VBOType::Pos2_F32_Color_F32);
                    p.vaos["colorMesh"].reset();
                }
                if (p.vbos["colorMesh"])
                {
                    p.vbos["colorMesh"]->copy(convert(mesh, VBOType::Pos2_F32_Color_F32));
                }

                if (!p.vaos["colorMesh"] && p.vbos["colorMesh"])
                {
                    p.vaos["colorMesh"] = VAO::create(p.vbos["colorMesh"]->getType(), p.vbos["colorMesh"]->getID());
                }
                if (p.vaos["colorMesh"] && p.vbos["colorMesh"])
                {
                    p.vaos["colorMesh"]->bind();
                    p.vaos["colorMesh"]->draw(GL_TRIANGLES, 0, size * 3);
                }
            }
        }

        void Render::drawText(
            const std::vector<std::shared_ptr<Glyph> >& glyphs,
            const V2F& pos,
            const Color4F& color)
        {
            TG_P();

            p.shaders["text"]->bind();
            p.shaders["text"]->setUniform("color", color);
            p.shaders["text"]->setUniform("textureSampler", 0);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glActiveTexture(static_cast<GLenum>(GL_TEXTURE0));
            glBindTexture(GL_TEXTURE_2D, p.glyphTextureAtlas->getTexture());

            int x = 0;
            int32_t rsbDeltaPrev = 0;
            TriMesh2F mesh;
            size_t meshIndex = 0;
            for (const auto& glyph : glyphs)
            {
                if (glyph)
                {
                    if (rsbDeltaPrev - glyph->lsbDelta > 32)
                    {
                        x -= 1;
                    }
                    else if (rsbDeltaPrev - glyph->lsbDelta < -31)
                    {
                        x += 1;
                    }
                    rsbDeltaPrev = glyph->rsbDelta;

                    if (glyph->image && glyph->image->isValid())
                    {
                        BoxPackID id = boxPackInvalidID;
                        const auto i = p.glyphIDs.find(glyph->info);
                        if (i != p.glyphIDs.end())
                        {
                            id = i->second;
                        }
                        TextureAtlasItem item;
                        if (boxPackInvalidID == id ||
                            !p.glyphTextureAtlas->getItem(id, item))
                        {
                            p.glyphTextureAtlas->addItem(glyph->image, item);
                            p.glyphIDs[glyph->info] = item.id;
                        }

                        const V2I& offset = glyph->offset;
                        const Box2I box(
                            pos.x + x + offset.x,
                            pos.y - offset.y,
                            glyph->image->getWidth(),
                            glyph->image->getHeight());
                        const auto& min = box.min;
                        const auto& max = box.max;

                        mesh.v.push_back(V2F(min.x, min.y));
                        mesh.v.push_back(V2F(max.x + 1, min.y));
                        mesh.v.push_back(V2F(max.x + 1, max.y + 1));
                        mesh.v.push_back(V2F(min.x, max.y + 1));
                        mesh.t.push_back(V2F(item.textureU.min(), item.textureV.min()));
                        mesh.t.push_back(V2F(item.textureU.max(), item.textureV.min()));
                        mesh.t.push_back(V2F(item.textureU.max(), item.textureV.max()));
                        mesh.t.push_back(V2F(item.textureU.min(), item.textureV.max()));

                        Triangle2 triangle;
                        triangle.v[0].v = meshIndex + 1;
                        triangle.v[1].v = meshIndex + 2;
                        triangle.v[2].v = meshIndex + 3;
                        triangle.v[0].t = meshIndex + 1;
                        triangle.v[1].t = meshIndex + 2;
                        triangle.v[2].t = meshIndex + 3;
                        mesh.triangles.push_back(triangle);
                        triangle.v[0].v = meshIndex + 3;
                        triangle.v[1].v = meshIndex + 4;
                        triangle.v[2].v = meshIndex + 1;
                        triangle.v[0].t = meshIndex + 3;
                        triangle.v[1].t = meshIndex + 4;
                        triangle.v[2].t = meshIndex + 1;
                        mesh.triangles.push_back(triangle);

                        meshIndex += 4;
                    }

                    x += glyph->advance;
                }
            }
            _drawTextMesh(mesh);
        }

        void Render::drawImage(
            const std::shared_ptr<Image>& image,
            const Box2F& box,
            const Color4F& color,
            const render::ImageOptions& imageOptions)
        {
            TG_P();

            const auto& info = image->getInfo();
            std::vector<std::shared_ptr<Texture> > textures;
            if (!imageOptions.cache)
            {
                textures = _getTextures(info, imageOptions.imageFilters);
                _copyTextures(image, textures);
            }
            else if (!p.textureCache->get(image, textures))
            {
                textures = _getTextures(info, imageOptions.imageFilters);
                _copyTextures(image, textures);
                p.textureCache->add(image, textures, image->getByteCount());
            }
            _setActiveTextures(info, textures);

            p.shaders["image"]->bind();
            p.shaders["image"]->setUniform("color", color);
            p.shaders["image"]->setUniform("pixelType", static_cast<int>(info.pixelType));
            VideoLevels videoLevels = info.videoLevels;
            switch (imageOptions.videoLevels)
            {
            case render::InputVideoLevels::FullRange:
                videoLevels = VideoLevels::FullRange;
                break;
            case render::InputVideoLevels::LegalRange:
                videoLevels = VideoLevels::LegalRange;
                break;
            default: break;
            }
            p.shaders["image"]->setUniform("videoLevels", static_cast<int>(videoLevels));
            p.shaders["image"]->setUniform("yuvCoefficients", getYUVCoefficients(info.yuvCoefficients));
            p.shaders["image"]->setUniform("imageChannels", getChannelCount(info.pixelType));
            p.shaders["image"]->setUniform("mirrorX", info.layout.mirror.x);
            p.shaders["image"]->setUniform("mirrorY", info.layout.mirror.y);
            switch (info.pixelType)
            {
            case PixelType::YUV_420P_U8:
            case PixelType::YUV_422P_U8:
            case PixelType::YUV_444P_U8:
            case PixelType::YUV_420P_U16:
            case PixelType::YUV_422P_U16:
            case PixelType::YUV_444P_U16:
                p.shaders["image"]->setUniform("textureSampler1", 1);
                p.shaders["image"]->setUniform("textureSampler2", 2);
            default:
                p.shaders["image"]->setUniform("textureSampler0", 0);
                break;
            }

            switch (imageOptions.alphaBlend)
            {
            case render::AlphaBlend::None:
                glBlendFuncSeparate(GL_ONE, GL_ZERO, GL_ONE, GL_ONE);
                break;
            case render::AlphaBlend::Straight:
                glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
                break;
            case render::AlphaBlend::Premultiplied:
                glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
                break;
            default: break;
            }

            if (p.vbos["image"])
            {
                p.vbos["image"]->copy(convert(mesh(box), p.vbos["image"]->getType()));
            }
            if (p.vaos["image"])
            {
                p.vaos["image"]->bind();
                p.vaos["image"]->draw(GL_TRIANGLES, 0, p.vbos["image"]->getSize());
            }
        }

        void Render::_drawTextMesh(const TriMesh2F& mesh)
        {
            TG_P();
            const size_t size = mesh.triangles.size();
            if (size > 0)
            {
                if (!p.vbos["text"] || (p.vbos["text"] && p.vbos["text"]->getSize() < size * 3))
                {
                    p.vbos["text"] = VBO::create(size * 3, VBOType::Pos2_F32_UV_U16);
                    p.vaos["text"].reset();
                }
                if (p.vbos["text"])
                {
                    p.vbos["text"]->copy(convert(mesh, p.vbos["text"]->getType()));
                }
                if (!p.vaos["text"] && p.vbos["text"])
                {
                    p.vaos["text"] = VAO::create(p.vbos["text"]->getType(), p.vbos["text"]->getID());
                }
                if (p.vaos["text"] && p.vbos["text"])
                {
                    p.vaos["text"]->bind();
                    p.vaos["text"]->draw(GL_TRIANGLES, 0, size * 3);
                }
            }
        }
    }
}

