// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/ObservableList.h>

#include <string>

namespace tg
{
    namespace core
    {
        class Context;
    }

    namespace ui
    {
        //! \name File Widgets
        ///@{
        
        //! File system drives model.
        class DrivesModel : public std::enable_shared_from_this<DrivesModel>
        {
            TG_NON_COPYABLE(DrivesModel);

        protected:
            void _init(const std::shared_ptr<core::Context>&);

            DrivesModel();

        public:
            ~DrivesModel();

            //! Create a new model.
            static std::shared_ptr<DrivesModel> create(
                const std::shared_ptr<core::Context>&);

            //! Observe the list of drives.
            std::shared_ptr<core::IObservableList<std::string> > observeDrives() const;

        private:
            TG_PRIVATE();
        };
        
        ///@}
    }
}
