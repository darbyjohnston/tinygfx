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
            const Box2F& rect,
            const Color4F& color)
        {
            TG_P();

            p.shaders["rect"]->bind();
            p.shaders["rect"]->setUniform("color", color);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            if (p.vbos["rect"])
            {
                const auto mesh = core::mesh(rect);
                p.vbos["rect"]->copy(convert(mesh, p.vbos["rect"]->getType()));
                p.stats.triCount += mesh.triangles.size();
            }
            if (p.vaos["rect"])
            {
                p.vaos["rect"]->bind();
                p.vaos["rect"]->draw(GL_TRIANGLES, 0, p.vbos["rect"]->getSize());
            }
        }

        void Render::drawRects(
            const std::vector<Box2F>& rects,
            const Color4F& color)
        {
            TriMesh2F mesh;
            mesh.v.resize(rects.size() * 4);
            mesh.triangles.resize(rects.size() * 2);
            size_t v = 0;
            size_t t = 0;
            for (const auto& rect : rects)
            {
                mesh.v[v + 0] = rect.min;
                mesh.v[v + 1].x = rect.max.x;
                mesh.v[v + 1].y = rect.min.y;
                mesh.v[v + 2] = rect.max;
                mesh.v[v + 3].x = rect.min.x;
                mesh.v[v + 3].y = rect.max.y;
                mesh.triangles[t + 0] = { v + 1, v + 2, v + 3 };
                mesh.triangles[t + 1] = { v + 3, v + 4, v + 1 };
                v += 4;
                t += 2;
            }
            drawMesh(mesh, color);
        }
        
        void Render::drawLine(
            const V2F& v0,
            const V2F& v1,
            const Color4F& color,
            const LineOptions& options)
        {
            TG_P();

            p.shaders["line"]->bind();
            p.shaders["line"]->setUniform("color", color);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            const V2F v2 = normalize(v1 - v0);
            const V2F v2CW = perpCW(v2) * options.width / 2.F;
            const V2F v2CCW = perpCCW(v2) * options.width / 2.F;
            TriMesh2F mesh;
            mesh.v.push_back(v0 + v2CCW);
            mesh.v.push_back(v0 + v2CW);
            mesh.v.push_back(v1 + v2CW);
            mesh.v.push_back(v1 + v2CCW);
            mesh.triangles.push_back({ 1, 2, 3 });
            mesh.triangles.push_back({ 3, 4, 1 });

            if (p.vbos["line"])
            {
                p.vbos["line"]->copy(convert(mesh, p.vbos["line"]->getType()));
                p.stats.triCount += mesh.triangles.size();
            }
            if (p.vaos["line"])
            {
                p.vaos["line"]->bind();
                p.vaos["line"]->draw(GL_TRIANGLES, 0, p.vbos["line"]->getSize());
            }
        }

        void Render::drawLines(
            const std::vector<std::pair<V2F, V2F> >& lines,
            const Color4F& color,
            const LineOptions& options)
        {
            TG_P();
            TriMesh2F mesh;
            mesh.v.resize(lines.size() * 4);
            mesh.triangles.resize(lines.size() * 2);
            size_t v = 0;
            size_t t = 0;
            for (const auto& i : lines)
            {
                const V2F v2 = normalize(i.second - i.first);
                const V2F v2CW = perpCW(v2) * options.width / 2.F;
                const V2F v2CCW = perpCCW(v2) * options.width / 2.F;
                mesh.v[v + 0] = i.first + v2CCW;
                mesh.v[v + 1] = i.first + v2CW;
                mesh.v[v + 2] = i.second + v2CW;
                mesh.v[v + 3] = i.second + v2CCW;
                mesh.triangles[t + 0] = { v + 1, v + 2, v + 3 };
                mesh.triangles[t + 1] = { v + 3, v + 4, v + 1 };
                v += 4;
                t += 2;
            }
            drawMesh(mesh, color);
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
                    p.stats.triCount += mesh.triangles.size();
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
                    p.stats.triCount += mesh.triangles.size();
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

            size_t glyphCount = 0;
            for (const auto& glyph : glyphs)
            {
                if (glyph && glyph->image && glyph->image->isValid())
                {
                    ++glyphCount;
                }
            }
            p.stats.glyphCount += glyphCount;

            int x = 0;
            int32_t rsbDeltaPrev = 0;
            TriMesh2F mesh;
            mesh.v.resize(glyphCount * 4);
            mesh.t.resize(glyphCount * 4);
            mesh.triangles.resize(glyphCount * 2);
            size_t v = 0;
            size_t t = 0;
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

                        mesh.v[v + 0].x = min.x;
                        mesh.v[v + 0].y = min.y;
                        mesh.v[v + 1].x = max.x + 1;
                        mesh.v[v + 1].y = min.y;
                        mesh.v[v + 2].x = max.x + 1;
                        mesh.v[v + 2].y = max.y + 1;
                        mesh.v[v + 3].x = min.x;
                        mesh.v[v + 3].y = max.y + 1;
                        mesh.t[v + 0].x = item.textureU.min();
                        mesh.t[v + 0].y = item.textureV.min();
                        mesh.t[v + 1].x = item.textureU.max();
                        mesh.t[v + 1].y = item.textureV.min();
                        mesh.t[v + 2].x = item.textureU.max();
                        mesh.t[v + 2].y = item.textureV.max();
                        mesh.t[v + 3].x = item.textureU.min();
                        mesh.t[v + 3].y = item.textureV.max();

                        mesh.triangles[t + 0].v[0] = { v + 1, v + 1 };
                        mesh.triangles[t + 0].v[1] = { v + 2, v + 2 };
                        mesh.triangles[t + 0].v[2] = { v + 3, v + 3 };
                        mesh.triangles[t + 1].v[0] = { v + 3, v + 3 };
                        mesh.triangles[t + 1].v[1] = { v + 4, v + 4 };
                        mesh.triangles[t + 1].v[2] = { v + 1, v + 1 };

                        v += 4;
                        t += 2;
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
            const ImageOptions& imageOptions)
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
            p.stats.textureCount += textures.size();

            p.shaders["image"]->bind();
            p.shaders["image"]->setUniform("color", color);
            p.shaders["image"]->setUniform("imageType", static_cast<int>(info.type));
            VideoLevels videoLevels = info.videoLevels;
            switch (imageOptions.videoLevels)
            {
            case InputVideoLevels::FullRange:
                videoLevels = VideoLevels::FullRange;
                break;
            case InputVideoLevels::LegalRange:
                videoLevels = VideoLevels::LegalRange;
                break;
            default: break;
            }
            p.shaders["image"]->setUniform("videoLevels", static_cast<int>(videoLevels));
            p.shaders["image"]->setUniform("yuvCoefficients", getYUVCoefficients(info.yuvCoefficients));
            p.shaders["image"]->setUniform("imageChannels", getChannelCount(info.type));
            p.shaders["image"]->setUniform("mirrorX", info.layout.mirror.x);
            p.shaders["image"]->setUniform("mirrorY", info.layout.mirror.y);
            switch (info.type)
            {
            case ImageType::YUV_420P_U8:
            case ImageType::YUV_422P_U8:
            case ImageType::YUV_444P_U8:
            case ImageType::YUV_420P_U16:
            case ImageType::YUV_422P_U16:
            case ImageType::YUV_444P_U16:
                p.shaders["image"]->setUniform("textureSampler1", 1);
                p.shaders["image"]->setUniform("textureSampler2", 2);
            default:
                p.shaders["image"]->setUniform("textureSampler0", 0);
                break;
            }

            switch (imageOptions.alphaBlend)
            {
            case AlphaBlend::None:
                glBlendFuncSeparate(GL_ONE, GL_ZERO, GL_ONE, GL_ONE);
                break;
            case AlphaBlend::Straight:
                glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
                break;
            case AlphaBlend::Premultiplied:
                glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
                break;
            default: break;
            }

            if (p.vbos["image"])
            {
                const auto mesh = core::mesh(box);
                p.vbos["image"]->copy(convert(mesh, p.vbos["image"]->getType()));
                p.stats.triCount += mesh.triangles.size();
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
                    p.stats.triCount += mesh.triangles.size();
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

