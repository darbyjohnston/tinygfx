// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgGL/Mesh.h>

namespace tg
{
    namespace gl
    {
        void VBO::_init(size_t count, size_t size)
        {
            _count = count;
            _size = size;
            glGenBuffers(1, &_id);
            glBindBuffer(GL_ARRAY_BUFFER, _id);
            glBufferData(GL_ARRAY_BUFFER, _count * _size, NULL, GL_DYNAMIC_DRAW);
        }

        VBO::VBO()
        {}

        VBO::~VBO()
        {
            if (_id)
            {
                glDeleteBuffers(1, &_id);
                _id = 0;
            }
        }

        std::shared_ptr<VBO> VBO::create(size_t count, size_t size)
        {
            auto out = std::shared_ptr<VBO>(new VBO);
            out->_init(count, size);
            return out;
        }

        size_t VBO::getCount() const
        {
            return _count;
        }

        size_t VBO::getSize() const
        {
            return _size;
        }

        GLuint VBO::getID() const
        {
            return _id;
        }

        void VBO::copy(const std::vector<uint8_t>& data)
        {
            glBindBuffer(GL_ARRAY_BUFFER, _id);
            glBufferSubData(GL_ARRAY_BUFFER, 0, data.size(), (void*)data.data());
        }
        
        void VBO::copy(const std::vector<uint8_t>& data, size_t offset)
        {
            glBindBuffer(GL_ARRAY_BUFFER, _id);
            glBufferSubData(GL_ARRAY_BUFFER, offset, data.size(), (void*)data.data());
        }
        
        void VBO::copy(const std::vector<uint8_t>& data, size_t offset, size_t size)
        {
            glBindBuffer(GL_ARRAY_BUFFER, _id);
            glBufferSubData(GL_ARRAY_BUFFER, offset, size, (void*)data.data());
        }

        void VAO::_init(GLuint vbo)
        {
            glGenVertexArrays(1, &_id);
            glBindVertexArray(_id);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
        }

        VAO::VAO()
        {}

        VAO::~VAO()
        {
            if (_id)
            {
                glDeleteVertexArrays(1, &_id);
                _id = 0;
            }
        }

        std::shared_ptr<VAO> VAO::create(GLuint vbo)
        {
            auto out = std::shared_ptr<VAO>(new VAO);
            out->_init(vbo);
            return out;
        }

        void VAO::bind()
        {
            glBindVertexArray(_id);
        }

        void VAO::draw(GLenum mode, size_t offset, size_t size)
        {
            glDrawArrays(mode, offset, size);
        }
    }
}