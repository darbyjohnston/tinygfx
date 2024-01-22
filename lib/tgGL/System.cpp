// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgGL/System.h>

#include <tgGL/GL.h>

#include <tgCore/Context.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

namespace tg
{
    namespace gl
    {
        namespace
        {
            void glfwErrorCallback(int, const char* description)
            {
                std::cerr << "GLFW ERROR: " << description << std::endl;
            }
        }
        
        struct System::Private
        {
            bool glfwInit = false;
        };
        
        System::System(const std::shared_ptr<core::Context>& context) :
            ISystem(context, "tg::gl::System"),
            _p(new Private)
        {
            TG_P();
            
            // Initialize GLFW.
            glfwSetErrorCallback(glfwErrorCallback);
            int glfwMajor = 0;
            int glfwMinor = 0;
            int glfwRevision = 0;
            glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRevision);
            if (!glfwInit())
            {
                //! \todo Do not throw for now so that non-OpenGL tests can run.
                //throw std::runtime_error("Cannot initialize GLFW");
            }
            p.glfwInit = true;
        }

        System::~System()
        {
            TG_P();
            if (p.glfwInit)
            {
                glfwTerminate();
            }
        }

        std::shared_ptr<System> System::create(const std::shared_ptr<core::Context>& context)
        {
            return std::shared_ptr<System>(new System(context));
        }
    }
}