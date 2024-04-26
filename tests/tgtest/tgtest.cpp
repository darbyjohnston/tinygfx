// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "tgtest.h"

#include <tgUIAppTest/AppTest.h>

#include <tgUITest/ActionTest.h>
#include <tgUITest/ButtonGroupTest.h>
#include <tgUITest/ButtonTest.h>
#include <tgUITest/ColorWidgetTest.h>
#include <tgUITest/DoubleEditTest.h>
#include <tgUITest/DoubleEditSliderTest.h>
#include <tgUITest/DoubleSliderTest.h>
#include <tgUITest/DoubleModelTest.h>
#include <tgUITest/DragAndDropTest.h>
#include <tgUITest/EventTest.h>
#include <tgUITest/FileBrowserTest.h>
#include <tgUITest/FileEditTest.h>
#include <tgUITest/FloatEditTest.h>
#include <tgUITest/FloatEditSliderTest.h>
#include <tgUITest/FloatSliderTest.h>
#include <tgUITest/FloatModelTest.h>
#include <tgUITest/GridLayoutTest.h>
#include <tgUITest/IntEditTest.h>
#include <tgUITest/IntEditSliderTest.h>
#include <tgUITest/IntSliderTest.h>
#include <tgUITest/IntModelTest.h>
#include <tgUITest/LabelTest.h>
#include <tgUITest/LayoutUtilTest.h>
#include <tgUITest/LineEditTest.h>
#include <tgUITest/MDIWidgetTest.h>
#include <tgUITest/RowLayoutTest.h>
#include <tgUITest/StackLayoutTest.h>
#include <tgUITest/StyleTest.h>
#include <tgUITest/WidgetOptionsTest.h>

#include <tgBaseAppTest/AppTest.h>
#include <tgBaseAppTest/CmdLineTest.h>

#if defined(TINYGFX_API_GL_4_1) || defined(TINYGFX_API_GLES_2)
#include <tgGLTest/MeshTest.h>
#include <tgGLTest/OffscreenBufferTest.h>
#include <tgGLTest/TextureAtlasTest.h>
#include <tgGLTest/TextureTest.h>
#include <tgGLTest/RenderTest.h>
#include <tgGLTest/ShaderTest.h>
#include <tgGLTest/WindowTest.h>
#endif // TINYGFX_API_GL_4_1

#include <tgCoreTest/BoxPackTest.h>
#include <tgCoreTest/BoxTest.h>
#include <tgCoreTest/ColorTest.h>
#include <tgCoreTest/CommandTest.h>
#include <tgCoreTest/ErrorTest.h>
#include <tgCoreTest/FileIOTest.h>
#include <tgCoreTest/FileTest.h>
#include <tgCoreTest/FontSystemTest.h>
#include <tgCoreTest/FormatTest.h>
#include <tgCoreTest/ImageIOTest.h>
#include <tgCoreTest/ImageTest.h>
#include <tgCoreTest/LRUCacheTest.h>
#include <tgCoreTest/MathTest.h>
#include <tgCoreTest/MatrixTest.h>
#include <tgCoreTest/MemoryTest.h>
#include <tgCoreTest/MeshTest.h>
#include <tgCoreTest/OSTest.h>
#include <tgCoreTest/ObservableTest.h>
#include <tgCoreTest/PNGTest.h>
#include <tgCoreTest/RangeTest.h>
#include <tgCoreTest/RenderOptionsTest.h>
#include <tgCoreTest/SizeTest.h>
#include <tgCoreTest/StringTest.h>
#include <tgCoreTest/SystemTest.h>
#include <tgCoreTest/TimeTest.h>
#include <tgCoreTest/TimerTest.h>
#include <tgCoreTest/VectorTest.h>

#include <tgUI/Init.h>

#include <tgBaseApp/CmdLine.h>

#if defined(TINYGFX_API_GL_4_1) || defined(TINYGFX_API_GLES_2)
#include <tgGL/Init.h>
#endif // TINYGFX_API_GL_4_1

#include <tgCore/Context.h>
#include <tgCore/Format.h>
#include <tgCore/Time.h>

#include <iostream>

using namespace tg;
using namespace tg::core;

namespace tg
{
    namespace tests
    {
        struct App::Private
        {
            std::string testName;
            std::vector<std::shared_ptr<test::ITest> > tests;
            std::chrono::steady_clock::time_point startTime;
        };
        
        void App::_init(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv)
        {
            app::IApp::_init(
                context,
                argv,
                "tgtest",
                "Test application",
                {
                    app::CmdLineValueArg<std::string>::create(
                        _p->testName,
                        "Test",
                        "Name of the test to run.",
                        true)
                });
            TG_P();
            p.startTime = std::chrono::steady_clock::now();                
#if defined(TINYGFX_API_GL_4_1) || defined(TINYGFX_API_GLES_2)
            gl::init(context);
#endif // TINYGFX_API_GL_4_1            
            ui::init(context);

            p.tests.push_back(core_test::BoxPackTest::create(context));
            p.tests.push_back(core_test::BoxTest::create(context));
            p.tests.push_back(core_test::ColorTest::create(context));
            p.tests.push_back(core_test::CommandTest::create(context));
            p.tests.push_back(core_test::ErrorTest::create(context));
            p.tests.push_back(core_test::FileIOTest::create(context));
            p.tests.push_back(core_test::FileTest::create(context));
            p.tests.push_back(core_test::FontSystemTest::create(context));
            p.tests.push_back(core_test::FormatTest::create(context));
            p.tests.push_back(core_test::ImageIOTest::create(context));
            p.tests.push_back(core_test::ImageTest::create(context));
            p.tests.push_back(core_test::LRUCacheTest::create(context));
            p.tests.push_back(core_test::MathTest::create(context));
            p.tests.push_back(core_test::MatrixTest::create(context));
            p.tests.push_back(core_test::MemoryTest::create(context));
            p.tests.push_back(core_test::MeshTest::create(context));
            p.tests.push_back(core_test::OSTest::create(context));
            p.tests.push_back(core_test::ObservableTest::create(context));
            p.tests.push_back(core_test::PNGTest::create(context));
            p.tests.push_back(core_test::RangeTest::create(context));
            p.tests.push_back(core_test::RenderOptionsTest::create(context));
            p.tests.push_back(core_test::SizeTest::create(context));
            p.tests.push_back(core_test::StringTest::create(context));
            p.tests.push_back(core_test::SystemTest::create(context));
            p.tests.push_back(core_test::TimeTest::create(context));
            p.tests.push_back(core_test::TimerTest::create(context));
            p.tests.push_back(core_test::VectorTest::create(context));

#if defined(TINYGFX_API_GL_4_1) || defined(TINYGFX_API_GLES_2)
            p.tests.push_back(gl_test::MeshTest::create(context));
            p.tests.push_back(gl_test::OffscreenBufferTest::create(context));
            p.tests.push_back(gl_test::TextureAtlasTest::create(context));
            p.tests.push_back(gl_test::TextureTest::create(context));
            p.tests.push_back(gl_test::RenderTest::create(context));
            p.tests.push_back(gl_test::ShaderTest::create(context));
            p.tests.push_back(gl_test::WindowTest::create(context));
#endif // TINYGFX_API_GL_4_1

            p.tests.push_back(app_test::AppTest::create(context));
            p.tests.push_back(app_test::CmdLineTest::create(context));

            p.tests.push_back(ui_test::ActionTest::create(context));
            p.tests.push_back(ui_test::ButtonTest::create(context));
            p.tests.push_back(ui_test::ButtonGroupTest::create(context));
            p.tests.push_back(ui_test::ColorWidgetTest::create(context));
            p.tests.push_back(ui_test::DoubleEditTest::create(context));
            p.tests.push_back(ui_test::DoubleEditSliderTest::create(context));
            p.tests.push_back(ui_test::DoubleSliderTest::create(context));
            p.tests.push_back(ui_test::DoubleModelTest::create(context));
            p.tests.push_back(ui_test::DragAndDropTest::create(context));
            p.tests.push_back(ui_test::EventTest::create(context));
            p.tests.push_back(ui_test::FileBrowserTest::create(context));
            p.tests.push_back(ui_test::FileEditTest::create(context));
            p.tests.push_back(ui_test::FloatEditTest::create(context));
            p.tests.push_back(ui_test::FloatEditSliderTest::create(context));
            p.tests.push_back(ui_test::FloatSliderTest::create(context));
            p.tests.push_back(ui_test::FloatModelTest::create(context));
            p.tests.push_back(ui_test::GridLayoutTest::create(context));
            p.tests.push_back(ui_test::IntEditTest::create(context));
            p.tests.push_back(ui_test::IntEditSliderTest::create(context));
            p.tests.push_back(ui_test::IntSliderTest::create(context));
            p.tests.push_back(ui_test::IntModelTest::create(context));
            p.tests.push_back(ui_test::LabelTest::create(context));
            p.tests.push_back(ui_test::LayoutUtilTest::create(context));
            p.tests.push_back(ui_test::LineEditTest::create(context));
            p.tests.push_back(ui_test::MDIWidgetTest::create(context));
            p.tests.push_back(ui_test::RowLayoutTest::create(context));
            p.tests.push_back(ui_test::StackLayoutTest::create(context));
            p.tests.push_back(ui_test::StyleTest::create(context));
            p.tests.push_back(ui_test::WidgetOptionsTest::create(context));

            p.tests.push_back(ui_test::AppTest::create(context));
        }

        App::App() :
            _p(new Private)
        {}

        App::~App()
        {}

        std::shared_ptr<App> App::create(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv)
        {
            auto out = std::shared_ptr<App>(new App);
            out->_init(context, argv);
            return out;
        }
        
        int App::run()
        {
            TG_P();
            const int exit = getExit();
            if (0 == exit)
            {
                // Get the tests to run.
                std::vector<std::shared_ptr<test::ITest> > runTests;
                for (const auto& test : p.tests)
                {
                    if (p.testName.empty() ||
                        (!p.testName.empty() && contains(test->getName(), p.testName)))
                    {
                        runTests.push_back(test);
                    }
                }                
            
                // Run the tests.
                for (const auto& test : runTests)
                {
                    _context->tick();
                    _print(Format("Running test: {0}").arg(test->getName()));
                    test->run();
                }

                // Tick the tests.
                bool tickTests = false;
                do
                {
                    auto t0 = std::chrono::steady_clock::now();
                    tickTests = false;
                    for (const auto& test : runTests)
                    {
                        _context->tick();
                        if (test->doTick())
                        {
                            tickTests = true;
                            test->tick();
                        }
                        auto t1 = std::chrono::steady_clock::now();
                        sleep(std::chrono::milliseconds(5), t0, t1);
                        t0 = t1;
                    }
                }
                while (tickTests);
                
                const auto now = std::chrono::steady_clock::now();
                const std::chrono::duration<float> diff = now - p.startTime;
                _print(Format("Seconds elapsed: {0}").arg(diff.count(), 2));
            }
            return exit;
        }
    }
}

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = app::convert(argc, argv);
        auto app = tests::App::create(context, args);
        r = app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

