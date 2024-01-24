// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUIApp/IWindow.h>

namespace tg
{
    namespace examples
    {
        namespace simple
        {
            //! Window.
            class Window : public ui::IWindow
            {
                TG_NON_COPYABLE(Window);

            protected:
                Window(
                    const std::shared_ptr<core::Context>&,
                    const std::string& name,
                    const core::Size2I&);

            public:
                virtual ~Window();
                
                static std::shared_ptr<Window> create(
                    const std::shared_ptr<core::Context>&,
                    const std::string& name,
                    const core::Size2I&);

            protected:
                void _draw(
                    const core::V2F& contentScale,
                    const std::shared_ptr<core::FontSystem>&,
                    const std::shared_ptr<render::IRender>&) override;
            };
        }
    }
}

