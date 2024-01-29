// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidgetPopup.h>

namespace tg
{
    namespace ui
    {
        //! Color popup.
        class ColorPopup : public IWidgetPopup
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const core::Color4F&,
                const std::shared_ptr<IWidget>& parent);

            ColorPopup();

        public:
            virtual ~ColorPopup();

            //! Create a new popup.
            static std::shared_ptr<ColorPopup> create(
                const std::shared_ptr<core::Context>&,
                const core::Color4F&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the callback.
            void setCallback(const std::function<void(const core::Color4F&)>&);

        private:
            TG_PRIVATE();
        };
    }
}
