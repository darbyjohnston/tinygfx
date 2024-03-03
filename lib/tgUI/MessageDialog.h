// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IDialog.h>

#include <tgCore/ISystem.h>

namespace tg
{
    namespace ui
    {
        //! \name Dialogs
        ///@{

        //! Message dialog.
        class MessageDialog : public IDialog
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& title,
                const std::string& text,
                const std::shared_ptr<IWidget>& parent);

            MessageDialog();

        public:
            virtual ~MessageDialog();

            //! Create a new widget.
            static std::shared_ptr<MessageDialog> create(
                const std::shared_ptr<core::Context>&,
                const std::string& title,
                const std::string& text,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the callback.
            void setCallback(const std::function<void(void)>&);

        private:
            TG_PRIVATE();
        };

        //! Confirmation dialog.
        class ConfirmDialog : public IDialog
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& title,
                const std::string& text,
                const std::shared_ptr<IWidget>& parent);

            ConfirmDialog();

        public:
            virtual ~ConfirmDialog();

            //! Create a new widget.
            static std::shared_ptr<ConfirmDialog> create(
                const std::shared_ptr<core::Context>&,
                const std::string& title,
                const std::string& text,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the callback.
            void setCallback(const std::function<void(bool)>&);

        private:
            TG_PRIVATE();
        };

        //! Message dialog system.
        class MessageDialogSystem : public core::ISystem
        {
        protected:
            MessageDialogSystem(const std::shared_ptr<core::Context>&);

        public:
            virtual ~MessageDialogSystem();

            //! Create a new system.
            static std::shared_ptr<MessageDialogSystem> create(
                const std::shared_ptr<core::Context>&);

            //! Open a message dialog.
            void message(
                const std::string& title,
                const std::string& text,
                const std::shared_ptr<IWindow>&);

            //! Open a confirmation dialog.
            void confirm(
                const std::string& title,
                const std::string& text,
                const std::shared_ptr<IWindow>&,
                const std::function<void(bool)>&);

        private:
            TG_PRIVATE();
        };

        ///@}
    }
}
