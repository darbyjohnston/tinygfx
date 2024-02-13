// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IPopup.h>

namespace tg
{
    namespace ui
    {
        //! \name Popup Widgets
        ///@{
        
        //! Tooltip.
        class Tooltip : public IPopup
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& text,
                const core::V2I& pos,
                const std::shared_ptr<IWidget>&);

            Tooltip();

        public:
            virtual ~Tooltip();

            //! Create a new tooltip.
            static std::shared_ptr<Tooltip> create(
                const std::shared_ptr<core::Context>&,
                const std::string& text,
                const core::V2I& pos,
                const std::shared_ptr<IWidget>&);

            void close() override;

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;

        private:
            TG_PRIVATE();
        };
        
        ///@}
    }
}
