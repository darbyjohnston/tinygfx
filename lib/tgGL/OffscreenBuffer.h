// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Image.h>

#include <tgGlad/gl.h>

#include <memory>

namespace tg
{
    namespace gl
    {
        //! Offscreen buffer depth size.
        enum class OffscreenDepth
        {
            None,
            _24,
            _32,

            Count,
            First = None
        };

        //! Offscreen buffer stencil size.
        enum class OffscreenStencil
        {
            None,
            _8,

            Count,
            First = None
        };

        //! Offscreen buffer options.
        struct OffscreenBufferOptions
        {
            image::Format colorFormat = image::Format::None;
            image::Type colorType = image::Type::None;
            GLint colorMin = GL_LINEAR;
            GLint colorMag = GL_LINEAR;
            OffscreenDepth depth = OffscreenDepth::None;
            OffscreenStencil stencil = OffscreenStencil::None;
            GLsizei samples = 0;
        };

        //! Offscreen buffer.
        class OffscreenBuffer : public std::enable_shared_from_this<OffscreenBuffer>
        {
        protected:
            void _init(
                const math::Vector2i&,
                const OffscreenBufferOptions&);
            OffscreenBuffer();

        public:
            ~OffscreenBuffer();

            //! Create a new offscreen buffer.
            static std::shared_ptr<OffscreenBuffer> create(
                const math::Vector2i&,
                const OffscreenBufferOptions&);

            //! Get the offscreen buffer size.
            const math::Vector2i& getSize() const;

            //! Get the offscreen buffer ID.
            GLuint getID() const;

            //! Get the color texture ID.
            GLuint getColorID() const;

            //! Bind the offscreen buffer.
            void bind();

        private:
            math::Vector2i _size = math::Vector2i(0, 0);
            GLuint _id = 0;
            GLuint _colorID = 0;
            GLuint _depthStencilID = 0;
        };

        //! Check whether the offscreen buffer should be created or re-created.
        bool doCreate(const std::shared_ptr<OffscreenBuffer>&, const math::Vector2i&);

        //! Offscreen Buffer Binding
        class OffscreenBufferBinding
        {
        public:
            explicit OffscreenBufferBinding(const std::shared_ptr<OffscreenBuffer>&);

            ~OffscreenBufferBinding();

        private:
            std::shared_ptr<OffscreenBuffer> _buffer;
            GLint _previous = 0;
        };
    }
}
