// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

namespace tg
{
    namespace core
    {
        template<typename T>
        inline void observableList(pybind11::module_& m, const std::string& type)
        {
            std::string name = "ListObserver" + type;
            py::class_<ListObserver<T>, std::shared_ptr<ListObserver<T> > >(m, name.c_str())
                .def(
                    py::init(&ListObserver<T>::create),
                    py::arg("observableList"),
                    py::arg("callback"),
                    py::arg("action") = ObserverAction::Trigger);
            name = "IObservableList" + type;
            py::class_<IObservableList<T>, std::shared_ptr<IObservableList<T> > >(m, name.c_str());
            name = "ObservableList" + type;
            py::class_<ObservableList<T>, IObservableList<T>, std::shared_ptr<ObservableList<T> > >(m, name.c_str())
                .def(py::init(py::overload_cast<const std::vector<T>&>(&ObservableList<T>::create)))
                .def("setAlways", &ObservableList<T>::setAlways)
                .def("setIfChanged", &ObservableList<T>::setIfChanged)
                .def("get", &ObservableList<T>::get);
        }
    }
}
