// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/FileBrowser.h>

#include <tgUI/IButton.h>

#include <filesystem>

namespace tg
{
    namespace ui
    {
        struct FileInfo
        {
            std::filesystem::path path;
            bool isDir = false;
            size_t size = 0;
            std::filesystem::file_time_type time;
        };

        class PathsWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            PathsWidget();

        public:
            virtual ~PathsWidget();

            static std::shared_ptr<PathsWidget> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void setCallback(const std::function<void(const std::filesystem::path&)>&);

            void setRecentFilesModel(const std::shared_ptr<RecentFilesModel>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            void _createButton(
                const std::shared_ptr<core::Context>&,
                const std::string& text,
                const std::string& toolTip,
                const std::shared_ptr<IWidget>& parent);

            void _pathsUpdate();

            TG_PRIVATE();
        };

        class Button : public IButton
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const FileInfo&,
                const std::shared_ptr<IWidget>& parent);

            Button();

        public:
            virtual ~Button();

            static std::shared_ptr<Button> create(
                const std::shared_ptr<core::Context>&,
                const FileInfo&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            const std::vector<int>& getTextWidths() const;

            void setColumns(const std::vector<int>&);

            void sizeHintEvent(const SizeHintEvent&) override;
            void clipEvent(const core::Box2I&, bool) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            TG_PRIVATE();
        };

        class DirectoryWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            DirectoryWidget();

        public:
            virtual ~DirectoryWidget();

            static std::shared_ptr<DirectoryWidget> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void setPath(const std::filesystem::path&);

            void reload();

            void setCallback(const std::function<void(const std::filesystem::path&)>&);

            void setOptions(const FileBrowserOptions&);

            const FileBrowserOptions& getOptions() const;

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            void _directoryUpdate();

            TG_PRIVATE();
        };

        class FileBrowserWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::filesystem::path&,
                const std::shared_ptr<IWidget>& parent);

            FileBrowserWidget();

        public:
            virtual ~FileBrowserWidget();

            static std::shared_ptr<FileBrowserWidget> create(
                const std::shared_ptr<core::Context>&,
                const std::filesystem::path&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void setCallback(const std::function<void(const std::filesystem::path&)>&);

            void setCancelCallback(const std::function<void(void)>&);

            std::filesystem::path getPath() const;

            const FileBrowserOptions& getOptions() const;

            void setOptions(const FileBrowserOptions&);
            
            void setOptionsCallback(const std::function<void(const FileBrowserOptions&)>&);

            void setRecentFilesModel(const std::shared_ptr<RecentFilesModel>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            void _setPath(const std::filesystem::path&);

            void _pathUpdate();
            void _optionsUpdate();

            TG_PRIVATE();
        };
    }
}
