// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Matrix3.h>
#include <tgCore/Matrix4.h>
#include <tgCore/Vector2.h>
#include <tgCore/Vector3.h>
#include <tgCore/Vector4.h>

#include <tgGlad/gl.h>

#include <memory>
#include <string>
#include <vector>

namespace tg
{
    namespace gl
    {
        //! Shader.
        class Shader
        {
            void _init(
                const std::string& vertexSource,
                const std::string& fragmentSource);

            Shader();

        public:
            ~Shader();

            //! Create a new shader.
            static std::shared_ptr<Shader> create(
                const std::string& vertexSource,
                const std::string& fragmentSource);

            //! Bind the shader.
            void bind();

            //! \name Uniforms
            ///@{

            void setUniform(GLint, int);
            void setUniform(GLint, float);
            void setUniform(GLint, const math::Vector2f&);
            void setUniform(GLint, const math::Vector3f&);
            void setUniform(GLint, const math::Vector4f&);
            void setUniform(GLint, const math::Matrix3x3f&);
            void setUniform(GLint, const math::Matrix4x4f&);
            void setUniform(GLint, const float[4]);

            void setUniform(GLint, const std::vector<int>&);
            void setUniform(GLint, const std::vector<float>&);
            void setUniform(GLint, const std::vector<math::Vector3f>&);
            void setUniform(GLint, const std::vector<math::Vector4f>&);

            void setUniform(const std::string&, int);
            void setUniform(const std::string&, float);
            void setUniform(const std::string&, const math::Vector2f&);
            void setUniform(const std::string&, const math::Vector3f&);
            void setUniform(const std::string&, const math::Vector4f&);
            void setUniform(const std::string&, const math::Matrix3x3f&);
            void setUniform(const std::string&, const math::Matrix4x4f&);
            void setUniform(const std::string&, const float[4]);

            void setUniform(const std::string&, const std::vector<int>&);
            void setUniform(const std::string&, const std::vector<float>&);
            void setUniform(const std::string&, const std::vector<math::Vector3f>&);
            void setUniform(const std::string&, const std::vector<math::Vector4f>&);

            ///@}

        private:
            std::string _vertexSource;
            std::string _fragmentSource;
            GLuint _vertex = 0;
            GLuint _fragment = 0;
            GLuint _program = 0;
        };
    }
}
