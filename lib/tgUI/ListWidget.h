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

            //! Get the items.
            const std::vector<std::string>& getItems() const;

            //! Set the items.
            void setItems(const std::vector<std::string>&);

            //! Get the current item.
            int getCurrentItem() const;

            //! Set the current item.
            void setCurrentItem(int);

            //! Set the callback.
            void setCallback(const std::function<void(int)>&);

            //! Get the search.
            const std::string& getSearch() const;

            //! Set the search.
            void setSearch(const std::string&);

            //! Clear the search.
            void clearSearch();

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
