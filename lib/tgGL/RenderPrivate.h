// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGL/Render.h>

#include <tgGL/GL.h>
#include <tgGL/Mesh.h>
#include <tgGL/Shader.h>
#include <tgGL/TextureAtlas.h>

#include <map>

namespace tg
{
    namespace gl
    {
        std::string vertexSource();
        std::string meshFragmentSource();
        std::string colorMeshVertexSource();
        std::string colorMeshFragmentSource();
        std::string textFragmentSource();
        std::string imageFragmentSource();

        struct Render::Private
        {
            core::Size2I size;
            render::Options options;
            core::Box2I viewport;
            bool clipRectEnabled = false;
            core::Box2I clipRect;
            core::M44F transform;
            
            std::map<std::string, std::shared_ptr<gl::Shader> > shaders;
            std::shared_ptr<TextureCache> textureCache;
            std::shared_ptr<gl::TextureAtlas> glyphTextureAtlas;
            std::map<core::GlyphInfo, gl::TextureAtlasID> glyphIDs;
            std::map<std::string, std::shared_ptr<gl::VBO> > vbos;
            std::map<std::string, std::shared_ptr<gl::VAO> > vaos;
        };
    }
}

