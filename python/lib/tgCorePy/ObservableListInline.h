// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/ObservableList.h>

namespace tg
{
    namespace core
    {
        template<typename T>
        inline void observableList(pybind11::module_& m, const std::string& type)
        {
            std::string name = "ListObserver" + type;
            pybind11::class_<ListObserver<T>, std::shared_ptr<ListObserver<T> > >(m, name.c_str())
                .def(
                    pybind11::init(&ListObserver<T>::create),
                    pybind11::arg("observableList"),
                    pybind11::arg("callback"),
                    pybind11::arg("action") = ObserverAction::Trigger);
            name = "IObservableList" + type;
            pybind11::class_<IObservableList<T>, std::shared_ptr<IObservableList<T> > >(m, name.c_str());
            name = "ObservableList" + type;
            pybind11::class_<ObservableList<T>, IObservableList<T>, std::shared_ptr<ObservableList<T> > >(m, name.c_str())
                .def(pybind11::init(pybind11::overload_cast<const std::vector<T>&>(&ObservableList<T>::create)))
                .def("setAlways", &ObservableList<T>::setAlways)
                .def("setIfChanged", &ObservableList<T>::setIfChanged)
                .def("get", &ObservableList<T>::get);
        }
    }
}
