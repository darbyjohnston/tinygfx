// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IMenuPopup.h>

#include <tgUI/DrawUtil.h>
#include <tgUI/IWindow.h>
#include <tgUI/ScrollWidget.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        namespace
        {
            class ContainerWidget : public IWidget
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>& parent = nullptr);

                ContainerWidget();

            public:
                virtual ~ContainerWidget();

                static std::shared_ptr<ContainerWidget> create(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>& parent = nullptr);

                void setGeometry(const Box2I&) override;
                void sizeHintEvent(const SizeHintEvent&) override;
            };

            void ContainerWidget::_init(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<IWidget>& parent)
            {
                IWidget::_init(context, "tg::ui::ContainerWidget", parent);
                _setMouseHover(true);
                _setMousePress(true);
            }

            ContainerWidget::ContainerWidget()
            {}

            ContainerWidget::~ContainerWidget()
            {}

            std::shared_ptr<ContainerWidget> ContainerWidget::create(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<IWidget>& parent)
            {
                auto out = std::shared_ptr<ContainerWidget>(new ContainerWidget);
                out->_init(context, parent);
                return out;
            }

            void ContainerWidget::setGeometry(const Box2I& value)
            {
                IWidget::setGeometry(value);
                if (!_children.empty())
                {
                    _children.front()->setGeometry(value);
                }
            }

            void ContainerWidget::sizeHintEvent(const SizeHintEvent& value)
            {
                IWidget::sizeHintEvent(value);
                if (!_children.empty())
                {
                    _sizeHint = _children.front()->getSizeHint();
                }
            }
        }

        struct IMenuPopup::Private
        {
            MenuPopupStyle popupStyle = MenuPopupStyle::Menu;
            ColorRole popupRole = ColorRole::Window;
            Box2I buttonGeometry;
            bool open = false;
            std::function<void(void)> closeCallback;
            std::shared_ptr<IWidget> widget;
            std::shared_ptr<ScrollWidget> scrollWidget;
            std::shared_ptr<ContainerWidget> containerWidget;

            struct SizeData
            {
                bool sizeInit = true;
                int shadow = 0;
            };
            SizeData size;
        };

        void IMenuPopup::_init(
            const std::shared_ptr<Context>& context,
            const std::string& objectName,
            const std::shared_ptr<IWidget>& parent)
        {
            IPopup::_init(context, objectName, parent);
            TG_P();

            p.scrollWidget = ScrollWidget::create(
                context,
                ScrollType::Menu);
            
            p.containerWidget = ContainerWidget::create(context, shared_from_this());
            p.scrollWidget->setParent(p.containerWidget);
        }

        IMenuPopup::IMenuPopup() :
            _p(new Private)
        {}

        IMenuPopup::~IMenuPopup()
        {}

        void IMenuPopup::open(
            const std::shared_ptr<IWindow>& window,
            const Box2I& buttonGeometry)
        {
            TG_P();
            p.buttonGeometry = buttonGeometry;
            p.open = true;
            setParent(window);
            takeKeyFocus();
        }

        bool IMenuPopup::isOpen() const
        {
            return _p->open;
        }

        void IMenuPopup::close()
        {
            TG_P();
            p.open = false;
            setParent(nullptr);
            if (p.closeCallback)
            {
                p.closeCallback();
            }
        }

        void IMenuPopup::setCloseCallback(const std::function<void(void)>& value)
        {
            _p->closeCallback = value;
        }

        void IMenuPopup::setPopupStyle(MenuPopupStyle value)
        {
            TG_P();
            p.popupStyle = value;
        }

        void IMenuPopup::setPopupRole(ColorRole value)
        {
            TG_P();
            if (value == p.popupRole)
                return;
            p.popupRole = value;
            _updates |= Update::Draw;
        }

        void IMenuPopup::setWidget(const std::shared_ptr<IWidget>& value)
        {
            TG_P();
            p.widget = value;
            p.scrollWidget->setWidget(p.widget);
        }

        void IMenuPopup::setGeometry(const Box2I& value)
        {
            IPopup::setGeometry(value);
            TG_P();
            Size2I sizeHint = p.containerWidget->getSizeHint();
            std::list<Box2I> boxes;
            switch (p.popupStyle)
            {
            case MenuPopupStyle::Menu:
                boxes.push_back(Box2I(
                    p.buttonGeometry.min.x,
                    p.buttonGeometry.max.y + 1,
                    std::max(sizeHint.w, p.buttonGeometry.w()),
                    sizeHint.h));
                boxes.push_back(Box2I(
                    p.buttonGeometry.max.x + 1 - sizeHint.w,
                    p.buttonGeometry.max.y + 1,
                    std::max(sizeHint.w, p.buttonGeometry.w()),
                    sizeHint.h));
                boxes.push_back(Box2I(
                    p.buttonGeometry.min.x,
                    p.buttonGeometry.min.y - sizeHint.h,
                    std::max(sizeHint.w, p.buttonGeometry.w()),
                    sizeHint.h));
                boxes.push_back(Box2I(
                    p.buttonGeometry.max.x + 1 - sizeHint.w,
                    p.buttonGeometry.min.y - sizeHint.h,
                    std::max(sizeHint.w, p.buttonGeometry.w()),
                    sizeHint.h));
                break;
            case MenuPopupStyle::SubMenu:
                boxes.push_back(Box2I(
                    p.buttonGeometry.max.x,
                    p.buttonGeometry.min.y,
                    sizeHint.w,
                    sizeHint.h));
                boxes.push_back(Box2I(
                    p.buttonGeometry.min.x - sizeHint.w,
                    p.buttonGeometry.min.y,
                    sizeHint.w,
                    sizeHint.h));
                break;
            default: break;
            }
            struct Intersect
            {
                Box2I original;
                Box2I intersected;
            };
            std::vector<Intersect> intersect;
            for (const auto& box : boxes)
            {
                intersect.push_back({ box, core::intersect(box, value) });
            }
            std::stable_sort(
                intersect.begin(),
                intersect.end(),
                [](const Intersect& a, const Intersect& b)
                {
                    return
                        area(a.intersected.size()) >
                        area(b.intersected.size());
                });
            Box2I g = intersect.front().intersected;
            p.containerWidget->setGeometry(g);
        }

        void IMenuPopup::sizeHintEvent(const SizeHintEvent& event)
        {
            const bool displayScaleChanged = event.displayScale != _displayScale;
            IPopup::sizeHintEvent(event);
            TG_P();

            if (displayScaleChanged || p.size.sizeInit)
            {
                p.size.shadow = event.style->getSizeRole(SizeRole::Shadow, _displayScale);
            }
            p.size.sizeInit = false;
        }

        void IMenuPopup::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IPopup::drawEvent(drawRect, event);
            TG_P();
            const Box2I& g = p.containerWidget->getGeometry();
            if (g.size().isValid())
            {
                const Box2I g2(
                    g.min.x - p.size.shadow,
                    g.min.y,
                    g.w() + p.size.shadow * 2,
                    g.h() + p.size.shadow);
                event.render->drawColorMesh(
                    shadow(g2, p.size.shadow),
                    Color4F(1.F, 1.F, 1.F));

                event.render->drawRect(
                    Box2F(g.x(), g.y(), g.w(), g.h()),
                    event.style->getColorRole(p.popupRole));
            }
        }
    }
}
