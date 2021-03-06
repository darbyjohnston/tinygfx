// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgGL/OffscreenBuffer.h>

#include <tgGL/Texture.h>

#include <stdexcept>
#include <string>

namespace tg
{
    namespace gl
    {
        namespace
        {
            enum class Error
            {
                ColorTexture,
                RenderBuffer,
                Create,
                Init
            };

            std::string getErrorLabel(Error error)
            {
                std::string out;
                switch (error)
                {
                case Error::ColorTexture:
                    out = "Cannot create color texture";
                    break;
                case Error::RenderBuffer:
                    out = "Cannot create render buffer";
                    break;
                case Error::Create:
                    out = "Cannot create frame buffer";
                    break;
                case Error::Init:
                    out = "Cannot initialize frame buffer";
                    break;
                default: break;
                }
                return out;
            }

            GLenum getBufferInternalFormat(OffscreenDepth depth, OffscreenStencil stencil)
            {
                GLenum out = GL_NONE;
                switch (depth)
                {
                case OffscreenDepth::None:
                    switch (stencil)
                    {
                    case OffscreenStencil::_8:
                        out = GL_STENCIL_INDEX8;
                        break;
                    default:
                        break;
                    }
                    break;
                case OffscreenDepth::_24:
                    switch (stencil)
                    {
                    case OffscreenStencil::None:
                        out = GL_DEPTH_COMPONENT24;
                        break;
                    case OffscreenStencil::_8:
                        out = GL_DEPTH24_STENCIL8;
                        break;
                    default: break;
                    }
                    break;
                case OffscreenDepth::_32:
                    switch (stencil)
                    {
                    case OffscreenStencil::None:
                        out = GL_DEPTH_COMPONENT32F;
                        break;
                    case OffscreenStencil::_8:
                        out = GL_DEPTH32F_STENCIL8;
                        break;
                    default: break;
                    }
                    break;
                default: break;
                }
                return out;
            }
        }

        void OffscreenBuffer::_init(
            const math::Vector2i& size,
            const OffscreenBufferOptions& options)
        {
            _size = size;

            GLenum target = GL_TEXTURE_2D;
            GLint maxSamples = 0;
            glGetIntegerv(GL_MAX_COLOR_TEXTURE_SAMPLES, &maxSamples);
            GLsizei samples = std::min(static_cast<GLint>(options.samples), maxSamples);
            if (samples > 0)
            {
                target = GL_TEXTURE_2D_MULTISAMPLE;
            }

            // Create the color texture.
            if (options.colorFormat != image::Format::None &&
                options.colorType != image::Type::None)
            {
                glGenTextures(1, &_colorID);
                if (!_colorID)
                {
                    throw std::runtime_error(getErrorLabel(Error::ColorTexture));
                }
                glBindTexture(target, _colorID);
                if (samples > 0)
                {
                    glTexImage2DMultisample(
                        target,
                        samples,
                        getTextureInternalFormat(options.colorFormat, options.colorType),
                        _size.x,
                        _size.y,
                        false);
                }
                else
                {
                    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, options.colorMag);
                    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, options.colorMin);
                    glTexImage2D(
                        target,
                        0,
                        getTextureInternalFormat(options.colorFormat, options.colorType),
                        _size.x,
                        _size.y,
                        0,
                        getTextureFormat(options.colorFormat),
                        getTextureType(options.colorType),
                        0);
                }
            }

            // Create the depth/stencil buffer.
            if (options.depth != OffscreenDepth::None ||
                options.stencil != OffscreenStencil::None)
            {
                glGenRenderbuffers(1, &_depthStencilID);
                if (!_depthStencilID)
                {
                    throw std::runtime_error(getErrorLabel(Error::RenderBuffer));
                }
                glBindRenderbuffer(GL_RENDERBUFFER, _depthStencilID);
                glRenderbufferStorageMultisample(
                    GL_RENDERBUFFER,
                    samples,
                    getBufferInternalFormat(options.depth, options.stencil),
                    _size.x,
                    _size.y);
                glBindRenderbuffer(GL_RENDERBUFFER, 0);
            }

            // Create the FBO.
            glGenFramebuffers(1, &_id);
            if (!_id)
            {
                throw std::runtime_error(getErrorLabel(Error::Create));
            }
            const OffscreenBufferBinding binding(shared_from_this());
            if (_colorID)
            {
                glFramebufferTexture2D(
                    GL_FRAMEBUFFER,
                    GL_COLOR_ATTACHMENT0,
                    target,
                    _colorID,
                    0);
            }
            if (_depthStencilID)
            {
                GLenum attachment = GL_NONE;
                if (options.depth != OffscreenDepth::None &&
                    options.stencil != OffscreenStencil::None)
                {
                    attachment = GL_DEPTH_STENCIL_ATTACHMENT;
                }
                else if (options.depth != OffscreenDepth::None)
                {
                    attachment = GL_DEPTH_ATTACHMENT;
                }
                else if (options.stencil != OffscreenStencil::None)
                {
                    attachment = GL_STENCIL_ATTACHMENT;
                }
                glFramebufferRenderbuffer(
                    GL_FRAMEBUFFER,
                    attachment,
                    GL_RENDERBUFFER,
                    _depthStencilID);
            }
            GLenum error = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if (error != GL_FRAMEBUFFER_COMPLETE)
            {
                throw std::runtime_error(getErrorLabel(Error::Init));
            }
        }

        OffscreenBuffer::OffscreenBuffer()
        {}

        OffscreenBuffer::~OffscreenBuffer()
        {
            if (_id)
            {
                glDeleteFramebuffers(1, &_id);
                _id = 0;
            }
            if (_colorID)
            {
                glDeleteTextures(1, &_colorID);
                _colorID = 0;
            }
            if (_depthStencilID)
            {
                glDeleteRenderbuffers(1, &_depthStencilID);
                _depthStencilID = 0;
            }
        }

        std::shared_ptr<OffscreenBuffer> OffscreenBuffer::create(
            const math::Vector2i& size,
            const OffscreenBufferOptions& options)
        {
            auto out = std::shared_ptr<OffscreenBuffer>(new OffscreenBuffer);
            out->_init(size, options);
            return out;
        }

        const math::Vector2i& OffscreenBuffer::getSize() const
        {
            return _size;
        }

        GLuint OffscreenBuffer::getID() const
        {
            return _id;
        }

        GLuint OffscreenBuffer::getColorID() const
        {
            return _colorID;
        }

        void OffscreenBuffer::bind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, _id);
        }

        bool doCreate(const std::shared_ptr<OffscreenBuffer>& offscreenBuffer, const math::Vector2i& size)
        {
            bool out = false;
            out |= size.x > 0 && size.y > 0 && !offscreenBuffer;
            out |= size.x > 0 && size.y > 0 && offscreenBuffer && offscreenBuffer->getSize() != size;
            return out;
        }

        OffscreenBufferBinding::OffscreenBufferBinding(const std::shared_ptr<OffscreenBuffer>& buffer) :
            _buffer(buffer)
        {
            glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_previous);
            _buffer->bind();
        }

        OffscreenBufferBinding::~OffscreenBufferBinding()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, _previous);
        }
    }
}