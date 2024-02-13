// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidget.h>

namespace tg
{
    namespace ui
    {
        //! \name File Widgets
        ///@{

        //! File edit widget.
        class FileEdit : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            FileEdit();

        public:
            virtual ~FileEdit();

            //! Create a new widget.
            static std::shared_ptr<FileEdit> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the path.
            void setPath(const std::string&);

            //! Get the path.
            const std::string& getPath() const;

            //! Set the callback.
            void setCallback(const std::function<void(const std::string&)>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            void _openDialog();

            TG_PRIVATE();
        };

        ///@}
    }
}
