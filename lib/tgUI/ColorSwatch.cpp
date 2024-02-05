// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/ColorSwatch.h>

#include <tgUI/ColorPopup.h>
#include <tgUI/DrawUtil.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct ColorSwatch::Private
        {
            Color4F color;
            bool editable = false;
            std::function<void(const Color4F&)> callback;
            SizeRole sizeRole = SizeRole::Swatch;
            std::shared_ptr<ColorPopup> popup;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int size = 0;
                int border = 0;
            };
            SizeData size;
        };

        void ColorSwatch::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::ColorSwatch", parent);
        }

        ColorSwatch::ColorSwatch() :
            _p(new Private)
        {}

        ColorSwatch::~ColorSwatch()
        {}

        std::shared_ptr<ColorSwatch> ColorSwatch::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ColorSwatch>(new ColorSwatch);
            out->_init(context, parent);
            return out;
        }

        const Color4F& ColorSwatch::getColor() const
        {
            return _p->color;
        }

        void ColorSwatch::setColor(const Color4F& value)
        {
            TG_P();
            if (value == p.color)
                return;
            p.color = value;
            _updates |= Update::Draw;
        }

        void ColorSwatch::setEditable(bool value)
        {
            TG_P();
            if (value == p.editable)
                return;
            p.editable = value;
            _setMouseHover(p.editable);
            _setMousePress(p.editable);
        }

        void ColorSwatch::setCallback(const std::function<void(const Color4F&)>& value)
        {
            _p->callback = value;
        }

        void ColorSwatch::setSizeRole(SizeRole value)
        {
            TG_P();
            if (value == p.sizeRole)
                return;
            p.sizeRole = value;
            p.size.init = true;
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        void ColorSwatch::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();
            if (p.size.init || event.displayScale != p.size.displayScale)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.size = event.style->getSizeRole(p.sizeRole, p.size.displayScale);
                p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
            }
            _sizeHint.w = _sizeHint.h = p.size.size;
        }

        void ColorSwatch::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();
            const Box2I& g = _geometry;
            event.render->drawMesh(
                border(g, p.size.border),
                event.style->getColorRole(ColorRole::Border));
            const Box2I g2 = margin(g, -p.size.border);
            event.render->drawRect(
                Box2F(g2.x(), g2.y(), g2.w(), g2.h()),
                p.color);
        }

        void ColorSwatch::mousePressEvent(MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
            TG_P();
            if (p.editable)
            {
                _showPopup();
            }
        }

        void ColorSwatch::_showPopup()
        {
            TG_P();
            if (auto context = _context.lock())
            {
                if (!p.popup)
                {
                    p.popup = ColorPopup::create(context, p.color);
                    p.popup->open(getWindow(), getGeometry());
                    p.popup->setCallback(
                        [this](const Color4F& value)
                        {
                            _p->color = value;
                            _updates |= Update::Draw;
                            if (_p->callback)
                            {
                                _p->callback(value);
                            }
                        });
                    p.popup->setCloseCallback(
                        [this]
                        {
                            _p->popup.reset();
                        });
                }
                else
                {
                    p.popup->close();
                    p.popup.reset();
                }
            }
        }
    }
}
