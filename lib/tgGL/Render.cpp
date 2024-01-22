// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGL/RenderPrivate.h>

namespace tg
{
    namespace gl
    {
        void Render::_init(const std::shared_ptr<core::Context>& context)
        {
            IRender::_init(context);
        }

        Render::Render() :
            _p(new Private)
        {}

        Render::~Render()
        {}

        std::shared_ptr<Render> Render::create(
            const std::shared_ptr<core::Context>& context)
        {
            auto out = std::shared_ptr<Render>(new Render);
            out->_init(context);
            return out;
        }

        void Render::begin(
            const core::Size2I& size,
            const render::Options& options)
        {
            TG_P();

            p.size = size;
            p.options = options;

            if (!p.shaders["rect"])
            {
                p.shaders["rect"] = gl::Shader::create(
                    vertexSource(),
                    meshFragmentSource());
            }
            if (!p.shaders["line"])
            {
                p.shaders["line"] = gl::Shader::create(
                    vertexSource(),
                    meshFragmentSource());
            }
            if (!p.shaders["mesh"])
            {
                p.shaders["mesh"] = gl::Shader::create(
                    vertexSource(),
                    meshFragmentSource());
            }
            if (!p.shaders["colorMesh"])
            {
                p.shaders["colorMesh"] = gl::Shader::create(
                    colorMeshVertexSource(),
                    colorMeshFragmentSource());
            }

            p.vbos["rect"] = gl::VBO::create(2 * 3, gl::VBOType::Pos2_F32);
            p.vaos["rect"] = gl::VAO::create(p.vbos["rect"]->getType(), p.vbos["rect"]->getID());
            p.vbos["line"] = gl::VBO::create(2 * 3, gl::VBOType::Pos2_F32);
            p.vaos["line"] = gl::VAO::create(p.vbos["line"]->getType(), p.vbos["line"]->getID());

            setViewport(core::Box2I(0, 0, size.w(), size.h()));
            if (options.clear)
            {
                clearViewport(options.clearColor);
            }
            setTransform(core::ortho(
                0.F,
                static_cast<float>(size.w()),
                static_cast<float>(size.h()),
                0.F,
                -1.F,
                1.F));
        }
        
        void Render::end()
        {}

        core::Size2I Render::getRenderSize() const
        {
            return _p->size;
        }

        void Render::setRenderSize(const core::Size2I& value)
        {
            _p->size = value;
        }

        core::Box2I Render::getViewport() const
        {
            return _p->viewport;
        }

        void Render::setViewport(const core::Box2I& value)
        {
            TG_P();
            p.viewport = value;
            glViewport(
                value.x(),
                p.size.h() - value.h() - value.y(),
                value.w(),
                value.h());
        }

        void Render::clearViewport(const core::Color4F& value)
        {
            glClearColor(value.r(), value.g(), value.b(), value.a());
            glClear(GL_COLOR_BUFFER_BIT);
        }

        bool Render::getClipRectEnabled() const
        {
            return _p->clipRectEnabled;
        }

        void Render::setClipRectEnabled(bool value)
        {
            TG_P();
            p.clipRectEnabled = value;
            if (p.clipRectEnabled)
            {
                glEnable(GL_SCISSOR_TEST);
            }
            else
            {
                glDisable(GL_SCISSOR_TEST);
            }
        }

        core::Box2I Render::getClipRect() const
        {
            return _p->clipRect;
        }

        void Render::setClipRect(const core::Box2I& value)
        {
            TG_P();
            p.clipRect = value;
            if (value.w() > 0 && value.h() > 0)
            {
                glScissor(
                    value.x(),
                    p.size.h() - value.h() - value.y(),
                    value.w(),
                    value.h());
            }
        }

        core::M44F Render::getTransform() const
        {
            return _p->transform;
        }

        void Render::setTransform(const core::M44F& value)
        {
            TG_P();
            p.transform = value;
            for (auto i : p.shaders)
            {
                i.second->bind();
                i.second->setUniform("transform.mvp", value);
            }
        }
    }
}

