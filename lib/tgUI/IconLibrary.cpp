// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/IconLibrary.h>

//#include <tgIO/PNG.h>
//#include <tgIO/System.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>
#include <tgCore/LRUCache.h>

namespace
{
#include <Icons/Audio_192.h>
#include <Icons/Audio_96.h>
#include <Icons/BellowsClosed_192.h>
#include <Icons/BellowsClosed_96.h>
#include <Icons/BellowsOpen_192.h>
#include <Icons/BellowsOpen_96.h>
#include <Icons/Clear_192.h>
#include <Icons/Clear_96.h>
#include <Icons/Close_192.h>
#include <Icons/Close_96.h>
#include <Icons/Copy_192.h>
#include <Icons/Copy_96.h>
#include <Icons/Decrement_192.h>
#include <Icons/Decrement_96.h>
#include <Icons/Directory_192.h>
#include <Icons/Directory_96.h>
#include <Icons/DirectoryUp_192.h>
#include <Icons/DirectoryUp_96.h>
#include <Icons/Empty_192.h>
#include <Icons/Empty_96.h>
#include <Icons/File_192.h>
#include <Icons/File_96.h>
#include <Icons/FileBrowser_192.h>
#include <Icons/FileBrowser_96.h>
#include <Icons/FileClose_192.h>
#include <Icons/FileClose_96.h>
#include <Icons/FileCloseAll_192.h>
#include <Icons/FileCloseAll_96.h>
#include <Icons/FileOpen_192.h>
#include <Icons/FileOpen_96.h>
#include <Icons/FrameNext_192.h>
#include <Icons/FrameNext_96.h>
#include <Icons/FramePrev_192.h>
#include <Icons/FramePrev_96.h>
#include <Icons/Increment_192.h>
#include <Icons/Increment_96.h>
#include <Icons/MenuArrow_192.h>
#include <Icons/MenuArrow_96.h>
#include <Icons/MenuChecked_192.h>
#include <Icons/MenuChecked_96.h>
#include <Icons/MenuUnchecked_192.h>
#include <Icons/MenuUnchecked_96.h>
#include <Icons/Mute_192.h>
#include <Icons/Mute_96.h>
#include <Icons/Next_192.h>
#include <Icons/Next_96.h>
#include <Icons/PlaybackForward_192.h>
#include <Icons/PlaybackForward_96.h>
#include <Icons/PlaybackReverse_192.h>
#include <Icons/PlaybackReverse_96.h>
#include <Icons/PlaybackStop_192.h>
#include <Icons/PlaybackStop_96.h>
#include <Icons/Prev_192.h>
#include <Icons/Prev_96.h>
#include <Icons/Reload_192.h>
#include <Icons/Reload_96.h>
#include <Icons/Reset_192.h>
#include <Icons/Reset_96.h>
#include <Icons/Settings_192.h>
#include <Icons/Settings_96.h>
#include <Icons/SubMenuArrow_192.h>
#include <Icons/SubMenuArrow_96.h>
#include <Icons/TimeEnd_192.h>
#include <Icons/TimeEnd_96.h>
#include <Icons/TimeStart_192.h>
#include <Icons/TimeStart_96.h>
#include <Icons/Volume_192.h>
#include <Icons/Volume_96.h>
#include <Icons/WindowFullScreen_192.h>
#include <Icons/WindowFullScreen_96.h>
}

#include <atomic>
#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        namespace
        {
            const size_t requestCount = 1;
        }

        struct IconLibrary::Private
        {
            std::weak_ptr<Context> context;
            
            std::map<std::pair<std::string, int>, std::vector<uint8_t> > iconData;
            
            struct Request
            {
                std::string name;
                float displayScale = 1.F;
                std::promise<std::shared_ptr<Image> > promise;
                //std::shared_ptr<io::IRead> reader;
                //std::future<io::VideoData> future;
            };
            const size_t requestTimeout = 5;

            typedef std::pair<std::string, float> CacheKey;

            struct Mutex
            {
                std::list<std::shared_ptr<Request> > requests;
                bool stopped = false;
                std::mutex mutex;
            };
            Mutex mutex;

            struct Thread
            {
                //std::shared_ptr<io::IPlugin> plugin;
                LRUCache<CacheKey, std::shared_ptr<Image> > cache;
                std::condition_variable cv;
                std::thread thread;
                std::atomic<bool> running;
            };
            Thread thread;
        };
        
        void IconLibrary::_init(const std::shared_ptr<Context>& context)
        {
            TG_P();
            p.context = context;
            
            /*p.iconData[std::make_pair("Audio", 96)] = Audio_96_png;
            p.iconData[std::make_pair("BellowsClosed", 96)] = BellowsClosed_96_png;
            p.iconData[std::make_pair("BellowsOpen", 96)] = BellowsOpen_96_png;
            p.iconData[std::make_pair("Clear", 96)] = Clear_96_png;
            p.iconData[std::make_pair("Close", 96)] = Close_96_png;
            p.iconData[std::make_pair("Color", 96)] = Color_96_png;
            p.iconData[std::make_pair("Compare", 96)] = Compare_96_png;
            p.iconData[std::make_pair("CompareA", 96)] = CompareA_96_png;
            p.iconData[std::make_pair("CompareB", 96)] = CompareB_96_png;
            p.iconData[std::make_pair("CompareDifference", 96)] = CompareDifference_96_png;
            p.iconData[std::make_pair("CompareHorizontal", 96)] = CompareHorizontal_96_png;
            p.iconData[std::make_pair("CompareOverlay", 96)] = CompareOverlay_96_png;
            p.iconData[std::make_pair("CompareTile", 96)] = CompareTile_96_png;
            p.iconData[std::make_pair("CompareVertical", 96)] = CompareVertical_96_png;
            p.iconData[std::make_pair("CompareWipe", 96)] = CompareWipe_96_png;
            p.iconData[std::make_pair("Copy", 96)] = Copy_96_png;
            p.iconData[std::make_pair("Decrement", 96)] = Decrement_96_png;
            p.iconData[std::make_pair("Devices", 96)] = Devices_96_png;
            p.iconData[std::make_pair("Directory", 96)] = Directory_96_png;
            p.iconData[std::make_pair("DirectoryUp", 96)] = DirectoryUp_96_png;
            p.iconData[std::make_pair("DockWidgetClose", 96)] = DockWidgetClose_96_png;
            p.iconData[std::make_pair("DockWidgetNormal", 96)] = DockWidgetNormal_96_png;
            p.iconData[std::make_pair("Empty", 96)] = Empty_96_png;
            p.iconData[std::make_pair("File", 96)] = File_96_png;
            p.iconData[std::make_pair("FileBrowser", 96)] = FileBrowser_96_png;
            p.iconData[std::make_pair("FileClose", 96)] = FileClose_96_png;
            p.iconData[std::make_pair("FileCloseAll", 96)] = FileCloseAll_96_png;
            p.iconData[std::make_pair("FileOpen", 96)] = FileOpen_96_png;
            p.iconData[std::make_pair("FileOpenSeparateAudio", 96)] = FileOpenSeparateAudio_96_png;
            p.iconData[std::make_pair("Files", 96)] = Files_96_png;
            p.iconData[std::make_pair("FrameNext", 96)] = FrameNext_96_png;
            p.iconData[std::make_pair("FramePrev", 96)] = FramePrev_96_png;
            p.iconData[std::make_pair("Increment", 96)] = Increment_96_png;
            p.iconData[std::make_pair("Info", 96)] = Info_96_png;
            p.iconData[std::make_pair("MenuArrow", 96)] = MenuArrow_96_png;
            p.iconData[std::make_pair("MenuChecked", 96)] = MenuChecked_96_png;
            p.iconData[std::make_pair("MenuUnchecked", 96)] = MenuUnchecked_96_png;
            p.iconData[std::make_pair("Messages", 96)] = Messages_96_png;
            p.iconData[std::make_pair("Mute", 96)] = Mute_96_png;
            p.iconData[std::make_pair("Next", 96)] = Next_96_png;
            p.iconData[std::make_pair("PlaybackForward", 96)] = PlaybackForward_96_png;
            p.iconData[std::make_pair("PlaybackReverse", 96)] = PlaybackReverse_96_png;
            p.iconData[std::make_pair("PlaybackStop", 96)] = PlaybackStop_96_png;
            p.iconData[std::make_pair("Prev", 96)] = Prev_96_png;
            p.iconData[std::make_pair("Reset", 96)] = Reset_96_png;
            p.iconData[std::make_pair("Reload", 96)] = Reload_96_png;
            p.iconData[std::make_pair("Settings", 96)] = Settings_96_png;
            p.iconData[std::make_pair("SubMenuArrow", 96)] = SubMenuArrow_96_png;
            p.iconData[std::make_pair("TimeEnd", 96)] = TimeEnd_96_png;
            p.iconData[std::make_pair("TimeStart", 96)] = TimeStart_96_png;
            p.iconData[std::make_pair("View", 96)] = View_96_png;
            p.iconData[std::make_pair("ViewFrame", 96)] = ViewFrame_96_png;
            p.iconData[std::make_pair("ViewZoom1To1", 96)] = ViewZoom1To1_96_png;
            p.iconData[std::make_pair("Volume", 96)] = Volume_96_png;
            p.iconData[std::make_pair("WindowFullScreen", 96)] = WindowFullScreen_96_png;
            p.iconData[std::make_pair("WindowSecondary", 96)] = WindowSecondary_96_png;

            p.iconData[std::make_pair("Audio", 192)] = Audio_192_png;
            p.iconData[std::make_pair("BellowsClosed", 192)] = BellowsClosed_192_png;
            p.iconData[std::make_pair("BellowsOpen", 192)] = BellowsOpen_192_png;
            p.iconData[std::make_pair("Clear", 192)] = Clear_192_png;
            p.iconData[std::make_pair("Close", 192)] = Close_192_png;
            p.iconData[std::make_pair("Color", 192)] = Color_192_png;
            p.iconData[std::make_pair("Compare", 192)] = Compare_192_png;
            p.iconData[std::make_pair("CompareA", 192)] = CompareA_192_png;
            p.iconData[std::make_pair("CompareB", 192)] = CompareB_192_png;
            p.iconData[std::make_pair("CompareDifference", 192)] = CompareDifference_192_png;
            p.iconData[std::make_pair("CompareHorizontal", 192)] = CompareHorizontal_192_png;
            p.iconData[std::make_pair("CompareOverlay", 192)] = CompareOverlay_192_png;
            p.iconData[std::make_pair("CompareTile", 192)] = CompareTile_192_png;
            p.iconData[std::make_pair("CompareVertical", 192)] = CompareVertical_192_png;
            p.iconData[std::make_pair("CompareWipe", 192)] = CompareWipe_192_png;
            p.iconData[std::make_pair("Copy", 192)] = Copy_192_png;
            p.iconData[std::make_pair("Decrement", 192)] = Decrement_192_png;
            p.iconData[std::make_pair("Devices", 192)] = Devices_192_png;
            p.iconData[std::make_pair("Directory", 192)] = Directory_192_png;
            p.iconData[std::make_pair("DirectoryUp", 192)] = DirectoryUp_192_png;
            p.iconData[std::make_pair("DockWidgetClose", 192)] = DockWidgetClose_192_png;
            p.iconData[std::make_pair("DockWidgetNormal", 192)] = DockWidgetNormal_192_png;
            p.iconData[std::make_pair("Empty", 192)] = Empty_192_png;
            p.iconData[std::make_pair("File", 192)] = File_192_png;
            p.iconData[std::make_pair("FileBrowser", 192)] = FileBrowser_192_png;
            p.iconData[std::make_pair("FileClose", 192)] = FileClose_192_png;
            p.iconData[std::make_pair("FileCloseAll", 192)] = FileCloseAll_192_png;
            p.iconData[std::make_pair("FileOpen", 192)] = FileOpen_192_png;
            p.iconData[std::make_pair("FileOpenSeparateAudio", 192)] = FileOpenSeparateAudio_192_png;
            p.iconData[std::make_pair("Files", 192)] = Files_192_png;
            p.iconData[std::make_pair("FrameNext", 192)] = FrameNext_192_png;
            p.iconData[std::make_pair("FramePrev", 192)] = FramePrev_192_png;
            p.iconData[std::make_pair("Increment", 192)] = Increment_192_png;
            p.iconData[std::make_pair("Info", 192)] = Info_192_png;
            p.iconData[std::make_pair("MenuArrow", 192)] = MenuArrow_192_png;
            p.iconData[std::make_pair("MenuChecked", 192)] = MenuChecked_192_png;
            p.iconData[std::make_pair("MenuUnchecked", 192)] = MenuUnchecked_192_png;
            p.iconData[std::make_pair("Messages", 192)] = Messages_192_png;
            p.iconData[std::make_pair("Mute", 192)] = Mute_192_png;
            p.iconData[std::make_pair("Next", 192)] = Next_192_png;
            p.iconData[std::make_pair("PlaybackForward", 192)] = PlaybackForward_192_png;
            p.iconData[std::make_pair("PlaybackReverse", 192)] = PlaybackReverse_192_png;
            p.iconData[std::make_pair("PlaybackStop", 192)] = PlaybackStop_192_png;
            p.iconData[std::make_pair("Prev", 192)] = Prev_192_png;
            p.iconData[std::make_pair("Reset", 192)] = Reset_192_png;
            p.iconData[std::make_pair("Reload", 192)] = Reload_192_png;
            p.iconData[std::make_pair("Settings", 192)] = Settings_192_png;
            p.iconData[std::make_pair("SubMenuArrow", 192)] = SubMenuArrow_192_png;
            p.iconData[std::make_pair("TimeEnd", 192)] = TimeEnd_192_png;
            p.iconData[std::make_pair("TimeStart", 192)] = TimeStart_192_png;
            p.iconData[std::make_pair("View", 192)] = View_192_png;
            p.iconData[std::make_pair("ViewFrame", 192)] = ViewFrame_192_png;
            p.iconData[std::make_pair("ViewZoom1To1", 192)] = ViewZoom1To1_192_png;
            p.iconData[std::make_pair("Volume", 192)] = Volume_192_png;
            p.iconData[std::make_pair("WindowFullScreen", 192)] = WindowFullScreen_192_png;
            p.iconData[std::make_pair("WindowSecondary", 192)] = WindowSecondary_192_png;*/

            //auto io = context->getSystem<io::System>();
            //p.thread.plugin = io->getPlugin<png::Plugin>();
            p.thread.cache.setMax(1000);
            p.thread.running = true;
            p.thread.thread = std::thread(
                [this]
                {
                    TG_P();
                    while (p.thread.running)
                    {
                        std::list<std::shared_ptr<Private::Request> > requests;
                        {
                            std::unique_lock<std::mutex> lock(p.mutex.mutex);
                            if (p.thread.cv.wait_for(
                                lock,
                                std::chrono::milliseconds(p.requestTimeout),
                                [this]
                                {
                                    return !_p->mutex.requests.empty();
                                }))
                            {
                                for (
                                    size_t i = 0;
                                    i < requestCount && !p.mutex.requests.empty();
                                    ++i)
                                {
                                    requests.push_back(p.mutex.requests.front());
                                    p.mutex.requests.pop_front();
                                }
                            }
                        }
                        
                        auto i = requests.begin();
                        while (i != requests.end())
                        {
                            int dpi = 96;
                            if ((*i)->displayScale >= 2.F)
                            {
                                dpi = 192;
                            }

                            std::shared_ptr<Image> image;
                            if (p.thread.cache.get(std::make_pair((*i)->name, (*i)->displayScale), image))
                            {
                                (*i)->promise.set_value(image);
                                i = requests.erase(i);
                            }
                            else
                            {
                                //std::cout << "icon request: " << (*i)->name << " " << dpi << std::endl;
                                const auto j = p.iconData.find(std::make_pair((*i)->name, dpi));
                                if (j != p.iconData.end())
                                {
                                    try
                                    {
                                        const std::string name = Format("{0}_{1}.png").
                                            arg((*i)->name).
                                            arg(dpi);
                                        /*(*i)->reader = p.thread.plugin->read(
                                            file::Path(name),
                                            { file::MemoryRead(j->second.data(), j->second.size()) });
                                        if ((*i)->reader)
                                        {
                                            const auto ioInfo = (*i)->reader->getInfo().get();
                                            (*i)->future = (*i)->reader->readVideo(
                                                ioInfo.videoTime.start_time());
                                        }*/
                                    }
                                    catch (const std::exception&)
                                    {}
                                }
                                ++i;
                            }
                        }
                        for (const auto& request : requests)
                        {
                            /*std::shared_ptr<Image> image;
                            if (request->future.valid())
                            {
                                image = request->future.get().image;
                            }
                            request->promise.set_value(image);
                            p.thread.cache.add(
                                std::make_pair(request->name, request->displayScale),
                                image);*/
                        }
                    }
                    {
                        std::unique_lock<std::mutex> lock(p.mutex.mutex);
                        p.mutex.stopped = true;
                    }
                    cancelRequests();
                });
        }

        IconLibrary::IconLibrary() :
            _p(new Private)
        {}

        IconLibrary::~IconLibrary()
        {
            TG_P();
            p.thread.running = false;
            if (p.thread.thread.joinable())
            {
                p.thread.thread.join();
            }
        }

        std::shared_ptr<IconLibrary> IconLibrary::create(
            const std::shared_ptr<Context>& context)
        {
            auto out = std::shared_ptr<IconLibrary>(new IconLibrary);
            out->_init(context);
            return out;
        }

        std::future<std::shared_ptr<Image> > IconLibrary::request(
            const std::string& name,
            float displayScale)
        {
            TG_P();
            auto request = std::make_shared<Private::Request>();
            request->name = name;
            request->displayScale = displayScale;
            auto future = request->promise.get_future();
            bool valid = false;
            {
                std::unique_lock<std::mutex> lock(p.mutex.mutex);
                if (!p.mutex.stopped)
                {
                    valid = true;
                    p.mutex.requests.push_back(request);
                }
            }
            if (valid)
            {
                p.thread.cv.notify_one();
            }
            else
            {
                request->promise.set_value(nullptr);
            }
            return future;
        }
        
        void IconLibrary::cancelRequests()
        {
            TG_P();
            std::list<std::shared_ptr<Private::Request> > requests;
            {
                std::unique_lock<std::mutex> lock(p.mutex.mutex);
                requests = std::move(p.mutex.requests);
            }
            for (auto& request : requests)
            {
                request->promise.set_value(nullptr);
            }
        }
    }
}

