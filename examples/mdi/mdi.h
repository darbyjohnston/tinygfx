// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUIApp/Window.h>

namespace tg
{
    namespace examples
    {
        namespace mdi
        {
            class Window : public ui::Window
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    const std::string& name,
                    const core::Size2I&);

                Window() = default;

            public:
                virtual ~Window();

                static std::shared_ptr<Window> create(
                    const std::shared_ptr<core::Context>&,
                    const std::string& name,
                    const core::Size2I&);
            };
        }
    }
}
