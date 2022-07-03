// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgGL/Texture.h>

#include <array>

namespace tg
{
    namespace gl
    {
        GLenum getTextureFormat(image::Format value)
        {
            const std::array<GLenum, static_cast<size_t>(image::Format::Count)> data =
            {
                GL_NONE,

                GL_RGBA
            };
            return data[static_cast<size_t>(value)];
        }

        GLenum getTextureType(image::Type value)
        {
            const std::array<GLenum, static_cast<size_t>(image::Type::Count)> data =
            {
                GL_NONE,

                GL_FLOAT
            };
            return data[static_cast<size_t>(value)];
        }

        GLenum getTextureInternalFormat(image::Format format, image::Type type)
        {
            GLenum out = GL_NONE;
            switch (format)
            {
            case image::Format::RGBA:
                switch (type)
                {
                case image::Type::Float: out = GL_RGBA32F; break;
                }
                break;
            }
            return out;
        }

        void Texture::_init(
            const image::Info& info,
            GLenum filterMin,
            GLenum filterMag)
        {
            _info = info;
            _filterMin = filterMin;
            _filterMag = filterMag;
            if (_info.isValid())
            {
                glGenTextures(1, &_id);
                glBindTexture(GL_TEXTURE_2D, _id);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filterMin);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filterMag);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    getTextureInternalFormat(_info.format, _info.type),
                    _info.size.x,
                    _info.size.y,
                    0,
                    getTextureFormat(_info.format),
                    getTextureType(_info.type),
                    0);
            }
        }

        Texture::Texture()
        {}

        Texture::~Texture()
        {
            if (_id)
            {
                glDeleteTextures(1, &_id);
                _id = 0;
            }
        }

        std::shared_ptr<Texture> Texture::create(
            const image::Info& info,
            GLenum filterMin,
            GLenum filterMag)
        {
            auto out = std::shared_ptr<Texture>(new Texture);
            out->_init(info, filterMin, filterMag);
            return out;
        }

        const image::Info& Texture::getInfo() const
        {
            return _info;
        }

        GLuint Texture::getID() const
        {
            return _id;
        }

        void Texture::copy(const std::shared_ptr<image::Image>& image)
        {
            const auto& info = image->getInfo();
            glBindTexture(GL_TEXTURE_2D, _id);
            glTexSubImage2D(
                GL_TEXTURE_2D,
                0,
                0,
                0,
                info.size.x,
                info.size.y,
                getTextureFormat(info.format),
                getTextureType(info.type),
                image->getData());
        }

        void Texture::copy(const uint8_t* data, const image::Info& info)
        {
            glBindTexture(GL_TEXTURE_2D, _id);
            glTexSubImage2D(
                GL_TEXTURE_2D,
                0,
                0,
                0,
                info.size.x,
                info.size.y,
                getTextureFormat(info.format),
                getTextureType(info.type),
                data);
        }

        void Texture::copy(const std::shared_ptr<image::Image>& image, int x, int y)
        {
            const auto& info = image->getInfo();
            glBindTexture(GL_TEXTURE_2D, _id);
            glTexSubImage2D(
                GL_TEXTURE_2D,
                0,
                x,
                y,
                info.size.x,
                info.size.y,
                getTextureFormat(info.format),
                getTextureType(info.type),
                image->getData());
        }

        void Texture::bind()
        {
            glBindTexture(GL_TEXTURE_2D, _id);
        }
    }
}