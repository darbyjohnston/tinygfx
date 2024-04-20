// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUIAppTest/AppTest.h>

#include <tgUIApp/App.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {

        namespace
        {
            class App : public ui::App
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    std::vector<std::string>& argv);

                App() = default;

            public:
                virtual ~App();

                static std::shared_ptr<App> create(
                    const std::shared_ptr<core::Context>&,
                    std::vector<std::string>& argv);

            private:
            };

            void App::_init(
                const std::shared_ptr<core::Context>& context,
                std::vector<std::string>& argv)
            {
                IApp::_init(
                    context,
                    argv,
                    "tg::ui_test::App",
                    "Test UI application");
            }

            App::~App()
            {}

            std::shared_ptr<App> App::create(
                const std::shared_ptr<core::Context>& context,
                std::vector<std::string>& argv)
            {
                auto out = std::shared_ptr<App>(new App);
                out->_init(context, argv);
                return out;
            }
        }

        AppTest::AppTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::AppTest")
        {}

        AppTest::~AppTest()
        {}

        std::shared_ptr<AppTest> AppTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<AppTest>(new AppTest(context));
        }
                
        void AppTest::run()
        {
            int r = 0;
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv = { "app" };
                try
                {
                    auto app = App::create(context, argv);
                    r = app->getExit();
                    if (0 == r)
                    {
                        r = app->run();
                    }
                }
                catch (const std::exception&)
                {}
            }
            TG_ASSERT(0 == r);
        }
    }
}

