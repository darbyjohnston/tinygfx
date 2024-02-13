// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IntEditSlider.h>

#include <tgUI/IntEdit.h>
#include <tgUI/IntSlider.h>
#include <tgUI/RowLayout.h>
#include <tgUI/ToolButton.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct IntEditSlider::Private
        {
            std::shared_ptr<IntModel> model;

            std::shared_ptr<IntEdit> edit;
            std::shared_ptr<IntSlider> slider;
            std::shared_ptr<ToolButton> resetButton;
            std::shared_ptr<HorizontalLayout> layout;

            std::function<void(int)> callback;

            std::shared_ptr<ValueObserver<int> > valueObserver;
            std::shared_ptr<ValueObserver<bool> > hasDefaultObserver;
        };

        void IntEditSlider::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IntModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::IntEditSlider", parent);
            TG_P();

            setHStretch(Stretch::Expanding);

            p.model = model;
            if (!p.model)
            {
                p.model = IntModel::create(context);
            }

            p.edit = IntEdit::create(context, p.model);

            p.slider = IntSlider::create(context, p.model);

            p.resetButton = ToolButton::create(context);
            p.resetButton->setIcon("Reset");
            p.resetButton->setTooltip("Reset to the default value");

            p.layout = HorizontalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::SpacingTool);
            p.edit->setParent(p.layout);
            p.slider->setParent(p.layout);
            p.slider->setHStretch(Stretch::Expanding);
            p.resetButton->setParent(p.layout);

            p.resetButton->setClickedCallback(
                [this]
                {
                    _p->model->setDefaultValue();
                });

            p.valueObserver = ValueObserver<int>::create(
                p.model->observeValue(),
                [this](int value)
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

        IntEditSlider::IntEditSlider() :
            _p(new Private)
        {}

        IntEditSlider::~IntEditSlider()
        {}

        std::shared_ptr<IntEditSlider> IntEditSlider::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IntModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<IntEditSlider>(new IntEditSlider);
            out->_init(context, model, parent);
            return out;
        }

        int IntEditSlider::getValue() const
        {
            return _p->model->getValue();
        }

        void IntEditSlider::setValue(int value)
        {
            _p->model->setValue(value);
        }

        void IntEditSlider::setCallback(const std::function<void(int)>& value)
        {
            _p->callback = value;
        }

        const RangeI& IntEditSlider::getRange() const
        {
            return _p->model->getRange();
        }

        void IntEditSlider::setRange(const RangeI& value)
        {
            _p->model->setRange(value);
        }

        void IntEditSlider::setStep(int value)
        {
            _p->model->setStep(value);
        }

        void IntEditSlider::setLargeStep(int value)
        {
            _p->model->setLargeStep(value);
        }

        void IntEditSlider::setDefaultValue(int value)
        {
            _p->model->setDefaultValue(value);
        }

        const std::shared_ptr<IntModel>& IntEditSlider::getModel() const
        {
            return _p->model;
        }

        void IntEditSlider::setFontRole(FontRole value)
        {
            _p->edit->setFontRole(value);
        }

        void IntEditSlider::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void IntEditSlider::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->layout->getSizeHint());
        }
    }
}
