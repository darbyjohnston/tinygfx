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
        //! File browsaer paths widget.
        class FileBrowserPathsWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            FileBrowserPathsWidget();

        public:
            virtual ~FileBrowserPathsWidget();

            //! Create a new widget.
            static std::shared_ptr<FileBrowserPathsWidget> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the callback.
            void setCallback(const std::function<void(const std::filesystem::path&)>&);

            //! Set the recent files model.
            void setRecentFilesModel(const std::shared_ptr<RecentFilesModel>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            void _pathsUpdate();

            TG_PRIVATE();
        };

        //! File browser information.
        struct FileBrowserInfo
        {
            std::filesystem::path           path;
            bool                            isDir = false;
            size_t                          size  = 0;
            std::filesystem::file_time_type time;
        };

        //! File browser button.
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

            //! Create a new widget.
            static std::shared_ptr<FileBrowserButton> create(
                const std::shared_ptr<core::Context>&,
                const FileBrowserInfo&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the text widths.
            const std::vector<int>& getTextWidths() const;

            //! Set the columns.
            void setColumns(const std::vector<int>&);

            //! Set whether the button is current.
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

        //! File browser directory widget.
        class FileBrowserDirectoryWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            FileBrowserDirectoryWidget();

        public:
            virtual ~FileBrowserDirectoryWidget();

            //! Create a new widget.
            static std::shared_ptr<FileBrowserDirectoryWidget> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the path.
            const std::filesystem::path& getPath() const;

            //! Set the path.
            void setPath(const std::filesystem::path&);

            //! Reload the directory.
            void reload();

            //! Set the callback.
            void setCallback(const std::function<void(const std::filesystem::path&)>&);

            //! Get the options.
            const FileBrowserOptions& getOptions() const;

            //! Set the options.
            void setOptions(const FileBrowserOptions&);

            //! Observer the current item.
            std::shared_ptr<core::IObservableValue<int> > observeCurrent() const;

            //! Get an item rectangle.
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

        //! File browser widget.
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

            //! Create a new widget.
            static std::shared_ptr<FileBrowserWidget> create(
                const std::shared_ptr<core::Context>&,
                const std::filesystem::path&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the callback.
            void setCallback(const std::function<void(const std::filesystem::path&)>&);

            //! Set the cancel callback.
            void setCancelCallback(const std::function<void(void)>&);

            //! Get the path.
            std::filesystem::path getPath() const;

            //! Get the options.
            const FileBrowserOptions& getOptions() const;

            //! Set the options.
            void setOptions(const FileBrowserOptions&);

            //! Set the options callback.
            void setOptionsCallback(const std::function<void(const FileBrowserOptions&)>&);

            //! Get the recent files model.
            const std::shared_ptr<RecentFilesModel>& getRecentFilesModel() const;

            //! Set the recent files model.
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
