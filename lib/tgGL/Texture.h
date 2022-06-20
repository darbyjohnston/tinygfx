// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Image.h>

#include <tgGlad/gl.h>

namespace tg
{
    namespace gl
    {
        //! Get the OpenGL texture format.
        GLenum getTextureFormat(image::Format);

        //! Get the OpenGL texture type.
        GLenum getTextureType(image::Type);

        //! Get the OpenGL internal texture format.
        GLenum getTextureInternalFormat(image::Format, image::Type);

        //! OpenGL texture.
        class Texture : public std::enable_shared_from_this<Texture>
        {
        protected:
            void _init(
                const image::Info&,
                GLenum filterMin,
                GLenum filterMag);

            Texture();

        public:
            ~Texture();

            //! Create a new texture.
            static std::shared_ptr<Texture> create(
                const image::Info&,
                GLenum filterMin = GL_LINEAR,
                GLenum filterMag = GL_LINEAR);

            //! Get the image information.
            const image::Info& getInfo() const;

            //! Get the OpenGL texture ID.
            GLuint getID() const;

            //! Copy image data to the texture.
            void copy(const std::shared_ptr<image::Image>&);

            //! Copy image data to the texture.
            void copy(const uint8_t*, const image::Info&);

            //! Copy image data to the texture.
            void copy(const std::shared_ptr<image::Image>&, int x, int y);

            //! Bind the texture.
            void bind();

        private:
            image::Info _info;
            GLenum _filterMin = GL_LINEAR;
            GLenum _filterMag = GL_LINEAR;
            GLuint _id = 0;
        };
    }
}
