// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgBaseAppTest/AppTest.h>

#include <tgBaseApp/IApp.h>
#include <tgBaseApp/CmdLine.h>

#include <tgCore/Assert.h>
#include <tgCore/Memory.h>

using namespace tg::core;
using namespace tg::app;

namespace tg
{
    namespace app_test
    {
        AppTest::AppTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::app_test::AppTest")
        {}

        AppTest::~AppTest()
        {}

        std::shared_ptr<AppTest> AppTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<AppTest>(new AppTest(context));
        }

        namespace
        {
            class App : public IApp
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
                
                int run() override;
                
            private:
                Endian _arg = Endian::MSB;
                std::string _option;
            };

            void App::_init(
                const std::shared_ptr<core::Context>& context,
                std::vector<std::string>& argv)
            {
                IApp::_init(
                    context,
                    argv,
                    "tg::app_test::App",
                    "Test application",
                    {
                        CmdLineValueArg<Endian>::create(
                            _arg,
                            "arg",
                            "This is an argument")
                    },
                    {
                        CmdLineValueOption<std::string>::create(
                            _option,
                            { "-option" },
                            "This is an option")
                    });
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
            
            int App::run()
            {
                return _exit;
            }
        }
                
        void AppTest::run()
        {
            {
                char* argv[2];
                argv[0] = new char[2];
                argv[0][0] = 'a';
                argv[0][1] = 0;
                argv[1] = new char[2];
                argv[1][0] = 'b';
                argv[1][1] = 0;
                auto r = convert(2, argv);
                TG_ASSERT("a" == r[0]);
                TG_ASSERT("b" == r[1]);
                delete [] argv[0];
                delete [] argv[1];
            }
            {
                wchar_t* argv[2];
                argv[0] = new wchar_t[2];
                argv[0][0] = L'a';
                argv[0][1] = 0;
                argv[1] = new wchar_t[2];
                argv[1][0] = L'b';
                argv[1][1] = 0;
                auto r = convert(2, argv);
                TG_ASSERT("a" == r[0]);
                TG_ASSERT("b" == r[1]);
                delete [] argv[0];
                delete [] argv[1];
            }
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv = { "app", "-h" };
                auto app = App::create(context, argv);
                app->run();
            }
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv = { "app", "xxx" };
                try
                {
                    auto app = App::create(context, argv);
                }
                catch (const std::exception&)
                {}
            }
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv = { "app", "LSB", "-option" };
                try
                {
                    auto app = App::create(context, argv);
                }
                catch (const std::exception&)
                {}
            }
        }
    }
}

