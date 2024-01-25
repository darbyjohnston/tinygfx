// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IPopup.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        void IPopup::_init(
            const std::shared_ptr<Context>& context,
            const std::string& objectName,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, objectName, parent);
        }

        IPopup::IPopup()
        {}

        IPopup::~IPopup()
        {}

        void IPopup::keyPressEvent(KeyEvent & event)
        {
            if (0 == event.modifiers)
            {
                if (Key::Escape == event.key)
                {
                    event.accept = true;
                    close();
                }
            }
        }

        void IPopup::keyReleaseEvent(KeyEvent & event)
        {
            event.accept = true;
        }
    }
}
