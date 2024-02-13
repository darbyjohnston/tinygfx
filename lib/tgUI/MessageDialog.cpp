// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/MessageDialog.h>

#include <tgUI/Divider.h>
#include <tgUI/Label.h>
#include <tgUI/PushButton.h>
#include <tgUI/RowLayout.h>
#include <tgUI/Spacer.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        namespace
        {
            class MessageWidget : public IWidget
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    const std::string&,
                    const std::shared_ptr<IWidget>& parent);

                MessageWidget();

            public:
                virtual ~MessageWidget();

                static std::shared_ptr<MessageWidget> create(
                    const std::shared_ptr<Context>&,
                    const std::string&,
                    const std::shared_ptr<IWidget>& parent = nullptr);

                void setCallback(const std::function<void(bool)>&);

                void setGeometry(const Box2I&) override;
                void sizeHintEvent(const SizeHintEvent&) override;

            private:
                std::shared_ptr<Label> _titleLabel;
                std::shared_ptr<Label> _label;
                std::shared_ptr<PushButton> _okButton;
                std::shared_ptr<PushButton> _cancelButton;
                std::shared_ptr<VerticalLayout> _layout;
                std::function<void(bool)> _callback;
            };

            void MessageWidget::_init(
                const std::shared_ptr<Context>& context,
                const std::string& text,
                const std::shared_ptr<IWidget>& parent)
            {
                IWidget::_init(context, "tg::ui::MessageWidget", parent);

                _titleLabel = Label::create(context, "Message");
                _titleLabel->setMarginRole(SizeRole::MarginSmall);
                _titleLabel->setBackgroundRole(ColorRole::Button);

                _label = Label::create(context, text);
                _label->setMarginRole(SizeRole::MarginLarge);

                _okButton = PushButton::create(context, "OK");
                _cancelButton = PushButton::create(context, "Cancel");

                _layout = VerticalLayout::create(context, shared_from_this());
                _layout->setSpacingRole(SizeRole::None);
                _titleLabel->setParent(_layout);
                Divider::create(context, Orientation::Vertical, _layout);
                auto vLayout = VerticalLayout::create(context, _layout);
                vLayout->setMarginRole(SizeRole::MarginSmall);
                vLayout->setSpacingRole(SizeRole::None);
                _label->setParent(vLayout);
                auto hLayout = HorizontalLayout::create(context, vLayout);
                hLayout->setSpacingRole(SizeRole::None);
                _cancelButton->setParent(hLayout);
                auto spacer = Spacer::create(context, Orientation::Horizontal, hLayout);
                spacer->setHStretch(Stretch::Expanding);
                _okButton->setParent(hLayout);

                _okButton->setClickedCallback(
                    [this]
                    {
                        if (_callback)
                        {
                            _callback(true);
                        }
                    });

                _cancelButton->setClickedCallback(
                    [this]
                    {
                        if (_callback)
                        {
                            _callback(false);
                        }
                    });
            }

            MessageWidget::MessageWidget()
            {}

            MessageWidget::~MessageWidget()
            {}

            std::shared_ptr<MessageWidget> MessageWidget::create(
                const std::shared_ptr<Context>& context,
                const std::string& text,
                const std::shared_ptr<IWidget>& parent)
            {
                auto out = std::shared_ptr<MessageWidget>(new MessageWidget);
                out->_init(context, text, parent);
                return out;
            }

            void MessageWidget::setCallback(const std::function<void(bool)>& value)
            {
                _callback = value;
            }

            void MessageWidget::setGeometry(const Box2I& value)
            {
                IWidget::setGeometry(value);
                _layout->setGeometry(value);
            }

            void MessageWidget::sizeHintEvent(const SizeHintEvent& event)
            {
                IWidget::sizeHintEvent(event);
                _setSizeHint(_layout->getSizeHint());
            }
        }

        struct MessageDialog::Private
        {
            std::shared_ptr<MessageWidget> widget;

            std::function<void(bool)> callback;
        };

        void MessageDialog::_init(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent)
        {
            IDialog::_init(context, "tl::ui::MessageDialog", parent);
            TG_P();

            p.widget = MessageWidget::create(context, text, shared_from_this());

            p.widget->setCallback(
                [this](bool value)
                {
                    if (_p->callback)
                    {
                        _p->callback(value);
                    }
                });
        }

        MessageDialog::MessageDialog() :
            _p(new Private)
        {}

        MessageDialog::~MessageDialog()
        {}

        std::shared_ptr<MessageDialog> MessageDialog::create(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<MessageDialog>(new MessageDialog);
            out->_init(context, text, parent);
            return out;
        }

        void MessageDialog::setCallback(const std::function<void(bool)>& value)
        {
            _p->callback = value;
        }

        struct MessageDialogSystem::Private
        {
            std::shared_ptr<MessageDialog> dialog;
        };

        MessageDialogSystem::MessageDialogSystem(const std::shared_ptr<Context>& context) :
            ISystem(context, "tl::ui::MessageDialogSystem"),
            _p(new Private)
        {}

        MessageDialogSystem::~MessageDialogSystem()
        {}

        std::shared_ptr<MessageDialogSystem> MessageDialogSystem::create(const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<MessageDialogSystem>(new MessageDialogSystem(context));
        }

        void MessageDialogSystem::open(
            const std::string& text,
            const std::shared_ptr<IWindow>& window,
            const std::function<void(bool)>& callback)
        {
            TG_P();
            if (auto context = _context.lock())
            {
                p.dialog = MessageDialog::create(context, text);
                p.dialog->open(window);
                p.dialog->setCallback(
                    [this, callback](bool value)
                    {
                        callback(value);
                        _p->dialog->close();
                    });
                p.dialog->setCloseCallback(
                    [this]
                    {
                        _p->dialog.reset();
                    });
            }
        }
    }
}
