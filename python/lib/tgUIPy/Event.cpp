// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/Event.h>

#include <tgUI/Event.h>
#include <tgUI/IWidget.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        void event(py::module_& m)
        {
            py::class_<ChildEvent>(m, "ChildEvent")
                .def(py::init<const std::shared_ptr<IWidget>& >())
                .def_readwrite("child", &ChildEvent::child);

            py::class_<TickEvent>(m, "TickEvent");

            py::class_<SizeHintEvent>(m, "SizeHintEvent")
                .def(py::init<
                    const std::shared_ptr<core::FontSystem>&,
                    float,
                    const std::shared_ptr<Style>&,
                    const std::shared_ptr<IconLibrary>& >())
                .def_readwrite("fontSystem", &SizeHintEvent::fontSystem)
                .def_readwrite("displayScale", &SizeHintEvent::displayScale)
                .def_readwrite("style", &SizeHintEvent::style)
                .def_readwrite("iconLibrary", &SizeHintEvent::iconLibrary);

            py::class_<DrawEvent>(m, "DrawEvent")
                .def(py::init<
                    const std::shared_ptr<core::FontSystem>&,
                    float,
                    const std::shared_ptr<Style>&,
                    const std::shared_ptr<IconLibrary>&,
                    const std::shared_ptr<core::IRender>& >())
                .def_readwrite("fontSystem", &DrawEvent::fontSystem)
                .def_readwrite("displayScale", &DrawEvent::displayScale)
                .def_readwrite("style", &DrawEvent::style)
                .def_readwrite("iconLibrary", &DrawEvent::iconLibrary)
                .def_readwrite("render", &DrawEvent::render);

            py::class_<DragAndDropData, std::shared_ptr<DragAndDropData> >(m, "DragAndDropData");

            py::class_<MouseMoveEvent>(m, "MouseMoveEvent")
                .def(py::init<const core::V2I&, const core::V2I&>())
                .def_readwrite("pos", &MouseMoveEvent::pos)
                .def_readwrite("prev", &MouseMoveEvent::prev)
                .def_readwrite("accept", &MouseMoveEvent::accept)
                .def_readwrite("dndData", &MouseMoveEvent::dndData)
                .def_readwrite("dndCursor", &MouseMoveEvent::dndCursor)
                .def_readwrite("dndCursorHotspot", &MouseMoveEvent::dndCursorHotspot);

            py::enum_<KeyModifier>(m, "KeyModifier")
                .value("KeyModifierNone", KeyModifier::None)
                .value("Shift", KeyModifier::Shift)
                .value("Control", KeyModifier::Control)
                .value("Alt", KeyModifier::Alt)
                .value("Super", KeyModifier::Super)
                .export_values();
            m.attr("commandKeyModifier") = commandKeyModifier;
            m.def("getKeyModifierLabel", &getKeyModifierLabel);

            py::class_<MouseClickEvent>(m, "MouseClickEvent")
                .def(py::init<>())
                .def(py::init<int, int, const core::V2I&>())
                .def_readwrite("button", &MouseClickEvent::button)
                .def_readwrite("modifiers", &MouseClickEvent::modifiers)
                .def_readwrite("pos", &MouseClickEvent::pos)
                .def_readwrite("accept", &MouseClickEvent::accept);

            py::class_<ScrollEvent>(m, "ScrollEvent")
                .def(py::init<const core::V2F&, int, const core::V2I&>())
                .def_readwrite("value", &ScrollEvent::value)
                .def_readwrite("modifiers", &ScrollEvent::modifiers)
                .def_readwrite("pos", &ScrollEvent::pos)
                .def_readwrite("accept", &ScrollEvent::accept);

            py::enum_<Key>(m, "Key")
                .value("Unknown", Key::Unknown)
                .value("Space", Key::Space)
                .value("Apostrophe", Key::Apostrophe)
                .value("Comma)", Key::Comma)
                .value("Minus", Key::Minus)
                .value("Period", Key::Period)
                .value("Slash", Key::Slash)
                .value("_0", Key::_0)
                .value("_1", Key::_1)
                .value("_2", Key::_2)
                .value("_3", Key::_3)
                .value("_4", Key::_4)
                .value("_5", Key::_5)
                .value("_6", Key::_6)
                .value("_7", Key::_7)
                .value("_8", Key::_8)
                .value("_9", Key::_9)
                .value("Semicolon", Key::Semicolon)
                .value("Equal", Key::Equal)
                .value("A", Key::A)
                .value("B", Key::B)
                .value("C", Key::C)
                .value("D", Key::D)
                .value("E", Key::E)
                .value("F", Key::F)
                .value("G", Key::G)
                .value("H", Key::H)
                .value("I", Key::I)
                .value("J", Key::J)
                .value("K", Key::K)
                .value("L", Key::L)
                .value("M", Key::M)
                .value("N", Key::N)
                .value("O", Key::O)
                .value("P", Key::P)
                .value("Q", Key::Q)
                .value("R", Key::R)
                .value("S", Key::S)
                .value("T", Key::T)
                .value("U", Key::U)
                .value("V", Key::V)
                .value("W", Key::W)
                .value("X", Key::X)
                .value("Y", Key::Y)
                .value("Z", Key::Z)
                .value("LeftBracket", Key::LeftBracket)
                .value("Backslash", Key::Backslash)
                .value("RightBracket", Key::RightBracket)
                .value("GraveAccent", Key::GraveAccent)
                .value("Escape", Key::Escape)
                .value("Enter", Key::Enter)
                .value("Tab", Key::Tab)
                .value("Backspace", Key::Backspace)
                .value("Insert", Key::Insert)
                .value("Delete", Key::Delete)
                .value("Right", Key::Right)
                .value("Left", Key::Left)
                .value("Down", Key::Down)
                .value("Up", Key::Up)
                .value("PageUp", Key::PageUp)
                .value("PageDown", Key::PageDown)
                .value("Home", Key::Home)
                .value("End", Key::End)
                .value("CapsLock", Key::CapsLock)
                .value("ScrollLock", Key::ScrollLock)
                .value("NumLock", Key::NumLock)
                .value("PrintScreen", Key::PrintScreen)
                .value("Pause", Key::Pause)
                .value("F1", Key::F1)
                .value("F2", Key::F2)
                .value("F3", Key::F3)
                .value("F4", Key::F4)
                .value("F5", Key::F5)
                .value("F6", Key::F6)
                .value("F7", Key::F7)
                .value("F8", Key::F8)
                .value("F9", Key::F9)
                .value("F10", Key::F10)
                .value("F11", Key::F11)
                .value("F12", Key::F12)
                .value("LeftShift", Key::LeftShift)
                .value("LeftControl", Key::LeftControl)
                .value("LeftAlt", Key::LeftAlt)
                .value("LeftSuper", Key::LeftSuper)
                .value("RightShift", Key::RightShift)
                .value("RightControl", Key::RightControl)
                .value("RightAlt", Key::RightAlt)
                .value("RightSuper", Key::RightSuper)
                .export_values();
            m.def(
                "getShortcutLabel",
                &getShortcutLabel,
                py::arg("key"),
                py::arg("modifiers"));

            py::class_<KeyEvent>(m, "KeyEvent")
                .def(py::init<>())
                .def(py::init<Key, int, const core::V2I&>())
                .def_readwrite("key", &KeyEvent::key)
                .def_readwrite("modifiers", &KeyEvent::modifiers)
                .def_readwrite("pos", &KeyEvent::pos)
                .def_readwrite("accept", &KeyEvent::accept);

            py::class_<TextEvent>(m, "TextEvent")
                .def(py::init<const std::string&>())
                .def_readwrite("text", &TextEvent::text)
                .def_readwrite("accept", &TextEvent::accept);

            py::class_<TextDragAndDropData, DragAndDropData, std::shared_ptr<TextDragAndDropData> >(m, "TextDragAndDropData")
                .def(py::init<const std::string&>())
                .def_property_readonly("text", &TextDragAndDropData::getText);

            py::class_<DragAndDropEvent>(m, "DragAndDropEvent")
                .def(py::init<
                    const core::V2I&,
                    const core::V2I&,
                    const std::shared_ptr<DragAndDropData>&>())
                .def_readwrite("pos", &DragAndDropEvent::pos)
                .def_readwrite("prev", &DragAndDropEvent::prev)
                .def_readwrite("data", &DragAndDropEvent::data)
                .def_readwrite("accept", &DragAndDropEvent::accept);
        }
    }
}
