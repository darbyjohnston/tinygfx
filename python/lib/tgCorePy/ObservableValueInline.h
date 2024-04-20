// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

namespace tg
{
    namespace core
    {
        template<typename T>
        inline void observableValue(pybind11::module_& m, const std::string& type)
        {
            std::string name = "ValueObserver" + type;
            py::class_<ValueObserver<T>, std::shared_ptr<ValueObserver<T> > >(m, name.c_str())
                .def(
                    py::init(&ValueObserver<T>::create),
                    py::arg("observableValue"),
                    py::arg("callback"),
                    py::arg("action") = ObserverAction::Trigger);
            name = "IObservableValue" + type;
            py::class_<IObservableValue<T>, std::shared_ptr<IObservableValue<T> > >(m, name.c_str());
            name = "ObservableValue" + type;
            py::class_<ObservableValue<T>, IObservableValue<T>, std::shared_ptr<ObservableValue<T> > >(m, name.c_str())
                .def(py::init(py::overload_cast<const T&>(&ObservableValue<T>::create)))
                .def("setAlways", &ObservableValue<T>::setAlways)
                .def("setIfChanged", &ObservableValue<T>::setIfChanged)
                .def("get", &ObservableValue<T>::get);
        }
    }
}
