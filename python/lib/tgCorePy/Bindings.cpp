// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCorePy/Bindings.h>

#include <tgCorePy/Box.h>
#include <tgCorePy/Color.h>
#include <tgCorePy/Context.h>
#include <tgCorePy/FontSystem.h>
#include <tgCorePy/IRender.h>
#include <tgCorePy/ISystem.h>
#include <tgCorePy/Image.h>
#include <tgCorePy/Memory.h>
#include <tgCorePy/Observable.h>
#include <tgCorePy/ObservableList.h>
#include <tgCorePy/ObservableMap.h>
#include <tgCorePy/ObservableValue.h>
#include <tgCorePy/OS.h>
#include <tgCorePy/Random.h>
#include <tgCorePy/Range.h>
#include <tgCorePy/Size.h>
#include <tgCorePy/Vector.h>

#include <tgCore/Context.h>
#include <tgCore/Init.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace tg
{
    namespace core
    {
        void bind(py::module_& m)
        {
            auto sm = m.def_submodule("tgCore");
            sm.doc() = "Core functionality";

            sm.def("init", &init, "Initialize the library.");

            iSystem(sm);

            box(sm);
            color(sm);
            context(sm);
            fontSystem(sm);
            iRender(sm);
            image(sm);
            memory(sm);
            observable(sm);
            observableList(sm);
            observableMap(sm);
            observableValue(sm);
            os(sm);
            random(sm);
            range(sm);
            size(sm);
            vector(sm);
        }
    }
}
