// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/MDIWidget.h>

#include <tgUI/Divider.h>
#include <tgUI/DrawUtil.h>
#include <tgUI/Label.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ToolButton.h>

#include <tgCore/Error.h>
#include <tgCore/String.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        TG_ENUM_IMPL(
            MDIResize,
            "North",
            "NorthEast",
            "East",
            "SouthEast",
            "South",
            "SouthWest",
            "West",
            "NorthWest");

        struct MDIWidget::Private
        {
            std::shared_ptr<Label> titleLabel;
            std::shared_ptr<ToolButton> closeButton;
            std::shared_ptr<IWidget> widget;
            std::shared_ptr<VerticalLayout> widgetLayout;
            std::shared_ptr<VerticalLayout> layout;
            std::function<void(bool)> pressCallback;
            std::function<void(const V2I&)> moveCallback;
            std::function<void(MDIResize, const V2I&)> resizeCallback;

            struct SizeData
            {
                bool sizeInit = true;
                int border = 0;
                int handle = 0;
                int shadow = 0;

                Box2I insideGeometry;
            };
            SizeData size;

            struct MouseData
            {
                MDIResize resize = MDIResize::None;
                std::map<MDIResize, Box2I> resizeBoxes;
            };
            MouseData mouse;
        };

        void MDIWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::string& title,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::MDIWidget", parent);
            TG_P();

            _setMouseHover(true);
            _setMousePress(true);

            p.titleLabel = Label::create(context);
            p.titleLabel->setText(title);
            p.titleLabel->setMarginRole(SizeRole::MarginSmall);
            p.titleLabel->setHStretch(Stretch::Expanding);

            p.closeButton = ToolButton::create(context);
            p.closeButton->setIcon("Close");
            p.closeButton->setToolTip("Close the window");

            p.layout = VerticalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::None);
            auto hLayout = HorizontalLayout::create(context, p.layout);
            hLayout->setSpacingRole(SizeRole::None);
            hLayout->setBackgroundRole(ColorRole::Button);
            p.titleLabel->setParent(hLayout);
            p.closeButton->setParent(hLayout);
            Divider::create(context, Orientation::Vertical, p.layout);
            p.widgetLayout = VerticalLayout::create(context, p.layout);
            p.widgetLayout->setMarginRole(SizeRole::MarginInside);
            p.widgetLayout->setVStretch(Stretch::Expanding);

            p.closeButton->setClickedCallback(
                [this]
                {
                    setParent(nullptr);
                });
        }

        MDIWidget::MDIWidget() :
            _p(new Private)
        {}

        MDIWidget::~MDIWidget()
        {}

        std::shared_ptr<MDIWidget> MDIWidget::create(
            const std::shared_ptr<Context>& context,
            const std::string& title,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<MDIWidget>(new MDIWidget);
            out->_init(context, title, parent);
            return out;
        }

        void MDIWidget::setTitle(const std::string& value)
        {
            _p->titleLabel->setText(value);
        }

        void MDIWidget::setWidget(const std::shared_ptr<IWidget>& value)
        {
            TG_P();
            if (p.widget)
            {
                p.widget->setParent(nullptr);
            }
            p.widget = value;
            if (p.widget)
            {
                p.widget->setParent(p.widgetLayout);
            }
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        void MDIWidget::setPressCallback(const std::function<void(bool)>& value)
        {
            _p->pressCallback = value;
        }

        void MDIWidget::setMoveCallback(const std::function<void(const V2I&)>& value)
        {
            _p->moveCallback = value;
        }

        void MDIWidget::setResizeCallback(const std::function<void(MDIResize, const V2I&)>& value)
        {
            _p->resizeCallback = value;
        }

        const Box2I& MDIWidget::getInsideGeometry() const
        {
            return _p->size.insideGeometry;
        }

        void MDIWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            TG_P();
            const int margin = std::max(p.size.handle, p.size.shadow);
            const Box2I g = core::margin(
                value,
                -(margin + p.size.border),
                -(p.size.handle + p.size.border),
                -(margin + p.size.border),
                -(margin + p.size.border));
            p.size.insideGeometry = g;
            p.layout->setGeometry(g);
            p.mouse.resizeBoxes.clear();
            p.mouse.resizeBoxes[MDIResize::North] = Box2I(
                g.min.x + p.size.handle,
                g.min.y - p.size.handle,
                g.w() - p.size.handle * 2,
                p.size.handle);
            p.mouse.resizeBoxes[MDIResize::NorthEast] = Box2I(
                g.max.x - p.size.handle,
                g.min.y - p.size.handle,
                p.size.handle * 2,
                p.size.handle * 2);
            p.mouse.resizeBoxes[MDIResize::East] = Box2I(
                g.max.x,
                g.min.y + p.size.handle,
                p.size.handle,
                g.h() - p.size.handle * 2);
            p.mouse.resizeBoxes[MDIResize::SouthEast] = Box2I(
                g.max.x - p.size.handle,
                g.max.y - p.size.handle,
                p.size.handle * 2,
                p.size.handle * 2);
            p.mouse.resizeBoxes[MDIResize::South] = Box2I(
                g.min.x + p.size.handle,
                g.max.y,
                g.w() - p.size.handle * 2,
                p.size.handle);
            p.mouse.resizeBoxes[MDIResize::SouthWest] = Box2I(
                g.min.x - p.size.handle,
                g.max.y - p.size.handle,
                p.size.handle * 2,
                p.size.handle * 2);
            p.mouse.resizeBoxes[MDIResize::West] = Box2I(
                g.min.x - p.size.handle,
                g.min.y + p.size.handle,
                p.size.handle,
                g.h() - p.size.handle * 2);
            p.mouse.resizeBoxes[MDIResize::NorthWest] = Box2I(
                g.min.x - p.size.handle,
                g.min.y - p.size.handle,
                p.size.handle * 2,
                p.size.handle * 2);
        }

        void MDIWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            const bool displayScaleChanged = event.displayScale != _displayScale;
            IWidget::sizeHintEvent(event);
            TG_P();

            if (displayScaleChanged || p.size.sizeInit)
            {
                p.size.border = event.style->getSizeRole(SizeRole::Border, _displayScale);
                p.size.handle = event.style->getSizeRole(SizeRole::Handle, _displayScale);
                p.size.shadow = event.style->getSizeRole(SizeRole::Shadow, _displayScale);
            }
            p.size.sizeInit = false;

            const int margin = std::max(p.size.handle, p.size.shadow);
            _sizeHint = p.layout->getSizeHint() + p.size.border * 2;
            _sizeHint.w += margin * 2;
            _sizeHint.h += p.size.handle + margin;
        }

        void MDIWidget::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();
            const Box2I& g = _geometry;
            const int margin = std::max(p.size.handle, p.size.shadow);
            const Box2I g2 = core::margin(g, -margin, -p.size.handle, -margin, -margin);
            event.render->drawColorMesh(
                shadow(core::margin(g2, p.size.shadow, 0, p.size.shadow, p.size.shadow), p.size.shadow),
                Color4F(1.F, 1.F, 1.F));
            if (p.mouse.resize != MDIResize::None)
            {
                const auto i = p.mouse.resizeBoxes.find(p.mouse.resize);
                if (i != p.mouse.resizeBoxes.end())
                {
                    const Box2I g3 = i->second;
                    event.render->drawRect(
                        Box2F(g3.x(), g3.y(), g3.w(), g3.h()),
                        event.style->getColorRole(ColorRole::Checked));
                }
            }
            event.render->drawMesh(
                border(g2, p.size.border),
                event.style->getColorRole(ColorRole::Border));
            const Box2I g4 = core::margin(g2, -p.size.border);
            event.render->drawRect(
                Box2F(g4.x(), g4.y(), g4.w(), g4.h()),
                event.style->getColorRole(ColorRole::Window));
        }

        void MDIWidget::mouseLeaveEvent()
        {
            IWidget::mouseLeaveEvent();
            TG_P();
            if (p.mouse.resize != MDIResize::None)
            {
                p.mouse.resize = MDIResize::None;
                _updates |= Update::Draw;
            }
        }

        void MDIWidget::mouseMoveEvent(MouseMoveEvent& event)
        {
            IWidget::mouseMoveEvent(event);
            TG_P();
            if (!_mouse.press)
            {
                MDIResize resize = MDIResize::None;
                for (const auto& box : p.mouse.resizeBoxes)
                {
                    if (contains(box.second, event.pos))
                    {
                        resize = box.first;
                        break;
                    }
                }
                if (resize != p.mouse.resize)
                {
                    p.mouse.resize = resize;
                    _updates |= Update::Draw;
                }
            }
            else
            {
                if (p.mouse.resize != MDIResize::None)
                {
                    if (p.resizeCallback)
                    {
                        p.resizeCallback(p.mouse.resize, event.pos - _mouse.pressPos);
                    }
                }
                else if (p.moveCallback)
                {
                    p.moveCallback(event.pos - _mouse.pressPos);
                }
            }
        }

        void MDIWidget::mousePressEvent(MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
            TG_P();
            if (p.pressCallback)
            {
                p.pressCallback(true);
            }
        }

        void MDIWidget::mouseReleaseEvent(MouseClickEvent& event)
        {
            IWidget::mouseReleaseEvent(event);
            TG_P();
            if (p.pressCallback)
            {
                p.pressCallback(false);
            }
        }
    }
}
