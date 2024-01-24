// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGL/Init.h>

#include <tgGL/GL.h>
#include <tgGL/System.h>

#include <tgCore/Context.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

using namespace tg::core;

namespace tg
{
    namespace gl
    {
        void init(const std::shared_ptr<Context>& context)
        {
            if (!context->getSystem<System>())
            {
                context->addSystem(System::create(context));
            }
        }

        void initGLAD()
        {
#if defined(TINYGFX_API_GL_4_1)
            gladLoaderLoadGL();
#elif defined(TINYGFX_API_GLES_2)
            gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress);
#endif // TINYGFX_API_GL_4_1
        }
    }
}
