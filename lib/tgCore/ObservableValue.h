// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Observable.h>
#include <tgCore/Util.h>

#include <functional>
#include <memory>
#include <vector>

namespace tg
{
    namespace core
    {
        //! \name Observables
        ///@{

        template<typename T>
        class IObservableValue;

        //! Value observer.
        template<typename T>
        class ValueObserver : public std::enable_shared_from_this<ValueObserver<T> >
        {
            TG_NON_COPYABLE(ValueObserver);

        protected:
            void _init(
                const std::weak_ptr<IObservableValue<T> >&,
                const std::function<void(const T&)>&,
                ObserverAction);

            ValueObserver() = default;

        public:
            ~ValueObserver();

            //! Create a new value observer.
            static std::shared_ptr<ValueObserver<T> > create(
                const std::weak_ptr<IObservableValue<T> >&,
                const std::function<void(const T&)>&,
                ObserverAction = ObserverAction::Trigger);

            //! Execute the callback.
            void doCallback(const T&);

        private:
            std::function<void(const T&)> _callback;
            std::weak_ptr<IObservableValue<T> > _value;
        };

        //! Base class for observable values.
        template<typename T>
        class IObservableValue
        {
        public:
            virtual ~IObservableValue() = 0;

            //! Get the value.
            virtual const T& get() const = 0;

            //! Get the number of observers.
            std::size_t getObserversCount() const;

        protected:
            void _add(const std::weak_ptr<ValueObserver<T> >&);
            void _removeExpired();

            std::vector<std::weak_ptr<ValueObserver<T> > > _observers;

            friend class ValueObserver<T>;
        };

        //! Observable value.
        template<typename T>
        class ObservableValue : public IObservableValue<T>
        {
            TG_NON_COPYABLE(ObservableValue);

        protected:
            ObservableValue() = default;
            explicit ObservableValue(const T&);

        public:
            //! Create a new value.
            static std::shared_ptr<ObservableValue<T> > create();

            //! Create a new value.
            static std::shared_ptr<ObservableValue<T> > create(const T&);

            //! Set the value.
            void setAlways(const T&);

            //! Set the value only if it has changed.
            bool setIfChanged(const T&);

            const T& get() const override;

        private:
            T _value = T();
        };
        
        ///@}
    }
}

#include <tgCore/ObservableValueInline.h>
