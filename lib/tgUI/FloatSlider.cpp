// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/FloatSlider.h>

#include <tgUI/DrawUtil.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct FloatSlider::Private
        {
            std::shared_ptr<FloatModel> model;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int size = 0;
                int border = 0;
                int handle = 0;
                FontMetrics fontMetrics;
            };
            SizeData size;

            std::function<void(float)> callback;

            std::shared_ptr<ValueObserver<float> > valueObserver;
            std::shared_ptr<ValueObserver<RangeF> > rangeObserver;
        };

        void FloatSlider::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<FloatModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::FloatSlider", parent);
            TG_P();

            setAcceptsKeyFocus(true);
            setHStretch(Stretch::Expanding);
            _setMouseHover(true);
            _setMousePress(true);

            p.model = model;
            if (!p.model)
            {
                p.model = FloatModel::create(context);
            }

            p.valueObserver = ValueObserver<float>::create(
                p.model->observeValue(),
                [this](float value)
                {
                    _updates |= Update::Size;
                    _updates |= Update::Draw;
                    if (_p->callback)
                    {
                        _p->callback(value);
                    }
                });

            p.rangeObserver = ValueObserver<RangeF>::create(
                p.model->observeRange(),
                [this](const RangeF&)
                {
                    _updates |= Update::Size;
                    _updates |= Update::Draw;
                });
        }

        FloatSlider::FloatSlider() :
            _p(new Private)
        {}

        FloatSlider::~FloatSlider()
        {}

        std::shared_ptr<FloatSlider> FloatSlider::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<FloatModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<FloatSlider>(new FloatSlider);
            out->_init(context, model, parent);
            return out;
        }

        float FloatSlider::getValue() const
        {
            return _p->model->getValue();
        }

        void FloatSlider::setValue(float value)
        {
            _p->model->setValue(value);
        }

        void FloatSlider::setCallback(const std::function<void(float)>& value)
        {
            _p->callback = value;
        }

        const RangeF& FloatSlider::getRange() const
        {
            return _p->model->getRange();
        }

        void FloatSlider::setRange(const RangeF& value)
        {
            _p->model->setRange(value);
        }

        void FloatSlider::setStep(float value)
        {
            _p->model->setStep(value);
        }

        void FloatSlider::setLargeStep(float value)
        {
            _p->model->setLargeStep(value);
        }

        void FloatSlider::setDefaultValue(float value)
        {
            _p->model->setDefaultValue(value);
        }

        const std::shared_ptr<FloatModel>& FloatSlider::getModel() const
        {
            return _p->model;
        }

        void FloatSlider::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();
            if (p.size.init || event.displayScale != p.size.displayScale)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.size = event.style->getSizeRole(SizeRole::Slider, p.size.displayScale);
                p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
                p.size.handle = event.style->getSizeRole(SizeRole::Handle, p.size.displayScale);
                auto fontInfo = event.style->getFontRole(FontRole::Label, p.size.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(fontInfo);
            }
            _sizeHint.w =
                p.size.size +
                p.size.border * 6;
            _sizeHint.h =
                p.size.fontMetrics.lineHeight +
                p.size.border * 6;
        }

        void FloatSlider::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();

            const Box2I& g = _geometry;

            if (_keyFocus)
            {
                event.render->drawMesh(
                    border(g, p.size.border * 2),
                    event.style->getColorRole(ColorRole::KeyFocus));
            }
            else
            {
                event.render->drawMesh(
                    border(margin(g, -p.size.border), p.size.border),
                    event.style->getColorRole(ColorRole::Border));
            }

            const Box2I g2 = margin(g, -p.size.border * 2);
            event.render->drawRect(
                Box2F(g2.x(), g2.y(), g2.w(), g2.h()),
                event.style->getColorRole(ColorRole::Base));

            const Box2I g3 = _getSliderGeometry();
            //event.render->drawRect(
            //    Box2F(g3.x(), g3.y(), g3.w(), g3.h()),
            //    Color4F(1.F, 0.F, 0.F, .5F));
            int pos = 0;
            if (p.model)
            {
                pos = _valueToPos(p.model->getValue());
            }
            const Box2I g4(
                pos - p.size.handle / 2,
                g3.y(),
                p.size.handle,
                g3.h());
            event.render->drawRect(
                Box2F(g4.x(), g4.y(), g4.w(), g4.h()),
                event.style->getColorRole(ColorRole::Button));
            if (_mouse.press)
            {
                event.render->drawRect(
                    Box2F(g4.x(), g4.y(), g4.w(), g4.h()),
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (_mouse.inside)
            {
                event.render->drawRect(
                    Box2F(g4.x(), g4.y(), g4.w(), g4.h()),
                    event.style->getColorRole(ColorRole::Hover));
            }
        }

        void FloatSlider::mouseEnterEvent()
        {
            IWidget::mouseEnterEvent();
            _updates |= Update::Draw;
        }

        void FloatSlider::mouseLeaveEvent()
        {
            IWidget::mouseLeaveEvent();
            _updates |= Update::Draw;
        }

        void FloatSlider::mouseMoveEvent(MouseMoveEvent& event)
        {
            IWidget::mouseMoveEvent(event);
            TG_P();
            if (_mouse.press && p.model)
            {
                p.model->setValue(_posToValue(_mouse.pos.x));
            }
        }

        void FloatSlider::mousePressEvent(MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
            TG_P();
            if (p.model)
            {
                p.model->setValue(_posToValue(_mouse.pos.x));
            }
            takeKeyFocus();
            _updates |= Update::Draw;
        }

        void FloatSlider::mouseReleaseEvent(MouseClickEvent& event)
        {
            IWidget::mouseReleaseEvent(event);
            _updates |= Update::Draw;
        }

        void FloatSlider::keyPressEvent(KeyEvent& event)
        {
            TG_P();
            if (isEnabled() && p.model && 0 == event.modifiers)
            {
                switch (event.key)
                {
                case Key::Left:
                case Key::Down:
                    event.accept = true;
                    p.model->decrementStep();
                    break;
                case Key::Right:
                case Key::Up:
                    event.accept = true;
                    p.model->incrementStep();
                    break;
                case Key::PageUp:
                    event.accept = true;
                    p.model->incrementLargeStep();
                    break;
                case Key::PageDown:
                    event.accept = true;
                    p.model->decrementLargeStep();
                    break;
                case Key::End:
                    event.accept = true;
                    p.model->setValue(p.model->getRange().min());
                    break;
                case Key::Home:
                    event.accept = true;
                    p.model->setValue(p.model->getRange().max());
                    break;
                case Key::Escape:
                    if (hasKeyFocus())
                    {
                        event.accept = true;
                        releaseKeyFocus();
                    }
                    break;
                default: break;
                }
            }
        }

        void FloatSlider::keyReleaseEvent(KeyEvent& event)
        {
            event.accept = true;
        }

        Box2I FloatSlider::_getSliderGeometry() const
        {
            TG_P();
            return margin(
                _geometry,
                -(p.size.border * 3 + p.size.handle / 2),
                -(p.size.border * 3),
                -(p.size.border * 3 + p.size.handle / 2),
                -(p.size.border * 3));
        }

        float FloatSlider::_posToValue(int pos) const
        {
            TG_P();
            const Box2I g = _getSliderGeometry();
            const float v = (pos - g.x()) / static_cast<float>(g.w());
            float out = 0.F;
            if (p.model)
            {
                const RangeF& range = p.model->getRange();
                out = range.min() + (range.max() - range.min()) * v;
            }
            return out;
        }

        int FloatSlider::_valueToPos(float value) const
        {
            TG_P();
            const Box2I g = _getSliderGeometry();
            float v = 0.F;
            if (p.model)
            {
                const RangeF& range = p.model->getRange();
                if (range.min() != range.max())
                {
                    v = (value - range.min()) /
                        static_cast<float>(range.max() - range.min());
                }
            }
            return g.x() + g.w() * v;
        }
    }
}
