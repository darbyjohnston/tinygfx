// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/ButtonGroup.h>
#include <tgUI/IWidget.h>

namespace tg
{
    namespace ui
    {
        //! \name List Widgets
        ///@{

        //! List widget.
        class ListWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                ButtonGroupType,
                const std::shared_ptr<IWidget>& parent);

            ListWidget();

        public:
            virtual ~ListWidget();

            //! Create a new widget.
            static std::shared_ptr<ListWidget> create(
                const std::shared_ptr<core::Context>&,
                ButtonGroupType,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the items.
            void setItems(const std::vector<std::string>&);

            //! Set the current item.
            void setCurrentItem(int);

            //! Set the callback.
            void setCallback(const std::function<void(int)>&);

            //! Set the search.
            void setSearch(const std::string&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            void _widgetUpdate();
            void _searchUpdate();

            TG_PRIVATE();
        };

        ///@}
    }
}
