// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IntSlider.h>

#include <tgUI/DrawUtil.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct IntSlider::Private
        {
            std::shared_ptr<IntModel> model;

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

            std::function<void(int)> callback;

            std::shared_ptr<ValueObserver<int> > valueObserver;
            std::shared_ptr<ValueObserver<RangeI> > rangeObserver;
        };

        void IntSlider::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IntModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::IntSlider", parent);
            TG_P();

            setAcceptsKeyFocus(true);
            setHStretch(Stretch::Expanding);
            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);

            p.model = model;
            if (!p.model)
            {
                p.model = IntModel::create(context);
            }

            p.valueObserver = ValueObserver<int>::create(
                p.model->observeValue(),
                [this](int value)
                {
                    _setSizeUpdate();
                    _setDrawUpdate();
                    if (_p->callback)
                    {
                        _p->callback(value);
                    }
                });

            p.rangeObserver = ValueObserver<RangeI>::create(
                p.model->observeRange(),
                [this](const RangeI&)
                {
                    _setSizeUpdate();
                    _setDrawUpdate();
                });
        }

        IntSlider::IntSlider() :
            _p(new Private)
        {}

        IntSlider::~IntSlider()
        {}

        std::shared_ptr<IntSlider> IntSlider::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IntModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<IntSlider>(new IntSlider);
            out->_init(context, model, parent);
            return out;
        }

        int IntSlider::getValue() const
        {
            return _p->model->getValue();
        }

        void IntSlider::setValue(int value)
        {
            _p->model->setValue(value);
        }

        void IntSlider::setCallback(const std::function<void(int)>& value)
        {
            _p->callback = value;
        }

        const RangeI& IntSlider::getRange() const
        {
            return _p->model->getRange();
        }

        void IntSlider::setRange(const RangeI& value)
        {
            _p->model->setRange(value);
        }

        int IntSlider::getStep() const
        {
            return _p->model->getStep();
        }

        void IntSlider::setStep(int value)
        {
            _p->model->setStep(value);
        }

        int IntSlider::getLargeStep() const
        {
            return _p->model->getLargeStep();
        }

        void IntSlider::setLargeStep(int value)
        {
            _p->model->setLargeStep(value);
        }

        int IntSlider::getDefaultValue() const
        {
            return _p->model->getDefaultValue();
        }

        void IntSlider::setDefaultValue(int value)
        {
            _p->model->setDefaultValue(value);
        }

        const std::shared_ptr<IntModel>& IntSlider::getModel() const
        {
            return _p->model;
        }

        void IntSlider::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();
            if (p.size.init || event.displayScale || p.size.displayScale)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.size = event.style->getSizeRole(SizeRole::Slider, p.size.displayScale);
                p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
                p.size.handle = event.style->getSizeRole(SizeRole::Handle, p.size.displayScale);
                auto fontInfo = event.style->getFontRole(FontRole::Label, p.size.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(fontInfo);
            }
            _setSizeHint(Size2I(
                p.size.size +
                p.size.border * 6,
                p.size.fontMetrics.lineHeight +
                p.size.border * 6));
        }

        void IntSlider::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();

            const Box2I& g = getGeometry();

            if (hasKeyFocus())
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
            if (_isMousePressed())
            {
                event.render->drawRect(
                    Box2F(g4.x(), g4.y(), g4.w(), g4.h()),
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (_isMouseInside())
            {
                event.render->drawRect(
                    Box2F(g4.x(), g4.y(), g4.w(), g4.h()),
                    event.style->getColorRole(ColorRole::Hover));
            }
        }

        void IntSlider::mouseEnterEvent()
        {
            IWidget::mouseEnterEvent();
            _setDrawUpdate();
        }

        void IntSlider::mouseLeaveEvent()
        {
            IWidget::mouseLeaveEvent();
            _setDrawUpdate();
        }

        void IntSlider::mouseMoveEvent(MouseMoveEvent& event)
        {
            IWidget::mouseMoveEvent(event);
            TG_P();
            if (_isMousePressed() && p.model)
            {
                p.model->setValue(_posToValue(_getMousePos().x));
            }
        }

        void IntSlider::mousePressEvent(MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
            TG_P();
            if (p.model)
            {
                p.model->setValue(_posToValue(_getMousePos().x));
            }
            takeKeyFocus();
            _setDrawUpdate();
        }

        void IntSlider::mouseReleaseEvent(MouseClickEvent& event)
        {
            IWidget::mouseReleaseEvent(event);
            _setDrawUpdate();
        }

        void IntSlider::keyPressEvent(KeyEvent& event)
        {
            TG_P();
            if (isEnabled() && p.model)
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

        void IntSlider::keyReleaseEvent(KeyEvent& event)
        {
            event.accept = true;
        }

        Box2I IntSlider::_getSliderGeometry() const
        {
            TG_P();
            return margin(
                getGeometry(),
                -(p.size.border * 3 + p.size.handle / 2),
                -(p.size.border * 3),
                -(p.size.border * 3 + p.size.handle / 2),
                -(p.size.border * 3));
        }

        int IntSlider::_posToValue(int pos) const
        {
            TG_P();
            const Box2I g = _getSliderGeometry();
            const RangeI range = p.model ? p.model->getRange() : RangeI();
            const float inc = g.w() /
                static_cast<float>(range.max() - range.min());
            const float v = (pos + inc / 2 - g.x()) /
                static_cast<float>(g.w());
            const int out = range.min() +
                (range.max() - range.min()) * v;
            return out;
        }

        int IntSlider::_valueToPos(int value) const
        {
            TG_P();
            const Box2I g = _getSliderGeometry();
            const RangeI range = p.model ? p.model->getRange() : RangeI();
            float v = 0.F;
            if (range.min() != range.max())
            {
                v = (value - range.min()) /
                    static_cast<float>(range.max() - range.min());
            }
            const int out = g.x() + g.w() * v;
            return out;
        }
    }
}
