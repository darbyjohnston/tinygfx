// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/Event.h>

#include <tgCore/Error.h>
#include <tgCore/String.h>

#include <sstream>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        ChildEvent::ChildEvent(const std::shared_ptr<IWidget>& child) :
            child(child)
        {}

        TickEvent::TickEvent(
            const std::shared_ptr<FontSystem>&  fontSystem,
            const std::shared_ptr<Style>&       style,
            const std::shared_ptr<IconLibrary>& iconLibrary) :
            fontSystem(fontSystem),
            style(style),
            iconLibrary(iconLibrary)
        {}

        SizeHintEvent::SizeHintEvent(
            const std::shared_ptr<FontSystem>&  fontSystem,
            float                               displayScale,
            const std::shared_ptr<Style>&       style,
            const std::shared_ptr<IconLibrary>& iconLibrary) :
            fontSystem(fontSystem),
            displayScale(displayScale),
            style(style),
            iconLibrary(iconLibrary)
        {}

        DrawEvent::DrawEvent(
            const std::shared_ptr<FontSystem>&      fontSystem,
            float                                   displayScale,
            const std::shared_ptr<Style>&           style,
            const std::shared_ptr<IconLibrary>&     iconLibrary,
            const std::shared_ptr<render::IRender>& render) :
            fontSystem(fontSystem),
            displayScale(displayScale),
            style(style),
            iconLibrary(iconLibrary),
            render(render)
        {}

        DragAndDropData::~DragAndDropData()
        {}

        MouseMoveEvent::MouseMoveEvent(
            const V2I& pos,
            const V2I& prev) :
            pos(pos),
            prev(prev)
        {}

        MouseClickEvent::MouseClickEvent(
            int        button,
            int        modifiers,
            const V2I& pos) :
            button(button),
            modifiers(modifiers),
            pos(pos)
        {}

        ScrollEvent::ScrollEvent(
            const V2F& value,
            int        modifiers,
            const V2I& pos) :
            value(value),
            modifiers(modifiers),
            pos(pos)
        {}

        std::string getKeyModifierLabel(int value)
        {
            std::vector<std::string> out;
            if (value & static_cast<size_t>(KeyModifier::Shift))
            {
                out.push_back("Shift");
            }
            if (value & static_cast<size_t>(KeyModifier::Control))
            {
                out.push_back("Ctrl");
            }
            if (value & static_cast<size_t>(KeyModifier::Alt))
            {
                out.push_back("Alt");
            }
            if (value & static_cast<size_t>(KeyModifier::Super))
            {
                out.push_back("Cmd");
            }
            return join(out, '+');
        }

        TG_ENUM_IMPL(
            Key,
            "Unknown",
            "Space",
            "Apostrophe",
            "Comma",
            "Minus",
            "Period",
            "Slash",
            "_0",
            "_1",
            "_2",
            "_3",
            "_4",
            "_5",
            "_6",
            "_7",
            "_8",
            "_9",
            "Semicolon",
            "Equal",
            "A",
            "B",
            "C",
            "D",
            "E",
            "F",
            "G",
            "H",
            "I",
            "J",
            "K",
            "L",
            "M",
            "N",
            "O",
            "P",
            "Q",
            "R",
            "S",
            "T",
            "U",
            "V",
            "W",
            "X",
            "Y",
            "Z",
            "LeftBracket",
            "Backslash",
            "RightBracket",
            "GraveAccent",
            "Escape",
            "Enter",
            "Tab",
            "Backspace",
            "Insert",
            "Delete",
            "Right",
            "Left",
            "Down",
            "Up",
            "PageUp",
            "PageDown",
            "Home",
            "End",
            "CapsLock",
            "ScrollLock",
            "NumLock",
            "PrintScreen",
            "Pause",
            "F1",
            "F2",
            "F3",
            "F4",
            "F5",
            "F6",
            "F7",
            "F8",
            "F9",
            "F10",
            "F11",
            "F12",
            "LeftShift",
            "LeftControl",
            "LeftAlt",
            "LeftSuper",
            "RightShift",
            "RightControl",
            "RightAlt",
            "RightSuper");

        std::string getLabel(Key key, int modifiers)
        {
            std::stringstream ss;
            if (key != Key::Unknown)
            {
                if (modifiers)
                {
                    ss << getKeyModifierLabel(modifiers);
                    ss << "+";
                }
                ss << key;
            }
            return ss.str();
        }

        KeyEvent::KeyEvent(
            Key        key,
            int        modifiers,
            const V2I& pos) :
            key(key),
            modifiers(modifiers),
            pos(pos)
        {}

        TextEvent::TextEvent(const std::string& text) :
            text(text)
        {}

        TextDragAndDropData::TextDragAndDropData(const std::string& text) :
            _text(text)
        {}

        TextDragAndDropData::~TextDragAndDropData()
        {}

        const std::string& TextDragAndDropData::getText() const
        {
            return _text;
        }

        DragAndDropEvent::DragAndDropEvent(
            const V2I& pos,
            const V2I& prev,
            const std::shared_ptr<DragAndDropData>& data) :
            pos(pos),
            prev(prev),
            data(data)
        {}
    }
}
