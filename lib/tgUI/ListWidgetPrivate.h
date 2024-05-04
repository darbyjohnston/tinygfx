// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ListWidget.h>

namespace tg
{
    namespace ui
    {
        class ListItemsWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                ButtonGroupType,
                const std::shared_ptr<IWidget>& parent);

            ListItemsWidget();

        public:
            virtual ~ListItemsWidget();

            static std::shared_ptr<ListItemsWidget> create(
                const std::shared_ptr<core::Context>&,
                ButtonGroupType,
                const std::shared_ptr<IWidget>& parent = nullptr);

            const std::vector<std::string>& getItems() const;
            void setItems(const std::vector<std::string>&);
            bool getChecked(int) const;
            void setChecked(int, bool);
            void setCallback(const std::function<void(int, bool)>&);

            int getCurrent() const;
            void setCurrent(int);
            std::shared_ptr<core::IObservableValue<int> > observeCurrent() const;

            const std::string& getSearch() const;
            void setSearch(const std::string&);
            void clearSearch();

            FontRole getFontRole() const;
            void setFontRole(FontRole);

            core::Box2I getRect(int) const;

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void mouseLeaveEvent() override;
            void mouseMoveEvent(MouseMoveEvent&) override;
            void mousePressEvent(MouseClickEvent&) override;
            void mouseReleaseEvent(MouseClickEvent&) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            int _getItemHeight() const;
            int _posToIndex(int) const;
            
            void _action(int);

            TG_PRIVATE();
        };
    }
}
