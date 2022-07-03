// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgGlad/gl.h>

#include <tgCore/Mesh.h>

#include <memory>
#include <vector>

namespace tg
{
    namespace gl
    {
        //! OpenGL vertex buffer object.
        class VBO
        {
        protected:
            void _init(size_t count, size_t size);

            VBO();

        public:
            ~VBO();

            //! Create a new vertex buffer object.
            static std::shared_ptr<VBO> create(size_t count, size_t size);

            //! Get the count.
            size_t getCount() const;

            //! Get the size.
            size_t getSize() const;

            //! Get the OpenGL ID.
            GLuint getID() const;

            //! Copy data to the vertex buffer object.
            void copy(const std::vector<uint8_t>&);

            //! Copy data to the vertex buffer object.
            void copy(const std::vector<uint8_t>&, size_t offset);

            //! Copy data to the vertex buffer object.
            void copy(const std::vector<uint8_t>&, size_t offset, size_t size);

        private:
            size_t _count = 0;
            size_t _size = 0;
            GLuint _id = 0;
        };

        //! OpenGL vertex array object.
        class VAO
        {
        protected:
            void _init(GLuint vbo);

            VAO();

        public:
            ~VAO();

            //! Create a new vertex array object.
            static std::shared_ptr<VAO> create(GLuint vbo);

            //! Get the OpenGL ID.
            GLuint getID() const;

            //! Bind the vertex array object.
            void bind();

            //! Draw the vertex array object.
            void draw(GLenum mode, size_t offset, size_t size);

        private:
            GLuint _id = 0;
        };

        //! VBO and VAO.
        typedef std::pair<std::shared_ptr<VBO>, std::shared_ptr<VAO> > VBOVAO;

        //! Two-dimensional mesh data types.
        enum class Mesh2DType
        {
            V2F_T2F,
        };

        //! Create a VBO and VAO for a two-dimensional mesh.
        VBOVAO create(const geom::Mesh2D&, Mesh2DType);

        //! Three-dimensional mesh data types.
        enum class Mesh3DType
        {
            V3F_T2F_N3F
        };

        //! Create a VBO and VAO for a three-dimensional mesh.
        VBOVAO create(const geom::Mesh3D&, Mesh3DType);
    }
}
