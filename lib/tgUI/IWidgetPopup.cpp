// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IWidgetPopup.h>

#include <tgUI/DrawUtil.h>
#include <tgUI/IWindow.h>

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
                _setMouseHoverEnabled(true);
                _setMousePressEnabled(true);
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
                const auto& children = getChildren();
                if (!children.empty())
                {
                    children.front()->setGeometry(value);
                }
            }

            void ContainerWidget::sizeHintEvent(const SizeHintEvent& event)
            {
                IWidget::sizeHintEvent(event);
                const auto& children = getChildren();
                if (!children.empty())
                {
                    _setSizeHint(children.front()->getSizeHint());
                }
            }
        }

        struct IWidgetPopup::Private
        {
            ColorRole popupRole = ColorRole::Window;
            Box2I buttonGeometry;
            bool open = false;
            std::function<void(void)> closeCallback;
            std::shared_ptr<IWidget> widget;
            std::shared_ptr<ContainerWidget> containerWidget;

            struct SizeData
            {
                int border = 0;
                int shadow = 0;
            };
            SizeData size;
        };

        void IWidgetPopup::_init(
            const std::shared_ptr<Context>& context,
            const std::string& objectName,
            const std::shared_ptr<IWidget>& parent)
        {
            IPopup::_init(context, objectName, parent);
            TG_P();
            p.containerWidget = ContainerWidget::create(context, shared_from_this());
        }

        IWidgetPopup::IWidgetPopup() :
            _p(new Private)
        {}

        IWidgetPopup::~IWidgetPopup()
        {}

        void IWidgetPopup::open(
            const std::shared_ptr<IWindow>& window,
            const Box2I& buttonGeometry)
        {
            TG_P();
            p.buttonGeometry = buttonGeometry;
            p.open = true;
            setParent(window);
        }

        bool IWidgetPopup::isOpen() const
        {
            return _p->open;
        }

        void IWidgetPopup::close()
        {
            TG_P();
            p.open = false;
            setParent(nullptr);
            if (p.closeCallback)
            {
                p.closeCallback();
            }
        }

        void IWidgetPopup::setCloseCallback(const std::function<void(void)>& value)
        {
            _p->closeCallback = value;
        }

        void IWidgetPopup::setPopupRole(ColorRole value)
        {
            TG_P();
            if (value == p.popupRole)
                return;
            p.popupRole = value;
            _setDrawUpdate();
        }

        void IWidgetPopup::setWidget(const std::shared_ptr<IWidget>& value)
        {
            TG_P();
            if (p.widget)
            {
                p.widget->setParent(nullptr);
            }
            p.widget = value;
            if (p.widget)
            {
                p.widget->setParent(p.containerWidget);
            }
        }

        void IWidgetPopup::setGeometry(const Box2I& value)
        {
            IPopup::setGeometry(value);
            TG_P();
            Size2I sizeHint = p.containerWidget->getSizeHint();
            std::list<Box2I> boxes;
            boxes.push_back(Box2I(
                p.buttonGeometry.min.x,
                p.buttonGeometry.max.y + 1,
                sizeHint.w,
                sizeHint.h));
            boxes.push_back(Box2I(
                p.buttonGeometry.max.x + 1 - sizeHint.w,
                p.buttonGeometry.max.y + 1,
                sizeHint.w,
                sizeHint.h));
            boxes.push_back(Box2I(
                p.buttonGeometry.min.x,
                p.buttonGeometry.min.y - sizeHint.h,
                sizeHint.w,
                sizeHint.h));
            boxes.push_back(Box2I(
                p.buttonGeometry.max.x + 1 - sizeHint.w,
                p.buttonGeometry.min.y - sizeHint.h,
                sizeHint.w,
                sizeHint.h));
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

        void IWidgetPopup::sizeHintEvent(const SizeHintEvent& event)
        {
            IPopup::sizeHintEvent(event);
            TG_P();
            p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
            p.size.shadow = event.style->getSizeRole(SizeRole::Shadow, event.displayScale);
        }

        void IWidgetPopup::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IPopup::drawEvent(drawRect, event);
            TG_P();
            const Box2I g = margin(p.containerWidget->getGeometry(), p.size.border);
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

                event.render->drawMesh(
                    border(g, p.size.border),
                    event.style->getColorRole(ColorRole::Border));

                const Box2I g3 = margin(g, -p.size.border);
                event.render->drawRect(
                    Box2F(g3.x(), g3.y(), g3.w(), g3.h()),
                    event.style->getColorRole(p.popupRole));
            }
        }

        void IWidgetPopup::keyPressEvent(KeyEvent& event)
        {
            if (0 == event.modifiers)
            {
                if (Key::Escape == event.key)
                {
                    event.accept = true;
                    close();
                }
            }
        }

        void IWidgetPopup::keyReleaseEvent(KeyEvent& event)
        {
            event.accept = true;
        }
    }
}
