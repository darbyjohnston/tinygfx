// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidget.h>

namespace tg
{
    namespace examples
    {
        namespace textedit
        {
            class TextWidget : public ui::IWidget
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    const std::shared_ptr<IWidget>& parent);

                TextWidget();

            public:
                virtual ~TextWidget();

                static std::shared_ptr<TextWidget> create(
                    const std::shared_ptr<core::Context>&,
                    const std::shared_ptr<IWidget>& parent = nullptr);

            private:
                TG_PRIVATE();
            };
        }
    }
}
