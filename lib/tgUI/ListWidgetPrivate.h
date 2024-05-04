// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ListWidget.h>

namespace tg
{
    namespace ui
    {
        class ItemsWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                ui::ButtonGroupType,
                const std::shared_ptr<ui::IWidget>& parent);

            ItemsWidget();

        public:
            virtual ~ItemsWidget();

            static std::shared_ptr<ItemsWidget> create(
                const std::shared_ptr<core::Context>&,
                ui::ButtonGroupType,
                const std::shared_ptr<ui::IWidget>& parent = nullptr);

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

            ui::FontRole getFontRole() const;
            void setFontRole(ui::FontRole);

            core::Box2I getRect(int) const;

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const ui::SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const ui::DrawEvent&) override;
            void mouseLeaveEvent() override;
            void mouseMoveEvent(ui::MouseMoveEvent&) override;
            void mousePressEvent(ui::MouseClickEvent&) override;
            void mouseReleaseEvent(ui::MouseClickEvent&) override;
            void keyPressEvent(ui::KeyEvent&) override;
            void keyReleaseEvent(ui::KeyEvent&) override;

        private:
            int _getMargin() const;
            int _posToIndex(int) const;
            int _indexToPos(int) const;
            
            void _action(int);

            TG_PRIVATE();
        };
    }
}
