// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/FileBrowser.h>

#include <tgUI/IButton.h>

namespace tg
{
    namespace ui
    {
        class FileBrowserPathsWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            FileBrowserPathsWidget();

        public:
            virtual ~FileBrowserPathsWidget();

            static std::shared_ptr<FileBrowserPathsWidget> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void setCallback(const std::function<void(const std::filesystem::path&)>&);

            void setRecentFilesModel(const std::shared_ptr<RecentFilesModel>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            void _pathsUpdate();

            TG_PRIVATE();
        };

        struct FileBrowserInfo
        {
            std::filesystem::path           path;
            bool                            isDir = false;
            size_t                          size  = 0;
            std::filesystem::file_time_type time;
        };

        class FileBrowserButton : public IButton
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const FileBrowserInfo&,
                const std::shared_ptr<IWidget>& parent);

            FileBrowserButton();

        public:
            virtual ~FileBrowserButton();

            static std::shared_ptr<FileBrowserButton> create(
                const std::shared_ptr<core::Context>&,
                const FileBrowserInfo&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            const std::vector<int>& getTextWidths() const;

            void setColumns(const std::vector<int>&);

            void setCurrent(bool);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void clipEvent(const core::Box2I&, bool) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            TG_PRIVATE();
        };

        class FileBrowserDirectoryWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            FileBrowserDirectoryWidget();

        public:
            virtual ~FileBrowserDirectoryWidget();

            static std::shared_ptr<FileBrowserDirectoryWidget> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            const std::filesystem::path& getPath() const;
            void setPath(const std::filesystem::path&);

            void reload();

            void setCallback(const std::function<void(const std::filesystem::path&)>&);

            const FileBrowserOptions& getOptions() const;
            void setOptions(const FileBrowserOptions&);

            std::shared_ptr<core::IObservableValue<int> > observeCurrent() const;

            core::Box2I getRect(int) const;

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void keyFocusEvent(bool) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            void _directoryUpdate();
            void _setCurrent(int);
            void _currentUpdate();

            TG_PRIVATE();
        };
    }
}
