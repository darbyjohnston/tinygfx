// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidget.h>

namespace tg
{
    namespace ui
    {
        //! Base class for popups.
        class IPopup : public IWidget
        {
            TG_NON_COPYABLE(IPopup);

        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& objectName,
                const std::shared_ptr<IWidget>& parent = nullptr);

            IPopup();

        public:
            virtual ~IPopup() = 0;

            //! Close the popup.
            virtual void close() = 0;

            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;
        };
    }
}
