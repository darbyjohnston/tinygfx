// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/Window.h>

#include <dtk/core/Timer.h>

namespace tg
{
    namespace examples
    {
        namespace noise
        {
            class Window : public dtk::Window
            {
            protected:
                void _init(
                    const std::shared_ptr<dtk::Context>&,
                    const std::string& name,
                    const dtk::Size2I&);

            public:
                virtual ~Window();

                static std::shared_ptr<Window> create(
                    const std::shared_ptr<dtk::Context>&,
                    const std::string& name,
                    const dtk::Size2I&);

                void setGeometry(const dtk::Box2I&) override;
                void drawEvent(const dtk::Box2I&, const dtk::DrawEvent&) override;

            private:
                void _render();
                void _tick();

                std::shared_ptr<dtk::Image> _image;
                std::shared_ptr<dtk::Timer> _timer;
                double _noiseZ = 0.0;
            };
        }
    }
}
