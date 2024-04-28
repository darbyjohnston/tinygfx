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

        //! Tab bar widget.
        class TabBar : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            TabBar();

        public:
            virtual ~TabBar();

            //! Create a new widget.
            static std::shared_ptr<TabBar> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the tabs.
            const std::vector<std::string>& getTabs() const;

            //! Set the tabs.
            void setTabs(const std::vector<std::string>&);

            //! Add a tab.
            void addTab(const std::string&);

            //! Clear the tabs.
            void clearTabs();

            //! Get the current tab.
            int getCurrentTab() const;

            //! Set the current tab.
            void setCurrentTab(int);

            //! Set the callback.
            void setCallback(const std::function<void(int)>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            void _widgetUpdate();

            TG_PRIVATE();
        };

        ///@}
    }
}
