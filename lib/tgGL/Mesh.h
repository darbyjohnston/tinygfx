// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Mesh.h>
#include <tgCore/Range.h>
#include <tgCore/Util.h>

#include <memory>
#include <vector>

namespace tg
{
    namespace geom
    {
        struct TriMesh2;
        struct TriMesh3;
    }

    namespace gl
    {
        //! Vertex buffer object types.
        enum class VBOType
        {
            Pos2_F32,
            Pos2_F32_UV_U16,
            Pos2_F32_Color_F32,
            Pos3_F32,
            Pos3_F32_UV_U16,
            Pos3_F32_UV_U16_Normal_U10,
            Pos3_F32_UV_U16_Normal_U10_Color_U8,
            Pos3_F32_UV_F32_Normal_F32,
            Pos3_F32_UV_F32_Normal_F32_Color_F32,
            Pos3_F32_Color_U8,

            Count,
            First = Pos2_F32
        };
        TG_ENUM(VBOType);

        //! Get the number of bytes used to store vertex buffer object types.
        std::size_t getByteCount(VBOType);

        //! Convert a triangle mesh to vertex buffer data.
        std::vector<uint8_t> convert(const core::TriMesh2F&, VBOType);

        //! Convert a triangle mesh to vertex buffer data.
        std::vector<uint8_t> convert(
            const core::TriMesh2F&,
            VBOType,
            const core::RangeSizeT&);

        //! Convert a triangle mesh to vertex buffer data.
        std::vector<uint8_t> convert(const core::TriMesh3F&, VBOType);

        //! Convert a triangle mesh to vertex buffer data.
        std::vector<uint8_t> convert(
            const core::TriMesh3F&,
            VBOType,
            const core::RangeSizeT&);

        //! OpenGL vertex buffer object.
        class VBO : public std::enable_shared_from_this<VBO>
        {
            TG_NON_COPYABLE(VBO);

        protected:
            VBO(std::size_t size, VBOType);

        public:
            ~VBO();

            //! Create a new object.
            static std::shared_ptr<VBO> create(std::size_t size, VBOType);

            //! Get the size.
            std::size_t getSize() const;

            //! Get the type.
            VBOType getType() const;

            //! Get the OpenGL ID.
            unsigned int getID() const;

            //! \name Copy
            //! Copy data to the vertex buffer object.
            ///@{

            void copy(const std::vector<uint8_t>&);
            void copy(const std::vector<uint8_t>&, std::size_t offset, std::size_t size);

            ///@}

        private:
            TG_PRIVATE();
        };

        //! OpenGL vertex array object.
        class VAO : public std::enable_shared_from_this<VAO>
        {
            TG_NON_COPYABLE(VAO);

        protected:
            VAO(VBOType, unsigned int vbo);

        public:
            ~VAO();

            //! Create a new object.
            static std::shared_ptr<VAO> create(VBOType, unsigned int vbo);

            //! Get the OpenGL ID.
            unsigned int getID() const;

            //! Bind the vertex array object.
            void bind();

            //! Draw the vertex array object.
            void draw(unsigned int mode, std::size_t offset, std::size_t size);

        private:
            TG_PRIVATE();
        };
    }
}
