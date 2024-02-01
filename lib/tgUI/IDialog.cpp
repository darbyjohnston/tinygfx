// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IDialog.h>

#include <tgUI/DrawUtil.h>
#include <tgUI/IWindow.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct IDialog::Private
        {
            bool open = false;
            std::function<void(void)> closeCallback;
            
            struct SizeData
            {
                bool sizeInit = true;
                int margin = 0;
                int border = 0;
                int shadow = 0;
            };
            SizeData size;
        };

        void IDialog::_init(
            const std::shared_ptr<Context>& context,
            const std::string& objectName,
            const std::shared_ptr<IWidget>& parent)
        {
            IPopup::_init(context, objectName, parent);
        }

        IDialog::IDialog() :
            _p(new Private)
        {}

        IDialog::~IDialog()
        {}

        void IDialog::open(const std::shared_ptr<IWindow>& window)
        {
            TG_P();
            p.open = true;
            setParent(window);
            takeKeyFocus();
        }

        bool IDialog::isOpen() const
        {
            return _p->open;
        }

        void IDialog::close()
        {
            TG_P();
            p.open = false;
            setParent(nullptr);
            if (p.closeCallback)
            {
                p.closeCallback();
            }
        }

        void IDialog::setCloseCallback(const std::function<void(void)>& value)
        {
            _p->closeCallback = value;
        }

        void IDialog::setGeometry(const Box2I& value)
        {
            IPopup::setGeometry(value);
            TG_P();
            if (!_children.empty())
            {
                const Box2I g = margin(value, -p.size.margin);
                const Size2I& sizeHint = _children.front()->getSizeHint();
                V2I size;
                size.x = std::min(sizeHint.w, g.w());
                size.y = std::min(sizeHint.h, g.h());
                if (Stretch::Expanding == _children.front()->getHStretch())
                {
                    size.x = g.w();
                }
                if (Stretch::Expanding == _children.front()->getVStretch())
                {
                    size.y = g.h();
                }
                _children.front()->setGeometry(Box2I(
                    g.x() + g.w() / 2 - size.x / 2,
                    g.y() + g.h() / 2 - size.y / 2,
                    size.x,
                    size.y));
            }
        }

        void IDialog::sizeHintEvent(const SizeHintEvent& event)
        {
            const bool displayScaleChanged = event.displayScale != _displayScale;
            IPopup::sizeHintEvent(event);
            TG_P();

            if (displayScaleChanged || p.size.sizeInit)
            {
                p.size.margin = event.style->getSizeRole(SizeRole::MarginDialog, _displayScale);
                p.size.border = event.style->getSizeRole(SizeRole::Border, _displayScale);
                p.size.shadow = event.style->getSizeRole(SizeRole::Shadow, _displayScale);
            }
            p.size.sizeInit = false;
        }

        void IDialog::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IPopup::drawEvent(drawRect, event);
            TG_P();
            if (!_children.empty())
            {
                const Box2I g = _children.front()->getGeometry();
                const Box2I g2(
                    g.min.x - p.size.shadow,
                    g.min.y,
                    g.w() + p.size.shadow * 2,
                    g.h() + p.size.shadow);
                event.render->drawColorMesh(
                    shadow(g2, p.size.shadow),
                    Color4F(1.F, 1.F, 1.F));

                event.render->drawMesh(
                    border(margin(g, p.size.border), p.size.border),
                    event.style->getColorRole(ColorRole::Border));
                
                event.render->drawRect(
                    Box2F(g.x(), g.y(), g.w(), g.h()),
                    event.style->getColorRole(ColorRole::Window));
            }
        }
    }
}
