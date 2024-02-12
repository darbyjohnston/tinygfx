// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/DoubleEditSlider.h>

#include <tgUI/DoubleEdit.h>
#include <tgUI/DoubleSlider.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ToolButton.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct DoubleEditSlider::Private
        {
            std::shared_ptr<DoubleModel> model;

            std::shared_ptr<DoubleEdit> edit;
            std::shared_ptr<DoubleSlider> slider;
            std::shared_ptr<ToolButton> resetButton;
            std::shared_ptr<HorizontalLayout> layout;

            std::function<void(double)> callback;

            std::shared_ptr<ValueObserver<double> > valueObserver;
            std::shared_ptr<ValueObserver<bool> > hasDefaultObserver;
        };

        void DoubleEditSlider::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<DoubleModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::DoubleEditSlider", parent);
            TG_P();

            setHStretch(Stretch::Expanding);

            p.model = model;
            if (!p.model)
            {
                p.model = DoubleModel::create(context);
            }

            p.edit = DoubleEdit::create(context, p.model);

            p.slider = DoubleSlider::create(context, p.model);

            p.resetButton = ToolButton::create(context);
            p.resetButton->setIcon("Reset");
            p.resetButton->setToolTip("Reset to the default value");

            p.layout = HorizontalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::SpacingTool);
            p.edit->setParent(p.layout);
            p.slider->setParent(p.layout);
            p.slider->setHStretch(ui::Stretch::Expanding);
            p.resetButton->setParent(p.layout);

            p.resetButton->setClickedCallback(
                [this]
                {
                    _p->model->setDefaultValue();
                });

            p.valueObserver = ValueObserver<double>::create(
                p.model->observeValue(),
                [this](double value)
                {
                    _p->resetButton->setEnabled(value != _p->model->getDefaultValue());
                    if (_p->callback)
                    {
                        _p->callback(value);
                    }
                });

            p.hasDefaultObserver = ValueObserver<bool>::create(
                p.model->observeHasDefaultValue(),
                [this](bool value)
                {
                    _p->resetButton->setVisible(value);
                });
        }

        DoubleEditSlider::DoubleEditSlider() :
            _p(new Private)
        {}

        DoubleEditSlider::~DoubleEditSlider()
        {}

        std::shared_ptr<DoubleEditSlider> DoubleEditSlider::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<DoubleModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<DoubleEditSlider>(new DoubleEditSlider);
            out->_init(context, model, parent);
            return out;
        }

        double DoubleEditSlider::getValue() const
        {
            return _p->model->getValue();
        }

        void DoubleEditSlider::setValue(double value)
        {
            _p->model->setValue(value);
        }

        void DoubleEditSlider::setCallback(const std::function<void(double)>& value)
        {
            _p->callback = value;
        }

        const RangeD& DoubleEditSlider::getRange() const
        {
            return _p->model->getRange();
        }

        void DoubleEditSlider::setRange(const RangeD& value)
        {
            _p->model->setRange(value);
        }

        void DoubleEditSlider::setStep(double value)
        {
            _p->model->setStep(value);
        }

        void DoubleEditSlider::setLargeStep(double value)
        {
            _p->model->setLargeStep(value);
        }

        void DoubleEditSlider::setDefaultValue(double value)
        {
            _p->model->setDefaultValue(value);
        }

        const std::shared_ptr<DoubleModel>& DoubleEditSlider::getModel() const
        {
            return _p->model;
        }

        void DoubleEditSlider::setPrecision(int value)
        {
            _p->edit->setPrecision(value);
        }

        void DoubleEditSlider::setFontRole(FontRole value)
        {
            _p->edit->setFontRole(value);
        }

        void DoubleEditSlider::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void DoubleEditSlider::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->layout->getSizeHint());
        }
    }
}
