// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/FileBrowser.h>

#include <tgUI/RecentFilesModel.h>

#include <tgCore/File.h>

#if defined(TINYGFX_NFD)
#include <nfd.hpp>
#endif // TINYGFX_NFD

#include <filesystem>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct FileBrowserSystem::Private
        {
            bool native = true;
            std::string path;
            FileBrowserOptions options;
            std::shared_ptr<FileBrowser> fileBrowser;
            std::shared_ptr<RecentFilesModel> recentFilesModel;
        };

        FileBrowserSystem::FileBrowserSystem(const std::shared_ptr<Context>& context) :
            ISystem(context, "tg::ui::FileBrowserSystem"),
            _p(new Private)
        {
            TG_P();
            p.path = std::filesystem::current_path();
            p.recentFilesModel = RecentFilesModel::create(context);
#if defined(TINYGFX_NFD)
            NFD::Init();
#endif // TINYGFX_NFD
        }

        FileBrowserSystem::~FileBrowserSystem()
        {
#if defined(TINYGFX_NFD)
            NFD::Quit();
#endif // TINYGFX_NFD
        }

        std::shared_ptr<FileBrowserSystem> FileBrowserSystem::create(const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileBrowserSystem>(new FileBrowserSystem(context));
        }

        void FileBrowserSystem::open(
            const std::shared_ptr<IWindow>& window,
            const std::function<void(const std::string&)>& callback)
        {
            TG_P();
            bool native = p.native;
#if defined(TINYGFX_NFD)
            if (native)
            {
                nfdu8char_t* outPath = nullptr;
                NFD::OpenDialog(outPath);
                if (outPath)
                {
                    callback(outPath);
                    NFD::FreePath(outPath);
                }
            }
#else  // TINYGFX_NFD
            native = false;
#endif  // TINYGFX_NFD
            if (!native)
            {
                if (auto context = _context.lock())
                {
                    if (!p.fileBrowser)
                    {
                        p.fileBrowser = FileBrowser::create(context, p.path);
                        p.fileBrowser->setRecentFilesModel(p.recentFilesModel);
                    }
                    p.fileBrowser->setOptions(p.options);
                    p.fileBrowser->open(window);
                    p.fileBrowser->setCallback(
                        [this, callback](const std::string& value)
                        {
                            callback(value);
                            _p->fileBrowser->close();
                        });
                    p.fileBrowser->setCloseCallback(
                        [this]
                        {
                            _p->path = _p->fileBrowser->getPath();
                            _p->options = _p->fileBrowser->getOptions();
                        });
                }
            }
        }

        bool FileBrowserSystem::isNativeFileDialog() const
        {
            return _p->native;
        }

        void FileBrowserSystem::setNativeFileDialog(bool value)
        {
            _p->native = value;
        }

        const std::string& FileBrowserSystem::getPath() const
        {
            return _p->path;
        }

        void FileBrowserSystem::setPath(const std::string& value)
        {
            _p->path = value;
        }

        const FileBrowserOptions& FileBrowserSystem::getOptions() const
        {
            return _p->options;
        }

        void FileBrowserSystem::setOptions(const FileBrowserOptions& options)
        {
            _p->options = options;
        }

        const std::shared_ptr<RecentFilesModel>& FileBrowserSystem::getRecentFilesModel() const
        {
            return _p->recentFilesModel;
        }
    }
}
