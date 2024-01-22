// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGL/RenderPrivate.h>

namespace tg
{
    namespace gl
    {
        std::string vertexSource()
        {
            return
                "precision mediump float;\n"
                "\n"
                "attribute vec3 vPos;\n"
                "attribute vec2 vTexture;\n"
                "varying vec2 fTexture;\n"
                "\n"
                "struct Transform\n"
                "{\n"
                "    mat4 mvp;\n"
                "};\n"
                "\n"
                "uniform Transform transform;\n"
                "\n"
                "void main()\n"
                "{\n"
                "    gl_Position = transform.mvp * vec4(vPos, 1.0);\n"
                "    fTexture = vTexture;\n"
                "}\n";
        }

        std::string meshFragmentSource()
        {
            return
                "precision mediump float;\n"
                "\n"
                "uniform vec4 color;\n"
                "\n"
                "void main()\n"
                "{\n"
                "\n"
                "    gl_FragColor = color;\n"
                "}\n";
        }

        std::string colorMeshVertexSource()
        {
            return
                "precision mediump float;\n"
                "\n"
                "attribute vec3 vPos;\n"
                "attribute vec4 vColor;\n"
                "varying vec4 fColor;\n"
                "\n"
                "struct Transform\n"
                "{\n"
                "    mat4 mvp;\n"
                "};\n"
                "\n"
                "uniform Transform transform;\n"
                "\n"
                "void main()\n"
                "{\n"
                "    gl_Position = transform.mvp * vec4(vPos, 1.0);\n"
                "    fColor = vColor;\n"
                "}\n";
        }

        std::string colorMeshFragmentSource()
        {
            return
                "precision mediump float;\n"
                "\n"
                "varying vec4 fColor;\n"
                "\n"
                "uniform vec4 color;\n"
                "\n"
                "void main()\n"
                "{\n"
                "\n"
                "    gl_FragColor = fColor * color;\n"
                "}\n";
        }
    }
}

