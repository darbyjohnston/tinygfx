// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IPopup.h>

namespace tg
{
    namespace ui
    {
        class IWindow;

        //! Base class for dialog widgets.
        class IDialog : public IPopup
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& objectName,
                const std::shared_ptr<IWidget>& parent = nullptr);

            IDialog();

        public:
            virtual ~IDialog() = 0;

            //! Open the dialog.
            void open(const std::shared_ptr<IWindow>&);

            //! Get whether the dialog is open.
            bool isOpen() const;

            //! Close the dialog.
            void close() override;

            //! Set the close callback.
            void setCloseCallback(const std::function<void(void)>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;

        private:
            TG_PRIVATE();
        };
    }
}
