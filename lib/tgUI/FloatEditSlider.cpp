// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/FloatEditSlider.h>

#include <tgUI/FloatEdit.h>
#include <tgUI/FloatSlider.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ToolButton.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct FloatEditSlider::Private
        {
            std::shared_ptr<FloatModel> model;

            std::shared_ptr<FloatEdit> edit;
            std::shared_ptr<FloatSlider> slider;
            std::shared_ptr<ToolButton> resetButton;
            std::shared_ptr<HorizontalLayout> layout;

            std::function<void(float)> callback;

            std::shared_ptr<ValueObserver<float> > valueObserver;
            std::shared_ptr<ValueObserver<bool> > hasDefaultObserver;
        };

        void FloatEditSlider::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<FloatModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::FloatEditSlider", parent);
            TG_P();

            setHStretch(Stretch::Expanding);

            p.model = model;
            if (!p.model)
            {
                p.model = FloatModel::create(context);
            }

            p.edit = FloatEdit::create(context, p.model);

            p.slider = FloatSlider::create(context, p.model);

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

            p.valueObserver = ValueObserver<float>::create(
                p.model->observeValue(),
                [this](float value)
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

        FloatEditSlider::FloatEditSlider() :
            _p(new Private)
        {}

        FloatEditSlider::~FloatEditSlider()
        {}

        std::shared_ptr<FloatEditSlider> FloatEditSlider::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<FloatModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<FloatEditSlider>(new FloatEditSlider);
            out->_init(context, model, parent);
            return out;
        }

        float FloatEditSlider::getValue() const
        {
            return _p->model->getValue();
        }

        void FloatEditSlider::setValue(float value)
        {
            _p->model->setValue(value);
        }

        void FloatEditSlider::setCallback(const std::function<void(float)>& value)
        {
            _p->callback = value;
        }

        const RangeF& FloatEditSlider::getRange() const
        {
            return _p->model->getRange();
        }

        void FloatEditSlider::setRange(const RangeF& value)
        {
            _p->model->setRange(value);
        }

        void FloatEditSlider::setStep(float value)
        {
            _p->model->setStep(value);
        }

        void FloatEditSlider::setLargeStep(float value)
        {
            _p->model->setLargeStep(value);
        }

        void FloatEditSlider::setDefaultValue(float value)
        {
            _p->model->setDefaultValue(value);
        }

        const std::shared_ptr<FloatModel>& FloatEditSlider::getModel() const
        {
            return _p->model;
        }

        void FloatEditSlider::setPrecision(int value)
        {
            _p->edit->setPrecision(value);
        }

        void FloatEditSlider::setFontRole(FontRole value)
        {
            _p->edit->setFontRole(value);
        }

        void FloatEditSlider::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void FloatEditSlider::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->layout->getSizeHint());
        }
    }
}
