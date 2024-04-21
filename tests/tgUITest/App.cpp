// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/App.h>

#include <tgUITest/Window.h>

#include <tgUI/IconLibrary.h>
#include <tgUI/Init.h>
#include <tgUI/Style.h>

#include <tgCore/LogSystem.h>
#include <tgCore/Time.h>
#include <tgCore/Timer.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        namespace
        {
            const std::chrono::milliseconds timeout(5);
        }

        struct App::Private
        {
            float displayScale = 1.F;
            std::shared_ptr<FontSystem> fontSystem;
            std::shared_ptr<ui::Style> style;
            std::shared_ptr<ui::IconLibrary> iconLibrary;
            bool running = true;
            std::list<std::shared_ptr<Window> > windows;
            std::shared_ptr<Timer> logTimer;
        };

        void App::_init(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<app::ICmdLineArg> >& cmdLineArgs,
            const std::vector<std::shared_ptr<app::ICmdLineOption> >& cmdLineOptions)
        {
            app::IApp::_init(
                context,
                argv,
                name,
                summary,
                cmdLineArgs,
                cmdLineOptions);
            TG_P();
            ui::init(context);

            p.fontSystem = context->getSystem<FontSystem>();
            p.style = Style::create(context);
            p.iconLibrary = IconLibrary::create(context);

            p.logTimer = Timer::create(context);
            p.logTimer->setRepeating(true);
            auto weak = std::weak_ptr<App>(std::dynamic_pointer_cast<App>(shared_from_this()));
            p.logTimer->start(
                std::chrono::seconds(10),
                [weak]
                {
                    if (auto app = weak.lock())
                    {
                        app->_log();
                    }
                });
        }

        App::App() :
            _p(new Private)
        {}

        App::~App()
        {}

        std::shared_ptr<App> App::create(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<app::ICmdLineArg> >& cmdLineArgs,
            const std::vector<std::shared_ptr<app::ICmdLineOption> >& cmdLineOptions)
        {
            auto out = std::shared_ptr<App>(new App);
            out->_init(context, argv, name, summary, cmdLineArgs, cmdLineOptions);
            return out;
        }

        void App::addWindow(const std::shared_ptr<Window>& window)
        {
            TG_P();
            p.windows.push_back(window);
        }

        void App::removeWindow(const std::shared_ptr<Window>& window)
        {
            TG_P();
            const auto i = std::find(p.windows.begin(), p.windows.end(), window);
            if (i != p.windows.end())
            {
                p.windows.erase(i);
            }
        }

        void App::exit()
        {
            _p->running = false;
        }

        int App::run()
        {
            TG_P();
            const int exit = getExit();
            if (0 == exit)
            {
                auto t0 = std::chrono::steady_clock::now();
                while (p.running && !p.windows.empty())
                {
                    _context->tick();

                    for (auto& window : p.windows)
                    {
                        TickEvent tickEvent(
                            p.fontSystem,
                            p.displayScale,
                            p.style,
                            p.iconLibrary);
                        _tickRecursive(
                            window,
                            true,
                            true,
                            tickEvent);
                    }

                    auto t1 = std::chrono::steady_clock::now();
                    sleep(timeout, t0, t1);
                    t1 = std::chrono::steady_clock::now();
                    t0 = t1;

                    //! \todo
                    p.running = false;
                }
            }
            return exit;
        }

        void App::_tickRecursive(
            const std::shared_ptr<IWidget>& widget,
            bool visible,
            bool enabled,
            const TickEvent& event)
        {
            TG_P();
            const bool parentsVisible = visible && widget->isVisible(false);
            const bool parentsEnabled = enabled && widget->isEnabled(false);
            for (const auto& child : widget->getChildren())
            {
                _tickRecursive(
                    child,
                    parentsVisible,
                    parentsEnabled,
                    event);
            }
            widget->tickEvent(visible, enabled, event);
        }

        void App::_log()
        {}
    }
}

