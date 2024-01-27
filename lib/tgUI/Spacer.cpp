// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Spacer.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct Spacer::Private
        {
            Orientation orientation = Orientation::Horizontal;
            SizeRole spacingRole = SizeRole::Spacing;

            struct SizeData
            {
                bool sizeInit = true;
                int size = 0;
            };
            SizeData size;
        };

        void Spacer::_init(
            const std::shared_ptr<Context>& context,
            Orientation orientation,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::Spacer", parent);
            TG_P();
            p.orientation = orientation;
        }

        Spacer::Spacer() :
            _p(new Private)
        {}

        Spacer::~Spacer()
        {}

        std::shared_ptr<Spacer> Spacer::create(
            const std::shared_ptr<Context>& context,
            Orientation orientation,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<Spacer>(new Spacer);
            out->_init(context, orientation, parent);
            return out;
        }

        void Spacer::setSpacingRole(SizeRole value)
        {
            TG_P();
            if (value == p.spacingRole)
                return;
            p.spacingRole = value;
            p.size.sizeInit = true;
            _updates |= Update::Size;
        }

        void Spacer::sizeHintEvent(const SizeHintEvent& event)
        {
            const bool displayScaleChanged = event.displayScale != _displayScale;
            IWidget::sizeHintEvent(event);
            TG_P();

            if (displayScaleChanged || p.size.sizeInit)
            {
                p.size.size = event.style->getSizeRole(p.spacingRole, _displayScale);
            }
            p.size.sizeInit = false;

            _sizeHint = Size2I();
            switch (p.orientation)
            {
            case Orientation::Horizontal:
                _sizeHint.w = p.size.size;
                break;
            case Orientation::Vertical:
                _sizeHint.h = p.size.size;
                break;
            default: break;
            }
        }
    }
}
