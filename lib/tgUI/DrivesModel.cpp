// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/DrivesModel.h>

#include <tgCore/File.h>
#include <tgCore/Time.h>
#include <tgCore/Timer.h>

#include <atomic>
#include <mutex>
#include <thread>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        namespace
        {
            const std::chrono::milliseconds timeout(100);
        }

        struct DrivesModel::Private
        {
            std::shared_ptr<ObservableList<std::filesystem::path> > drives;

            struct Mutex
            {
                std::vector<std::filesystem::path> drives;
                std::mutex mutex;
            };
            Mutex mutex;
            std::thread thread;
            std::atomic<bool> running;

            std::shared_ptr<Timer> timer;
        };

        void DrivesModel::_init(const std::shared_ptr<Context>& context)
        {
            TG_P();

            p.drives = ObservableList<std::filesystem::path>::create();

            p.running = true;
            p.thread = std::thread(
                [this]
                {
                    TG_P();
                    while (p.running)
                    {
                        const auto drives = getDrives();
                        {
                            std::lock_guard<std::mutex> lock(p.mutex.mutex);
                            p.mutex.drives = drives;
                        }
                        sleep(timeout);
                    }
                });

            p.timer = Timer::create(context);
            p.timer->setRepeating(true);
            p.timer->start(
                timeout,
                [this]
                {
                    TG_P();
                    std::vector<std::filesystem::path> drives;
                    {
                        std::lock_guard<std::mutex> lock(p.mutex.mutex);
                        drives = p.mutex.drives;
                    }
                    p.drives->setIfChanged(drives);
                });
        }

        DrivesModel::DrivesModel() :
            _p(new Private)
        {}

        DrivesModel::~DrivesModel()
        {
            TG_P();
            p.running = false;
            if (p.thread.joinable())
            {
                p.thread.join();
            }
        }

        std::shared_ptr<DrivesModel> DrivesModel::create(
            const std::shared_ptr<Context>& context)
        {
            auto out = std::shared_ptr<DrivesModel>(new DrivesModel);
            out->_init(context);
            return out;
        }

        std::shared_ptr<IObservableList<std::filesystem::path> > DrivesModel::observeDrives() const
        {
            return _p->drives;
        }
    }
}
