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

        VBOVAO create(const geom::Mesh2D& mesh, Mesh2DType type)
        {
            VBOVAO out;
            switch (type)
            {
            case Mesh2DType::V2F_T2F:
            {
                std::vector<uint8_t> vboData;
                struct VBOData
                {
                    float vx;
                    float vy;
                    float tx;
                    float ty;
                };
                vboData.resize(mesh.triangles.size() * 3 * sizeof(VBOData));
                auto* vboP = reinterpret_cast<VBOData*>(vboData.data());
                for (size_t i = 0; i < mesh.triangles.size(); ++i)
                {
                    const auto& triangle = mesh.triangles[i];
                    vboP[0].vx = mesh.v[triangle.v[0] - 1][0];
                    vboP[0].vy = mesh.v[triangle.v[0] - 1][1];
                    vboP[0].tx = triangle.t[0] > 0 ? mesh.t[triangle.t[0] - 1][0] : 0.F;
                    vboP[0].ty = triangle.t[0] > 0 ? mesh.t[triangle.t[0] - 1][1] : 0.F;

                    vboP[1].vx = mesh.v[triangle.v[1] - 1][0];
                    vboP[1].vy = mesh.v[triangle.v[1] - 1][1];
                    vboP[1].tx = triangle.t[1] > 0 ? mesh.t[triangle.t[1] - 1][0] : 0.F;
                    vboP[1].ty = triangle.t[1] > 0 ? mesh.t[triangle.t[1] - 1][1] : 0.F;

                    vboP[2].vx = mesh.v[triangle.v[2] - 1][0];
                    vboP[2].vy = mesh.v[triangle.v[2] - 1][1];
                    vboP[2].tx = triangle.t[2] > 0 ? mesh.t[triangle.t[2] - 1][0] : 0.F;
                    vboP[2].ty = triangle.t[2] > 0 ? mesh.t[triangle.t[2] - 1][1] : 0.F;

                    vboP += 3;
                }
                out.first = gl::VBO::create(mesh.triangles.size() * 3, sizeof(VBOData));
                out.first->copy(vboData);

                out.second = gl::VAO::create(out.first->getID());
                out.second->bind();
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)0);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)8);
                glEnableVertexAttribArray(1);
                break;
            }
            }
            return out;
        }

        VBOVAO create(const geom::Mesh3D& mesh, Mesh3DType type)
        {
            VBOVAO out;
            switch (type)
            {
            case Mesh3DType::V3F_T2F_N3F:
            {
                std::vector<uint8_t> vboData;
                struct VBOData
                {
                    float vx;
                    float vy;
                    float vz;
                    float tx;
                    float ty;
                    float nx;
                    float ny;
                    float nz;
                };
                vboData.resize(mesh.triangles.size() * 3 * sizeof(VBOData));
                VBOData* vboP = reinterpret_cast<VBOData*>(vboData.data());
                const auto& v = mesh.v;
                const auto& t = mesh.t;
                const auto& n = mesh.n;
                for (size_t i = 0; i < mesh.triangles.size(); ++i)
                {
                    const auto& triangle = mesh.triangles[i];
                    vboP[0].vx = v[triangle.v[0] - 1][0];
                    vboP[0].vy = v[triangle.v[0] - 1][1];
                    vboP[0].vz = v[triangle.v[0] - 1][2];
                    vboP[0].tx = triangle.t[0] > 0 ? t[triangle.t[0] - 1][0] : 0.F;
                    vboP[0].ty = triangle.t[0] > 0 ? t[triangle.t[0] - 1][1] : 0.F;
                    vboP[0].nx = triangle.n[0] > 0 ? n[triangle.n[0] - 1][0] : 0.F;
                    vboP[0].ny = triangle.n[0] > 0 ? n[triangle.n[0] - 1][1] : 0.F;
                    vboP[0].nz = triangle.n[0] > 0 ? n[triangle.n[0] - 1][2] : 0.F;

                    vboP[1].vx = v[triangle.v[1] - 1][0];
                    vboP[1].vy = v[triangle.v[1] - 1][1];
                    vboP[1].vz = v[triangle.v[1] - 1][2];
                    vboP[1].tx = triangle.t[1] > 0 ? t[triangle.t[1] - 1][0] : 0.F;
                    vboP[1].ty = triangle.t[1] > 0 ? t[triangle.t[1] - 1][1] : 0.F;
                    vboP[1].nx = triangle.n[1] > 0 ? n[triangle.n[1] - 1][0] : 0.F;
                    vboP[1].ny = triangle.n[1] > 0 ? n[triangle.n[1] - 1][1] : 0.F;
                    vboP[1].nz = triangle.n[1] > 0 ? n[triangle.n[1] - 1][2] : 0.F;

                    vboP[2].vx = v[triangle.v[2] - 1][0];
                    vboP[2].vy = v[triangle.v[2] - 1][1];
                    vboP[2].vz = v[triangle.v[2] - 1][2];
                    vboP[2].tx = triangle.t[2] > 0 ? t[triangle.t[2] - 1][0] : 0.F;
                    vboP[2].ty = triangle.t[2] > 0 ? t[triangle.t[2] - 1][1] : 0.F;
                    vboP[2].nx = triangle.n[2] > 0 ? n[triangle.n[2] - 1][0] : 0.F;
                    vboP[2].ny = triangle.n[2] > 0 ? n[triangle.n[2] - 1][1] : 0.F;
                    vboP[2].nz = triangle.n[2] > 0 ? n[triangle.n[2] - 1][2] : 0.F;

                    vboP += 3;
                }
                out.first = gl::VBO::create(mesh.triangles.size() * 3, sizeof(VBOData));
                out.first->copy(vboData);

                out.second = gl::VAO::create(out.first->getID());
                out.second->bind();
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)0);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)12);
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)20);
                glEnableVertexAttribArray(2);
                break;
            }
            }
            return out;
        }
    }
}