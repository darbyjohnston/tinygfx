// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGL/RenderPrivate.h>

#include <tgCore/Context.h>
#include <tgCore/Format.h>
#include <tgCore/LogSystem.h>

using namespace tg::core;

namespace tg
{
    namespace gl
    {
        namespace
        {
            const int pboSizeMin = 1024;
            const size_t statsAverageCount = 10;
        }

        void Render::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<TextureCache>& textureCache)
        {
            IRender::_init(context);
            TG_P();

            p.textureCache = textureCache;
            if (!p.textureCache)
            {
                p.textureCache = std::make_shared<TextureCache>();
            }

            p.glyphTextureAtlas = TextureAtlas::create(
                4096,
                ImageType::L_U8,
                TextureFilter::Linear);
            
            p.logTimer = Timer::create(context);
            p.logTimer->setRepeating(true);
            auto weak = std::weak_ptr<Render>(std::dynamic_pointer_cast<Render>(shared_from_this()));
            p.logTimer->start(
                std::chrono::seconds(10),
                [this]
                {
                    if (_p->options.log)
                    {
                        _log();
                    }
                });
        }

        Render::Render() :
            _p(new Private)
        {}

        Render::~Render()
        {}

        std::shared_ptr<Render> Render::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<TextureCache>& textureCache)
        {
            auto out = std::shared_ptr<Render>(new Render);
            out->_init(context, textureCache);
            return out;
        }

        void Render::begin(
            const Size2I& size,
            const RenderOptions& options)
        {
            TG_P();

            p.startTime = std::chrono::steady_clock::now();
            p.stats = Private::Stats();
            
            p.size = size;
            p.options = options;
            p.textureCache->setMax(options.textureCacheByteCount);

            glEnable(GL_BLEND);
            glBlendEquation(GL_FUNC_ADD);

            if (!p.shaders["rect"])
            {
                p.shaders["rect"] = Shader::create(
                    vertexSource(),
                    meshFragmentSource());
            }
            if (!p.shaders["line"])
            {
                p.shaders["line"] = Shader::create(
                    vertexSource(),
                    meshFragmentSource());
            }
            if (!p.shaders["mesh"])
            {
                p.shaders["mesh"] = Shader::create(
                    vertexSource(),
                    meshFragmentSource());
            }
            if (!p.shaders["colorMesh"])
            {
                p.shaders["colorMesh"] = Shader::create(
                    colorMeshVertexSource(),
                    colorMeshFragmentSource());
            }
            if (!p.shaders["text"])
            {
                p.shaders["text"] = Shader::create(
                    vertexSource(),
                    textFragmentSource());
            }
            if (!p.shaders["image"])
            {
                p.shaders["image"] = Shader::create(
                    vertexSource(),
                    imageFragmentSource());
            }

            p.vbos["rect"] = VBO::create(2 * 3, VBOType::Pos2_F32);
            p.vaos["rect"] = VAO::create(p.vbos["rect"]->getType(), p.vbos["rect"]->getID());
            p.vbos["line"] = VBO::create(2 * 3, VBOType::Pos2_F32);
            p.vaos["line"] = VAO::create(p.vbos["line"]->getType(), p.vbos["line"]->getID());
            p.vbos["image"] = VBO::create(2 * 3, VBOType::Pos2_F32_UV_U16);
            p.vaos["image"] = VAO::create(p.vbos["image"]->getType(), p.vbos["image"]->getID());

            setViewport(Box2I(0, 0, size.w, size.h));
            if (options.clear)
            {
                clearViewport(options.clearColor);
            }
            setTransform(ortho(
                0.F,
                static_cast<float>(size.w),
                static_cast<float>(size.h),
                0.F,
                -1.F,
                1.F));
        }
        
        void Render::end()
        {
            TG_P();
            const auto now = std::chrono::steady_clock::now();
            const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - p.startTime);
            p.stats.renderTime = diff.count();
            p.statsList.push_back(p.stats);
            while (p.statsList.size() > statsAverageCount)
            {
                p.statsList.pop_front();
            }
        }

        Size2I Render::getRenderSize() const
        {
            return _p->size;
        }

        void Render::setRenderSize(const Size2I& value)
        {
            _p->size = value;
        }

        Box2I Render::getViewport() const
        {
            return _p->viewport;
        }

        void Render::setViewport(const Box2I& value)
        {
            TG_P();
            p.viewport = value;
            glViewport(
                value.x(),
                p.size.h - value.h() - value.y(),
                value.w(),
                value.h());
        }

        void Render::clearViewport(const Color4F& value)
        {
            glClearColor(value.r, value.g, value.b, value.a);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        bool Render::getClipRectEnabled() const
        {
            return _p->clipRectEnabled;
        }

        void Render::setClipRectEnabled(bool value)
        {
            TG_P();
            p.clipRectEnabled = value;
            if (p.clipRectEnabled)
            {
                glEnable(GL_SCISSOR_TEST);
            }
            else
            {
                glDisable(GL_SCISSOR_TEST);
            }
        }

        Box2I Render::getClipRect() const
        {
            return _p->clipRect;
        }

        void Render::setClipRect(const Box2I& value)
        {
            TG_P();
            p.clipRect = value;
            const Size2I size = value.size();
            if (size.isValid())
            {
                glScissor(
                    value.x(),
                    p.size.h - size.h - value.y(),
                    size.w,
                    size.h);
            }
        }

        M44F Render::getTransform() const
        {
            return _p->transform;
        }

        void Render::setTransform(const M44F& value)
        {
            TG_P();
            p.transform = value;
            for (auto i : p.shaders)
            {
                i.second->bind();
                i.second->setUniform("transform.mvp", value);
            }
        }

        std::vector<std::shared_ptr<Texture> > Render::_getTextures(
            const ImageInfo& info,
            const ImageFilters& imageFilters,
            size_t offset)
        {
            std::vector<std::shared_ptr<Texture> > out;
            TextureOptions options;
            switch (imageFilters.minify)
            {
            case ImageFilter::Nearest:
                options.filters.minify = TextureFilter::Nearest;
                break;
            case ImageFilter::Linear:
                options.filters.minify = TextureFilter::Linear;
                break;
            default: break;
            }
            switch (imageFilters.magnify)
            {
            case ImageFilter::Nearest:
                options.filters.magnify = TextureFilter::Nearest;
                break;
            case ImageFilter::Linear:
                options.filters.magnify = TextureFilter::Linear;
                break;
            default: break;
            }
            options.pbo = info.size.w >= pboSizeMin || info.size.h >= pboSizeMin;
            switch (info.type)
            {
            case ImageType::YUV_420P_U8:
            {
                auto infoTmp = ImageInfo(info.size, ImageType::L_U8);
                out.push_back(Texture::create(infoTmp, options));
                infoTmp = ImageInfo(info.size.w / 2, info.size.h / 2, ImageType::L_U8);
                out.push_back(Texture::create(infoTmp, options));
                out.push_back(Texture::create(infoTmp, options));
                break;
            }
            case ImageType::YUV_422P_U8:
            {
                auto infoTmp = ImageInfo(info.size, ImageType::L_U8);
                out.push_back(Texture::create(infoTmp, options));
                infoTmp = ImageInfo(info.size.w / 2, info.size.h, ImageType::L_U8);
                out.push_back(Texture::create(infoTmp, options));
                out.push_back(Texture::create(infoTmp, options));
                break;
            }
            case ImageType::YUV_444P_U8:
            {
                auto infoTmp = ImageInfo(info.size, ImageType::L_U8);
                out.push_back(Texture::create(infoTmp, options));
                infoTmp = ImageInfo(info.size, ImageType::L_U8);
                out.push_back(Texture::create(infoTmp, options));
                out.push_back(Texture::create(infoTmp, options));
                break;
            }
            case ImageType::YUV_420P_U16:
            {
                auto infoTmp = ImageInfo(info.size, ImageType::L_U16);
                out.push_back(Texture::create(infoTmp, options));
                infoTmp = ImageInfo(info.size.w / 2, info.size.h / 2, ImageType::L_U16);
                out.push_back(Texture::create(infoTmp, options));
                out.push_back(Texture::create(infoTmp, options));
                break;
            }
            case ImageType::YUV_422P_U16:
            {
                auto infoTmp = ImageInfo(info.size, ImageType::L_U16);
                out.push_back(Texture::create(infoTmp, options));
                infoTmp = ImageInfo(info.size.w / 2, info.size.h, ImageType::L_U16);
                out.push_back(Texture::create(infoTmp, options));
                out.push_back(Texture::create(infoTmp, options));
                break;
            }
            case ImageType::YUV_444P_U16:
            {
                auto infoTmp = ImageInfo(info.size, ImageType::L_U16);
                out.push_back(Texture::create(infoTmp, options));
                infoTmp = ImageInfo(info.size, ImageType::L_U16);
                out.push_back(Texture::create(infoTmp, options));
                out.push_back(Texture::create(infoTmp, options));
                break;
            }
            default:
            {
                auto texture = Texture::create(info, options);
                out.push_back(texture);
                break;
            }
            }
            return out;
        }

        void Render::_copyTextures(
            const std::shared_ptr<Image>& image,
            const std::vector<std::shared_ptr<Texture> >& textures,
            size_t offset)
        {
            const auto& info = image->getInfo();
            switch (info.type)
            {
            case ImageType::YUV_420P_U8:
            {
                if (3 == textures.size())
                {
                    textures[0]->copy(image->getData(), textures[0]->getInfo());
                    const std::size_t w = info.size.w;
                    const std::size_t h = info.size.h;
                    const std::size_t w2 = w / 2;
                    const std::size_t h2 = h / 2;
                    textures[1]->copy(image->getData() + (w * h), textures[1]->getInfo());
                    textures[2]->copy(image->getData() + (w * h) + (w2 * h2), textures[2]->getInfo());
                }
                break;
            }
            case ImageType::YUV_422P_U8:
            {
                if (3 == textures.size())
                {
                    textures[0]->copy(image->getData(), textures[0]->getInfo());
                    const std::size_t w = info.size.w;
                    const std::size_t h = info.size.h;
                    const std::size_t w2 = w / 2;
                    textures[1]->copy(image->getData() + (w * h), textures[1]->getInfo());
                    textures[2]->copy(image->getData() + (w * h) + (w2 * h), textures[2]->getInfo());
                }
                break;
            }
            case ImageType::YUV_444P_U8:
            {
                if (3 == textures.size())
                {
                    textures[0]->copy(image->getData(), textures[0]->getInfo());
                    const std::size_t w = info.size.w;
                    const std::size_t h = info.size.h;
                    textures[1]->copy(image->getData() + (w * h), textures[1]->getInfo());
                    textures[2]->copy(image->getData() + (w * h) + (w * h), textures[2]->getInfo());
                }
                break;
            }
            case ImageType::YUV_420P_U16:
            {
                if (3 == textures.size())
                {
                    textures[0]->copy(image->getData(), textures[0]->getInfo());
                    const std::size_t w = info.size.w;
                    const std::size_t h = info.size.h;
                    const std::size_t w2 = w / 2;
                    const std::size_t h2 = h / 2;
                    textures[1]->copy(image->getData() + (w * h) * 2, textures[1]->getInfo());
                    textures[2]->copy(image->getData() + (w * h) * 2 + (w2 * h2) * 2, textures[2]->getInfo());
                }
                break;
            }
            case ImageType::YUV_422P_U16:
            {
                if (3 == textures.size())
                {
                    textures[0]->copy(image->getData(), textures[0]->getInfo());
                    const std::size_t w = info.size.w;
                    const std::size_t h = info.size.h;
                    const std::size_t w2 = w / 2;
                    textures[1]->copy(image->getData() + (w * h) * 2, textures[1]->getInfo());
                    textures[2]->copy(image->getData() + (w * h) * 2 + (w2 * h) * 2, textures[2]->getInfo());
                }
                break;
            }
            case ImageType::YUV_444P_U16:
            {
                if (3 == textures.size())
                {
                    textures[0]->copy(image->getData(), textures[0]->getInfo());
                    const std::size_t w = info.size.w;
                    const std::size_t h = info.size.h;
                    textures[1]->copy(image->getData() + (w * h) * 2, textures[1]->getInfo());
                    textures[2]->copy(image->getData() + (w * h) * 2 + (w * h) * 2, textures[2]->getInfo());
                }
                break;
            }
            default:
                if (1 == textures.size())
                {
                    textures[0]->copy(image);
                }
                break;
            }
        }

        void Render::_setActiveTextures(
            const ImageInfo& info,
            const std::vector<std::shared_ptr<Texture> >& textures,
            size_t offset)
        {
            switch (info.type)
            {
            case ImageType::YUV_420P_U8:
                if (3 == textures.size())
                {
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + offset));
                    textures[0]->bind();
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + 1 + offset));
                    textures[1]->bind();
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + 2 + offset));
                    textures[2]->bind();
                }
                break;
            case ImageType::YUV_422P_U8:
                if (3 == textures.size())
                {
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + offset));
                    textures[0]->bind();
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + 1 + offset));
                    textures[1]->bind();
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + 2 + offset));
                    textures[2]->bind();
                }
                break;
            case ImageType::YUV_444P_U8:
                if (3 == textures.size())
                {
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + offset));
                    textures[0]->bind();
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + 1 + offset));
                    textures[1]->bind();
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + 2 + offset));
                    textures[2]->bind();
                }
                break;
            case ImageType::YUV_420P_U16:
                if (3 == textures.size())
                {
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + offset));
                    textures[0]->bind();
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + 1 + offset));
                    textures[1]->bind();
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + 2 + offset));
                    textures[2]->bind();
                }
                break;
            case ImageType::YUV_422P_U16:
                if (3 == textures.size())
                {
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + offset));
                    textures[0]->bind();
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + 1 + offset));
                    textures[1]->bind();
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + 2 + offset));
                    textures[2]->bind();
                }
                break;
            case ImageType::YUV_444P_U16:
                if (3 == textures.size())
                {
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + offset));
                    textures[0]->bind();
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + 1 + offset));
                    textures[1]->bind();
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + 2 + offset));
                    textures[2]->bind();
                }
                break;
            default:
                if (1 == textures.size())
                {
                    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + offset));
                    textures[0]->bind();
                }
                break;
            }
        }
        
        void Render::_log()
        {
            TG_P();
            if (auto context = _context.lock())
            {
                auto logSystem = context->getSystem<LogSystem>();
                Private::Stats average;
                const size_t size = p.statsList.size();
                if (size)
                {
                    for (auto i : p.statsList)
                    {
                        average.renderTime   += i.renderTime;
                        average.triCount     += i.triCount;
                        average.textureCount += i.textureCount;
                        average.glyphCount   += i.glyphCount;
                    }
                    average.renderTime   /= size;
                    average.triCount     /= size;
                    average.textureCount /= size;
                    average.glyphCount   /= size;
                }
                logSystem->print(
                    "tg::gl::Render",
                    Format(
                        "Averages:\n"
                        "    Render time:    {0}ms\n"
                        "    Triangle count: {1}\n"
                        "    Texture count:  {2}\n"
                        "    Glyph count:    {3}").
                        arg(average.renderTime).
                        arg(average.triCount).
                        arg(average.textureCount).
                        arg(average.glyphCount));
            }
        }
    }
}

