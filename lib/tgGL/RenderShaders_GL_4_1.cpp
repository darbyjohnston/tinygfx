// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGL/RenderPrivate.h>

#include <tgCore/Format.h>

using namespace tg::core;

namespace tg
{
    namespace gl
    {
        std::string vertexSource()
        {
            return
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
        }

        std::string meshFragmentSource()
        {
            return
                "#version 410\n"
                "\n"
                "out vec4 outColor;\n"
                "\n"
                "uniform vec4 color;\n"
                "\n"
                "void main()\n"
                "{\n"
                "\n"
                "    outColor = color;\n"
                "}\n";
        }

        std::string colorMeshVertexSource()
        {
            return
                "#version 410\n"
                "\n"
                "layout(location = 0) in vec3 vPos;\n"
                "layout(location = 1) in vec4 vColor;\n"
                "out vec4 fColor;\n"
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
                "#version 410\n"
                "\n"
                "in vec4 fColor;\n"
                "out vec4 outColor;\n"
                "\n"
                "uniform vec4 color;\n"
                "\n"
                "void main()\n"
                "{\n"
                "\n"
                "    outColor = fColor * color;\n"
                "}\n";
        }

        std::string textFragmentSource()
        {
            return
                "#version 410\n"
                "\n"
                "in vec2 fTexture;\n"
                "out vec4 outColor;\n"
                "\n"
                "uniform vec4 color;\n"
                "uniform sampler2D textureSampler;\n"
                "\n"
                "void main()\n"
                "{\n"
                "\n"
                "    outColor.r = color.r;\n"
                "    outColor.g = color.g;\n"
                "    outColor.b = color.b;\n"
                "    outColor.a = color.a * texture(textureSampler, fTexture).r;\n"
                "}\n";
        }

        namespace
        {
            const std::string imageType =
                "// enum tg::core::ImageType\n"
                "const uint ImageType_None              = 0;\n"
                "const uint ImageType_L_U8              = 1;\n"
                "const uint ImageType_L_U16             = 2;\n"
                "const uint ImageType_L_U32             = 3;\n"
                "const uint ImageType_L_F16             = 4;\n"
                "const uint ImageType_L_F32             = 5;\n"
                "const uint ImageType_LA_U8             = 6;\n"
                "const uint ImageType_LA_U32            = 7;\n"
                "const uint ImageType_LA_U16            = 8;\n"
                "const uint ImageType_LA_F16            = 9;\n"
                "const uint ImageType_LA_F32            = 10;\n"
                "const uint ImageType_RGB_U8            = 11;\n"
                "const uint ImageType_RGB_U10           = 12;\n"
                "const uint ImageType_RGB_U16           = 13;\n"
                "const uint ImageType_RGB_U32           = 14;\n"
                "const uint ImageType_RGB_F16           = 15;\n"
                "const uint ImageType_RGB_F32           = 16;\n"
                "const uint ImageType_RGBA_U8           = 17;\n"
                "const uint ImageType_RGBA_U16          = 18;\n"
                "const uint ImageType_RGBA_U32          = 19;\n"
                "const uint ImageType_RGBA_F16          = 20;\n"
                "const uint ImageType_RGBA_F32          = 21;\n"
                "const uint ImageType_YUV_420P_U8       = 22;\n"
                "const uint ImageType_YUV_422P_U8       = 23;\n"
                "const uint ImageType_YUV_444P_U8       = 24;\n"
                "const uint ImageType_YUV_420P_U16      = 25;\n"
                "const uint ImageType_YUV_422P_U16      = 26;\n"
                "const uint ImageType_YUV_444P_U16      = 27;\n"
                "const uint ImageType_ARGB_4444_Premult = 28;\n";

            const std::string videoLevels =
                "// enum tg::core::VideoLevels\n"
                "const uint VideoLevels_FullRange  = 0;\n"
                "const uint VideoLevels_LegalRange = 1;\n";

            const std::string sampleTexture =
                "vec4 sampleTexture("
                "    vec2 textureCoord,\n"
                "    int imageType,\n"
                "    int videoLevels,\n"
                "    vec4 yuvCoefficients,\n"
                "    int imageChannels,\n"
                "    sampler2D s0,\n"
                "    sampler2D s1,\n"
                "    sampler2D s2)\n"
                "{\n"
                "    vec4 c;\n"
                "    if (ImageType_YUV_420P_U8 == imageType ||\n"
                "        ImageType_YUV_422P_U8 == imageType ||\n"
                "        ImageType_YUV_444P_U8 == imageType ||\n"
                "        ImageType_YUV_420P_U16 == imageType ||\n"
                "        ImageType_YUV_422P_U16 == imageType ||\n"
                "        ImageType_YUV_444P_U16 == imageType)\n"
                "    {\n"
                "        if (VideoLevels_FullRange == videoLevels)\n"
                "        {\n"
                "            float y  = texture(s0, textureCoord).r;\n"
                "            float cb = texture(s1, textureCoord).r - 0.5;\n"
                "            float cr = texture(s2, textureCoord).r - 0.5;\n"
                "            c.r = y + (yuvCoefficients.x * cr);\n"
                "            c.g = y - (yuvCoefficients.z * cb) - (yuvCoefficients.w * cr);\n"
                "            c.b = y + (yuvCoefficients.y * cb);\n"
                "        }\n"
                "        else if (VideoLevels_LegalRange == videoLevels)\n"
                "        {\n"
                "            float y  = (texture(s0, textureCoord).r - (16.0 / 255.0)) * (255.0 / (235.0 - 16.0));\n"
                "            float cb = (texture(s1, textureCoord).r - (16.0 / 255.0)) * (255.0 / (240.0 - 16.0)) - 0.5;\n"
                "            float cr = (texture(s2, textureCoord).r - (16.0 / 255.0)) * (255.0 / (240.0 - 16.0)) - 0.5;\n"
                "            c.r = y + (yuvCoefficients.x * cr);\n"
                "            c.g = y - (yuvCoefficients.z * cb) - (yuvCoefficients.w * cr);\n"
                "            c.b = y + (yuvCoefficients.y * cb);\n"
                "        }\n"
                "        c.a = 1.0;\n"
                "    }\n"
                "    else\n"
                "    {\n"
                "        c = texture(s0, textureCoord);\n"
                "\n"
                "        // Swizzle for the image channels.\n"
                "        if (1 == imageChannels)\n"
                "        {\n"
                "            c.g = c.b = c.r;\n"
                "            c.a = 1.0;\n"
                "        }\n"
                "        else if (2 == imageChannels)\n"
                "        {\n"
                "            c.a = c.g;\n"
                "            c.g = c.b = c.r;\n"
                "        }\n"
                "        else if (3 == imageChannels)\n"
                "        {\n"
                "            c.a = 1.0;\n"
                "        }\n"
                "    }\n"
                "    return c;\n"
                "}\n";
        }

        std::string imageFragmentSource()
        {
            return Format(
                "#version 410\n"
                "\n"
                "in vec2 fTexture;\n"
                "out vec4 outColor;\n"
                "\n"
                "{0}\n"
                "\n"
                "{1}\n"
                "\n"
                "{2}\n"
                "\n"
                "uniform vec4      color;\n"
                "uniform int       imageType;\n"
                "uniform int       videoLevels;\n"
                "uniform vec4      yuvCoefficients;\n"
                "uniform int       imageChannels;\n"
                "uniform int       mirrorX;\n"
                "uniform int       mirrorY;\n"
                "uniform sampler2D textureSampler0;\n"
                "uniform sampler2D textureSampler1;\n"
                "uniform sampler2D textureSampler2;\n"
                "\n"
                "void main()\n"
                "{\n"
                "    vec2 t = fTexture;\n"
                "    if (1 == mirrorX)\n"
                "    {\n"
                "        t.x = 1.0 - t.x;\n"
                "    }\n"
                "    if (0 == mirrorY)\n"
                "    {\n"
                "        t.y = 1.0 - t.y;\n"
                "    }\n"
                "    outColor = sampleTexture("
                "        t,\n"
                "        imageType,\n"
                "        videoLevels,\n"
                "        yuvCoefficients,\n"
                "        imageChannels,\n"
                "        textureSampler0,\n"
                "        textureSampler1,\n"
                "        textureSampler2) *\n"
                "        color;\n"
                //"    outColor.a = 1.0;\n"
                "}\n").
                arg(imageType).
                arg(videoLevels).
                arg(sampleTexture);
        }
    }
}

