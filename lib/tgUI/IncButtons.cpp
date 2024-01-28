// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IncButtons.h>

#include <tgUI/DoubleModel.h>
#include <tgUI/FloatModel.h>
#include <tgUI/IntModel.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct IncButton::Private
        {
            struct SizeData
            {
                int margin = 0;
            };
            SizeData size;
        };

        void IncButton::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IButton::_init(context, "tg::ui::IncButton", parent);
            setButtonRole(ColorRole::None);
            setRepeatClick(true);
        }

        IncButton::IncButton() :
            _p(new Private)
        {}

        IncButton::~IncButton()
        {}

        std::shared_ptr<IncButton> IncButton::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<IncButton>(new IncButton);
            out->_init(context, parent);
            return out;
        }

        void IncButton::sizeHintEvent(const SizeHintEvent& event)
        {
            IButton::sizeHintEvent(event);
            TG_P();

            //p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, _displayScale);

            _sizeHint = Size2I();
            if (_iconImage)
            {
                _sizeHint.w = _iconImage->getWidth();
                _sizeHint.h = _iconImage->getHeight();
            }
            _sizeHint.w += p.size.margin * 2;
            _sizeHint.h += p.size.margin * 2;
        }

        void IncButton::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IButton::drawEvent(drawRect, event);
            TG_P();

            const Box2I& g = _geometry;

            const ColorRole colorRole = _checked ?
                ColorRole::Checked :
                _buttonRole;
            if (colorRole != ColorRole::None)
            {
                event.render->drawRect(
                    Box2F(g.x(), g.y(), g.w(), g.h()),
                    event.style->getColorRole(colorRole));
            }

            if (_mouse.press && contains(_geometry, _mouse.pos))
            {
                event.render->drawRect(
                    Box2F(g.x(), g.y(), g.w(), g.h()),
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (_mouse.inside)
            {
                event.render->drawRect(
                    Box2F(g.x(), g.y(), g.w(), g.h()),
                    event.style->getColorRole(ColorRole::Hover));
            }

            int x = g.x() + p.size.margin;
            if (_iconImage)
            {
                const auto iconSize = _iconImage->getSize();
                event.render->drawImage(
                  _iconImage,
                  Box2F(
                      x,
                      g.y() + g.h() / 2 - iconSize.h / 2,
                      iconSize.w,
                      iconSize.h));
            }
        }

        void IncButtons::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::IncButtons", parent);
            _incButton = IncButton::create(context, shared_from_this());
            _incButton->setIcon("Increment");
            _incButton->setVAlign(VAlign::Top);
            _decButton = IncButton::create(context, shared_from_this());
            _decButton->setIcon("Decrement");
            _decButton->setVAlign(VAlign::Bottom);
        }

        IncButtons::IncButtons()
        {}

        IncButtons::~IncButtons()
        {}

        std::shared_ptr<IncButtons> IncButtons::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<IncButtons>(new IncButtons);
            out->_init(context, parent);
            return out;
        }

        void IncButtons::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _incButton->setGeometry(Box2I(
                value.min.x,
                value.min.y,
                value.w(),
                value.h() / 2));
            _decButton->setGeometry(Box2I(
                value.min.x,
                value.max.y - value.h() / 2,
                value.w(),
                value.h() / 2));
        }

        void IncButtons::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            const Size2I incSizeHint = _incButton->getSizeHint();
            const Size2I decSizeHint = _decButton->getSizeHint();
            _sizeHint.w = std::max(incSizeHint.w, decSizeHint.w);
            _sizeHint.h = incSizeHint.h + decSizeHint.h;
        }

        void IncButtons::setIncCallback(const std::function<void(void)>& value)
        {
            _incButton->setClickedCallback(value);
        }

        void IncButtons::setDecCallback(const std::function<void(void)>& value)
        {
            _decButton->setClickedCallback(value);
        }

        struct IntIncButtons::Private
        {
            std::shared_ptr<IntModel> model;
            std::shared_ptr<ValueObserver<int> > valueObserver;
            std::shared_ptr<ValueObserver<RangeI> > rangeObserver;
        };

        void IntIncButtons::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IntModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            IncButtons::_init(context, parent);
            TG_P();
            setObjectName("tg::ui::IntIncButtons");

            p.model = model;

            _modelUpdate();

            _incButton->setClickedCallback(
                [this]
                {
                    _p->model->incrementStep();
                });

            _decButton->setClickedCallback(
                [this]
                {
                    _p->model->decrementStep();
                });

            p.valueObserver = ValueObserver<int>::create(
                p.model->observeValue(),
                [this](int)
                {
                    _modelUpdate();
                });

            p.rangeObserver = ValueObserver<RangeI>::create(
                p.model->observeRange(),
                [this](const RangeI&)
                {
                    _modelUpdate();
                });
        }

        IntIncButtons::IntIncButtons() :
            _p(new Private)
        {}

        IntIncButtons::~IntIncButtons()
        {}

        std::shared_ptr<IntIncButtons> IntIncButtons::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IntModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<IntIncButtons>(new IntIncButtons);
            out->_init(context, model, parent);
            return out;
        }

        const std::shared_ptr<IntModel>& IntIncButtons::getModel() const
        {
            return _p->model;
        }

        void IntIncButtons::_modelUpdate()
        {
            TG_P();
            const int value = p.model->getValue();
            const RangeI& range = p.model->getRange();
            _incButton->setEnabled(value < range.max());
            _decButton->setEnabled(value > range.min());
        }

        struct FloatIncButtons::Private
        {
            std::shared_ptr<FloatModel> model;
            std::shared_ptr<ValueObserver<float> > valueObserver;
            std::shared_ptr<ValueObserver<RangeF> > rangeObserver;
        };

        void FloatIncButtons::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<FloatModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            IncButtons::_init(context, parent);
            TG_P();
            setObjectName("tg::ui::FloatIncButtons");

            p.model = model;

            _modelUpdate();

            _incButton->setClickedCallback(
                [this]
                {
                    _p->model->incrementStep();
                });

            _decButton->setClickedCallback(
                [this]
                {
                    _p->model->decrementStep();
                });

            p.valueObserver = ValueObserver<float>::create(
                p.model->observeValue(),
                [this](float)
                {
                    _modelUpdate();
                });

            p.rangeObserver = ValueObserver<RangeF>::create(
                p.model->observeRange(),
                [this](const RangeF&)
                {
                    _modelUpdate();
                });
        }

        FloatIncButtons::FloatIncButtons() :
            _p(new Private)
        {}

        FloatIncButtons::~FloatIncButtons()
        {}

        std::shared_ptr<FloatIncButtons> FloatIncButtons::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<FloatModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<FloatIncButtons>(new FloatIncButtons);
            out->_init(context, model, parent);
            return out;
        }

        const std::shared_ptr<FloatModel>& FloatIncButtons::getModel() const
        {
            return _p->model;
        }

        void FloatIncButtons::_modelUpdate()
        {
            TG_P();
            const float value = p.model->getValue();
            const RangeF& range = p.model->getRange();
            _incButton->setEnabled(value < range.max());
            _decButton->setEnabled(value > range.min());
        }

        struct DoubleIncButtons::Private
        {
            std::shared_ptr<DoubleModel> model;
            std::shared_ptr<ValueObserver<double> > valueObserver;
            std::shared_ptr<ValueObserver<RangeD> > rangeObserver;
        };

        void DoubleIncButtons::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<DoubleModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            IncButtons::_init(context, parent);
            TG_P();
            setObjectName("tg::ui::DoubleIncButtons");

            p.model = model;

            _modelUpdate();

            _incButton->setClickedCallback(
                [this]
                {
                    _p->model->incrementStep();
                });

            _decButton->setClickedCallback(
                [this]
                {
                    _p->model->decrementStep();
                });

            p.valueObserver = ValueObserver<double>::create(
                p.model->observeValue(),
                [this](double)
                {
                    _modelUpdate();
                });

            p.rangeObserver = ValueObserver<RangeD>::create(
                p.model->observeRange(),
                [this](const RangeD&)
                {
                    _modelUpdate();
                });
        }

        DoubleIncButtons::DoubleIncButtons() :
            _p(new Private)
        {}

        DoubleIncButtons::~DoubleIncButtons()
        {}

        std::shared_ptr<DoubleIncButtons> DoubleIncButtons::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<DoubleModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<DoubleIncButtons>(new DoubleIncButtons);
            out->_init(context, model, parent);
            return out;
        }

        const std::shared_ptr<DoubleModel>& DoubleIncButtons::getModel() const
        {
            return _p->model;
        }

        void DoubleIncButtons::_modelUpdate()
        {
            TG_P();
            const double value = p.model->getValue();
            const RangeD& range = p.model->getRange();
            _incButton->setEnabled(value < range.max());
            _decButton->setEnabled(value > range.min());
        }
    }
}
