// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUIApp/Window.h>

#include <tgCore/Timer.h>

namespace tg
{
    namespace examples
    {
        namespace noise
        {
            class Window : public ui::Window
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    const std::string& name,
                    const core::Size2I&);

            public:
                virtual ~Window();

                static std::shared_ptr<Window> create(
                    const std::shared_ptr<core::Context>&,
                    const std::string& name,
                    const core::Size2I&);

                void setGeometry(const core::Box2I&) override;
                void drawEvent(const core::Box2I&, const ui::DrawEvent&) override;

            private:
                void _tick();

                std::shared_ptr<core::Image> _image;
                std::shared_ptr<core::Timer> _timer;
                double _noiseZ = 0.0;
            };
        }
    }
}
