// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIPy/IWindow.h>

#include <tgUI/IWindow.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace tg
{
    namespace ui
    {
        class PyIWindow : public IWindow
        {
        public:
            virtual void drawEvent(const core::Box2I& drawRect, const ui::DrawEvent& event) override
            {
                PYBIND11_OVERRIDE(
                    void,
                    IWindow,
                    drawEvent,
                    drawRect,
                    event);
            }
        };

        void iWindow(py::module_& m)
        {
            py::class_<IWindow, IWidget, std::shared_ptr<IWindow>, PyIWindow>(m, "IWindow");
        }
    }
}
