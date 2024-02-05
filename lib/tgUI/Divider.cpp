// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Divider.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct Divider::Private
        {
            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int size = 0;
            };
            SizeData size;
        };

        void Divider::_init(
            const std::shared_ptr<Context>& context,
            Orientation orientation,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::Divider", parent);
            setBackgroundRole(ColorRole::Border);
            switch (orientation)
            {
            case Orientation::Horizontal:
                setVStretch(Stretch::Expanding);
                break;
            case Orientation::Vertical:
                setHStretch(Stretch::Expanding);
                break;
            default: break;
            }
        }

        Divider::Divider() :
            _p(new Private)
        {}

        Divider::~Divider()
        {}

        std::shared_ptr<Divider> Divider::create(
            const std::shared_ptr<Context>& context,
            Orientation orientation,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<Divider>(new Divider);
            out->_init(context, orientation, parent);
            return out;
        }

        void Divider::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();
            if (p.size.init || event.displayScale != p.size.displayScale)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.size = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
            }
            _sizeHint.w = _sizeHint.h = p.size.size;
        }
    }
}
