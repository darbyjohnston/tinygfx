// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidget.h>

namespace tg
{
    namespace ui
    {
        //! \name Layouts
        ///@{
        
        //! Bellows widget.
        class Bellows : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            Bellows();

        public:
            virtual ~Bellows();

            //! Create a new widget.
            static std::shared_ptr<Bellows> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Create a new widget.
            static std::shared_ptr<Bellows> create(
                const std::shared_ptr<core::Context>&,
                const std::string& text,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the text.
            const std::string& getText() const;

            //! Set the text.
            void setText(const std::string&);

            //! Set the widget.
            void setWidget(const std::shared_ptr<IWidget>&);

            //! Get whether the bellows is open.
            bool isOpen() const;

            //! Set whether the bellows is open.
            void setOpen(bool);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            TG_PRIVATE();
        };
        
        ///@}
    }
}
