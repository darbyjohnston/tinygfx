// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include "Sol001.h"

#include <tgGL/Mesh.h>

namespace tg
{
    namespace
    {
        const std::string vertexSource =
            "#version 410\n"
            "\n"
            "in vec3 vPos;\n"
            "in vec2 vTexture;\n"
            "out vec2 fTexture;\n"
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

        const std::string fragmentSource =
            "#version 410\n"
            "\n"
            "in vec2 fTexture;\n"
            "out vec4 fColor;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    fColor.r = 0.0;\n"
            "    fColor.g = fTexture.x;\n"
            "    fColor.b = fTexture.y;\n"
            "    fColor.a = 1.0;\n"
            "}\n";
    }

    Sol001::Sol001()
    {}

    std::shared_ptr<Sol001> Sol001::create()
    {
        return std::shared_ptr<Sol001>(new Sol001);
    }

    void Sol001::tick(float delta)
    {

    }

    void Sol001::render(const math::Vector2i& size)
    {
        glViewport(0, 0, size.x, size.y);
        glClearColor(0.F, 0.F, 1.F, 0.F);
        glClear(GL_COLOR_BUFFER_BIT);

        if (!_shader)
        {
            _shader = gl::Shader::create(vertexSource, fragmentSource);
        }
        _shader->bind();
        const auto mvp = math::ortho<float>(0.F, size.x, size.y, 0.F, -1.F, 1.F);
        _shader->setUniform("transform.mvp", mvp);

        std::vector<uint8_t> vboData;
        struct VBOData
        {
            float vx;
            float vy;
            uint16_t tx;
            uint16_t ty;
        };
        vboData.resize(4 * sizeof(VBOData));
        auto* vboP = reinterpret_cast<VBOData*>(vboData.data());
        vboP[0].vx = 0.F;
        vboP[0].vy = 0.F;
        vboP[0].tx = 0;
        vboP[0].ty = 0;
        vboP[1].vx = size.x;
        vboP[1].vy = 0.F;
        vboP[1].tx = 65535;
        vboP[1].ty = 0;
        vboP[2].vx = 0.F;
        vboP[2].vy = size.y;
        vboP[2].tx = 0;
        vboP[2].ty = 65535;
        vboP[3].vx = size.x;
        vboP[3].vy = size.y;
        vboP[3].tx = 65535;
        vboP[3].ty = 65535;
        auto vbo = gl::VBO::create(4, sizeof(VBOData));
        vbo->copy(vboData);

        auto vao = gl::VAO::create(vbo->getID());
        vao->bind();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VBOData), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_UNSIGNED_SHORT, GL_TRUE, sizeof(VBOData), (GLvoid*)8);
        glEnableVertexAttribArray(1);
        vao->draw(GL_TRIANGLE_STRIP, 0, 4);
    }
}
