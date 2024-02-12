// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IntEdit.h>

#include <tgUI/IncButtons.h>
#include <tgUI/LineEdit.h>
#include <tgUI/RowLayout.h>

#include <tgCore/Format.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct IntEdit::Private
        {
            std::shared_ptr<IntModel> model;
            int digits = 3;
            std::shared_ptr<LineEdit> lineEdit;
            std::shared_ptr<IntIncButtons> incButtons;
            std::shared_ptr<HorizontalLayout> layout;

            std::function<void(int)> callback;

            std::shared_ptr<ValueObserver<int> > valueObserver;
            std::shared_ptr<ValueObserver<RangeI> > rangeObserver;
        };

        void IntEdit::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IntModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::IntEdit", parent);
            TG_P();

            p.model = model;
            if (!p.model)
            {
                p.model = IntModel::create(context);
            }

            p.lineEdit = LineEdit::create(context, shared_from_this());
            p.lineEdit->setFontRole(FontRole::Mono);

            p.incButtons = IntIncButtons::create(context, p.model);

            p.layout = HorizontalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::SpacingTool);
            p.lineEdit->setParent(p.layout);
            p.incButtons->setParent(p.layout);

            p.lineEdit->setTextCallback(
                [this](const std::string& value)
                {
                    _p->model->setValue(std::atoi(value.c_str()));
                    _textUpdate();
                });
            p.lineEdit->setFocusCallback(
                [this](bool value)
                {
                    if (!value)
                    {
                        _textUpdate();
                    }
                });

            p.valueObserver = ValueObserver<int>::create(
                p.model->observeValue(),
                [this](int value)
                {
                    _textUpdate();
                    if (_p->callback)
                    {
                        _p->callback(value);
                    }
                });

            p.rangeObserver = ValueObserver<RangeI>::create(
                p.model->observeRange(),
                [this](const RangeI& value)
                {
                    _p->digits = digits(value.max());
                    _setSizeUpdate();
                    _textUpdate();
                });

            _textUpdate();
        }

        IntEdit::IntEdit() :
            _p(new Private)
        {}

        IntEdit::~IntEdit()
        {}

        std::shared_ptr<IntEdit> IntEdit::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IntModel>& model,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<IntEdit>(new IntEdit);
            out->_init(context, model, parent);
            return out;
        }

        int IntEdit::getValue() const
        {
            return _p->model->getValue();
        }

        void IntEdit::setValue(int value)
        {
            _p->model->setValue(value);
        }

        void IntEdit::setCallback(const std::function<void(int)>& value)
        {
            _p->callback = value;
        }

        const RangeI& IntEdit::getRange() const
        {
            return _p->model->getRange();
        }

        void IntEdit::setRange(const RangeI& value)
        {
            _p->model->setRange(value);
        }

        void IntEdit::setStep(int value)
        {
            _p->model->setStep(value);
        }

        void IntEdit::setLargeStep(int value)
        {
            _p->model->setLargeStep(value);
        }

        const std::shared_ptr<IntModel>& IntEdit::getModel() const
        {
            return _p->model;
        }

        void IntEdit::setFontRole(FontRole value)
        {
            _p->lineEdit->setFontRole(value);
        }

        void IntEdit::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void IntEdit::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->layout->getSizeHint());
        }

        void IntEdit::keyPressEvent(KeyEvent& event)
        {
            TG_P();
            if (isEnabled() && p.model)
            {
                switch (event.key)
                {
                case Key::Down:
                    event.accept = true;
                    p.model->decrementStep();
                    break;
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
                default: break;
                }
            }
        }

        void IntEdit::keyReleaseEvent(KeyEvent& event)
        {
            event.accept = true;
        }

        void IntEdit::_textUpdate()
        {
            TG_P();
            std::string text;
            std::string format;
            if (p.model)
            {
                text = Format("{0}").arg(p.model->getValue());
                int width = p.digits;
                if (p.model->getRange().min() < 0 ||
                    p.model->getRange().max() < 0)
                {
                    ++width;
                }
                format = Format("{0}").arg(0, width);
            }
            p.lineEdit->setText(text);
            p.lineEdit->setFormat(format);
        }
    }
}
