// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkUIApp/Window.h>

#include <dtkCore/Timer.h>

namespace tg
{
    namespace examples
    {
        namespace noise
        {
            class Window : public dtk::ui::Window
            {
            protected:
                void _init(
                    const std::shared_ptr<dtk::core::Context>&,
                    const std::string& name,
                    const dtk::core::Size2I&);

            public:
                virtual ~Window();

                static std::shared_ptr<Window> create(
                    const std::shared_ptr<dtk::core::Context>&,
                    const std::string& name,
                    const dtk::core::Size2I&);

                void setGeometry(const dtk::core::Box2I&) override;
                void drawEvent(const dtk::core::Box2I&, const dtk::ui::DrawEvent&) override;

            private:
                void _render();
                void _tick();

                std::shared_ptr<dtk::core::Image> _image;
                std::shared_ptr<dtk::core::Timer> _timer;
                double _noiseZ = 0.0;
            };
        }
    }
}
