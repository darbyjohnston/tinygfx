// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "Window.h"

#include <tgRender/IRender.h>

using namespace tg::core;

namespace tg
{
    namespace examples
    {
        namespace simple
        {
            Window::Window(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                const Size2I& size) :
                IWindow(context, name, size)
            {}

            Window::~Window()
            {}
            
            std::shared_ptr<Window> Window::create(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                const Size2I& size)
            {
                return std::shared_ptr<Window>(new Window(context, name, size));
            }
            
            void Window::_draw(
                const core::V2F& contentScale,
                const std::shared_ptr<render::IRender>& render)
            {
                render->begin(getFrameBufferSize());

                const Box2F box(0, 0, getWidth(), getHeight());
                const auto& min = box.min();
                const auto& max = box.max();
                TriMesh2F mesh;
                mesh.v.push_back(V2F(min.x(), min.y()));
                mesh.v.push_back(V2F(max.x(), min.y()));
                mesh.v.push_back(V2F(max.x(), max.y()));
                mesh.v.push_back(V2F(min.x(), max.y()));
                mesh.c.push_back(V4F(0.F, 0.F, 0.F, 1.F));
                mesh.c.push_back(V4F(0.F, 0.F, 0.F, 1.F));
                mesh.c.push_back(V4F(1.F, 1.F, 1.F, 1.F));
                mesh.c.push_back(V4F(1.F, 1.F, 1.F, 1.F));
                Triangle2 triangle;
                triangle.v[0].v = 1;
                triangle.v[1].v = 2;
                triangle.v[2].v = 3;
                triangle.v[0].c = 1;
                triangle.v[1].c = 2;
                triangle.v[2].c = 3;
                mesh.triangles.push_back(triangle);
                triangle.v[0].v = 3;
                triangle.v[1].v = 4;
                triangle.v[2].v = 1;
                triangle.v[0].c = 3;
                triangle.v[1].c = 4;
                triangle.v[2].c = 1;
                mesh.triangles.push_back(triangle);
                render->drawColorMesh(mesh);
                
                Box2F box2 = margin(box, -100.F);
                render::LineOptions lineOptions;
                lineOptions.width = 10.F * contentScale.x();
                render->drawLine(
                    V2F(box2.min().x(), box2.min().y()),
                    V2F(box2.max().x(), box2.max().y()),
                    Color4F(1.F, 0.F, 0.F, 1.F),
                    lineOptions);
                render->drawLine(
                    V2F(box2.min().x(), box2.max().y()),
                    V2F(box2.max().x(), box2.min().y()),
                    Color4F(1.F, 0.F, 0.F, 1.F),
                    lineOptions);

                render->end();
            }
        }
    }
}

