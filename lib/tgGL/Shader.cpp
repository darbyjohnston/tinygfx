// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGL/Shader.h>

#include <tgGL/GL.h>

#include <tgCore/Color.h>
#include <tgCore/Format.h>
#include <tgCore/String.h>

#include <iostream>

namespace tg
{
    namespace gl
    {
        struct Shader::Private
        {
            std::string vertexSource;
            std::string fragmentSource;
            GLuint vertex = 0;
            GLuint fragment = 0;
            GLuint program = 0;
        };

        void Shader::_init()
        {
            TG_P();

            p.vertex = glCreateShader(GL_VERTEX_SHADER);
            if (!p.vertex)
            {
                throw std::runtime_error("Cannot create vertex shader");
            }
            const char* src = p.vertexSource.c_str();
            glShaderSource(p.vertex, 1, &src, NULL);
            glCompileShader(p.vertex);
            int success = 0;
            glGetShaderiv(p.vertex, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                char infoLog[core::cStringSize];
                glGetShaderInfoLog(p.vertex, core::cStringSize, NULL, infoLog);
                auto lines = core::split(
                    p.vertexSource,
                    { '\n', '\r' },
                    core::SplitOptions::KeepEmpty);
                for (size_t i = 0; i < lines.size(); ++i)
                {
                    lines[i].insert(0, core::Format("{0}: ").arg(i));
                }
                lines.push_back(infoLog);
                //std::cout << core::join(lines, '\n') << std::endl;
                throw std::runtime_error(core::join(lines, '\n'));
            }

            p.fragment = glCreateShader(GL_FRAGMENT_SHADER);
            if (!p.fragment)
            {
                throw std::runtime_error("Cannot create fragment shader");
            }
            src = p.fragmentSource.c_str();
            glShaderSource(p.fragment, 1, &src, NULL);
            glCompileShader(p.fragment);
            glGetShaderiv(p.fragment, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                char infoLog[core::cStringSize];
                glGetShaderInfoLog(p.fragment, core::cStringSize, NULL, infoLog);
                auto lines = core::split(
                    p.fragmentSource,
                    { '\n', '\r' },
                    core::SplitOptions::KeepEmpty);
                for (size_t i = 0; i < lines.size(); ++i)
                {
                    lines[i].insert(0, core::Format("{0}: ").arg(i));
                }
                lines.push_back(infoLog);
                //std::cout << core::join(lines, '\n') << std::endl;
                throw std::runtime_error(core::join(lines, '\n'));
            }

            p.program = glCreateProgram();
            glAttachShader(p.program, p.vertex);
            glAttachShader(p.program, p.fragment);
            glLinkProgram(p.program);
            glGetProgramiv(p.program, GL_LINK_STATUS, &success);
            if (!success)
            {
                char infoLog[core::cStringSize];
                glGetProgramInfoLog(p.program, core::cStringSize, NULL, infoLog);
                throw std::runtime_error(infoLog);
            }
        }

        Shader::Shader() :
            _p(new Private)
        {}

        Shader::~Shader()
        {
            TG_P();
            if (p.program)
            {
                glDeleteProgram(p.program);
                p.program = 0;
            }
            if (p.vertex)
            {
                glDeleteShader(p.vertex);
                p.vertex = 0;
            }
            if (p.fragment)
            {
                glDeleteShader(p.fragment);
                p.fragment = 0;
            }
        }

        std::shared_ptr<Shader> Shader::create(
            const std::string& vertexSource,
            const std::string& fragmentSource)
        {
            auto out = std::shared_ptr<Shader>(new Shader);
            out->_p->vertexSource = vertexSource;
            out->_p->fragmentSource = fragmentSource;
            out->_init();
            return out;
        }

        const std::string& Shader::getVertexSource() const
        {
            return _p->vertexSource;
        }

        const std::string& Shader::getFragmentSource() const
        {
            return _p->fragmentSource;
        }

        unsigned int Shader::getProgram() const
        {
            return _p->program;
        }

        void Shader::bind()
        {
            glUseProgram(_p->program);
        }

        void Shader::setUniform(int location, int value)
        {
            glUniform1i(location, value);
        }

        void Shader::setUniform(int location, float value)
        {
            glUniform1f(location, value);
        }

        void Shader::setUniform(int location, const core::V2F& value)
        {
            glUniform2fv(location, 1, value.data());
        }

        void Shader::setUniform(int location, const core::V3F& value)
        {
            glUniform3fv(location, 1, value.data());
        }

        void Shader::setUniform(int location, const core::V4F& value)
        {
            glUniform4fv(location, 1, value.data());
        }

        void Shader::setUniform(int location, const core::M33F& value)
        {
            glUniformMatrix3fv(location, 1, GL_FALSE, value.data());
        }

        void Shader::setUniform(int location, const core::M44F& value)
        {
            glUniformMatrix4fv(location, 1, GL_FALSE, value.data());
        }

        void Shader::setUniform(int location, const core::Color4F& value)
        {
            glUniform4fv(location, 1, value.data());
        }

        void Shader::setUniform(int location, const float value[4])
        {
            glUniform4fv(location, 1, value);
        }

        void Shader::setUniform(int location, const std::vector<int>& value)
        {
            glUniform1iv(location, value.size(), &value[0]);
        }

        void Shader::setUniform(int location, const std::vector<float>& value)
        {
            glUniform1fv(location, value.size(), &value[0]);
        }

        void Shader::setUniform(int location, const std::vector<core::V3F>& value)
        {
            glUniform3fv(location, value.size(), value[0].data());
        }

        void Shader::setUniform(int location, const std::vector<core::V4F>& value)
        {
            glUniform4fv(location, value.size(), value[0].data());
        }

        void Shader::setUniform(const std::string& name, int value)
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }

        void Shader::setUniform(const std::string& name, float value)
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }

        void Shader::setUniform(const std::string& name, const core::V2F& value)
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }

        void Shader::setUniform(const std::string& name, const core::V3F& value)
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }

        void Shader::setUniform(const std::string& name, const core::V4F& value)
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }

        void Shader::setUniform(const std::string& name, const core::M33F& value)
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }

        void Shader::setUniform(const std::string& name, const core::M44F& value)
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }
        
        void Shader::setUniform(const std::string& name, const core::Color4F& value)
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }

        void Shader::setUniform(const std::string& name, const float value[4])
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }

        void Shader::setUniform(const std::string& name, const std::vector<int>& value)
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }

        void Shader::setUniform(const std::string& name, const std::vector<float>& value)
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }

        void Shader::setUniform(const std::string& name, const std::vector<core::V3F>& value)
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }

        void Shader::setUniform(const std::string& name, const std::vector<core::V4F>& value)
        {
            const GLint location = glGetUniformLocation(_p->program, name.c_str());
            setUniform(location, value);
        }
    }
}
