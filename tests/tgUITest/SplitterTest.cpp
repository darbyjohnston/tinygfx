// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/SplitterTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/Label.h>
#include <tgUI/Splitter.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        SplitterTest::SplitterTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::SplitterTest")
        {}

        SplitterTest::~SplitterTest()
        {}

        std::shared_ptr<SplitterTest> SplitterTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<SplitterTest>(new SplitterTest(context));
        }
                
        void SplitterTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("SplitterTest");
                auto app = App::create(
                    context,
                    argv,
                    "SplitterTest",
                    "Splitter test.");
                app->getStyle()->setSizeRole(SizeRole::HandleSmall, 100);
                auto window = Window::create(context, app, "SplitterTest");
                app->addWindow(window);
                window->show();
                app->tick();
                _test(context, app, window, Orientation::Horizontal);
                _test(context, app, window, Orientation::Vertical);
            }
        }

        void SplitterTest::_test(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Window>& window,
            Orientation orientation)
        {
            auto splitter = Splitter::create(context, orientation, window);
            std::vector<float> split = { .9F };
            splitter->setSplit(split);
            splitter->setSplit(split);
            TG_ASSERT(split == splitter->getSplit());
            app->tick();

            auto label0 = Label::create(context, "Label 0", splitter);
            auto label1 = Label::create(context, "Label 1", splitter);
            app->tick();
            splitter->setSplit({ .1F });
            app->tick();
            splitter->setSplit({ .5F });
            app->tick();

            window->setCursorEnter(true);
            Box2I g = splitter->getGeometry();
            V2I c = center(g);
            window->setCursorPos(c);
            window->setButton(0, true);
            window->setCursorPos(c + V2I(100, 100));
            window->setButton(0, false);

            splitter->setParent(nullptr);
        }
    }
}

