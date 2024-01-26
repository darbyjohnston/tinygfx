// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidget.h>

namespace tg
{
    namespace ui
    {
        class IClipboard;

        //! Base class for windows.
        class IWindow : public IWidget
        {
        protected:
            IWindow();

        public:
            virtual ~IWindow() = 0;

            //! Set the widget with key focus.
            void setKeyFocus(const std::shared_ptr<IWidget>&);

            //! Get the clipboard.
            const std::shared_ptr<IClipboard>& getClipboard() const;

            //! Set the clipboard.
            void setClipboard(const std::shared_ptr<IClipboard>&);

            void setVisible(bool) override;
            void tickEvent(
                bool parentsVisible,
                bool parentsEnabled,
                const TickEvent&) override;
            void drawOverlayEvent(const core::Box2I&, const DrawEvent&) override;

        protected:
            bool _key(Key, bool press, int modifiers);
            void _text(const std::string&);
            void _cursorEnter(bool enter);
            void _cursorPos(const core::V2I&);
            void _mouseButton(int button, bool press, int modifiers);
            void _scroll(const core::V2F&, int modifiers);

            void _clipEventRecursive(
                const std::shared_ptr<IWidget>&,
                const core::Box2I&,
                bool clipped);

            virtual void _drop(const std::vector<std::string>&);

        private:
            std::list<std::shared_ptr<IWidget> > _getUnderCursor(const core::V2I&);
            void _getUnderCursor(
                const std::shared_ptr<IWidget>&,
                const core::V2I&,
                std::list<std::shared_ptr<IWidget> >&);

            void _setHover(const std::shared_ptr<IWidget>&);
            void _hoverUpdate(MouseMoveEvent&);

            std::shared_ptr<IWidget> _keyFocusNext(const std::shared_ptr<IWidget>&);
            std::shared_ptr<IWidget> _keyFocusPrev(const std::shared_ptr<IWidget>&);
            void _getKeyFocus(
                const std::shared_ptr<IWidget>&,
                std::list<std::shared_ptr<IWidget> >&);

            TG_PRIVATE();
        };
    }
}
